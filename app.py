# app.py - SQLAlchemy 版，避免 native_password 錯誤
from flask import Flask, request, jsonify, render_template
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import text
import pymysql

app = Flask(__name__)

# ✅ MySQL 資料庫設定（使用 pymysql 連接器）
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://root:@localhost/aiotdb'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

db = SQLAlchemy(app)

# 首頁：Highcharts 圖表
@app.route('/')
def index():
    return render_template('index.html')

# 接收 ESP32 傳來的資料
@app.route('/add', methods=['GET'])
@app.route('/add', methods=['GET'])
def add_data():
    try:
        temp = float(request.args.get('temp', 0))
        humid = float(request.args.get('humid', 0))
        status = "green" if 20 <= temp <= 30 else "red"

        print(f"收到資料：temp={temp}, humid={humid}, status={status}")  # ← ✅ 加這行

        sql = text("INSERT INTO iot_data (temp, humid, status) VALUES (:temp, :humid, :status)")
        db.session.execute(sql, {"temp": temp, "humid": humid, "status": status})
        db.session.commit()

        return jsonify({"status": "success", "temp": temp, "humid": humid, "status_color": status})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)})

# 提供圖表資料
@app.route('/data')
def get_data():
    try:
        sql = text("""
            SELECT temp, humid, DATE_FORMAT(CONVERT_TZ(time, '+00:00', '+08:00'), '%Y-%m-%d %H:%i:%s') AS time, status
            FROM iot_data
            ORDER BY time DESC
            LIMIT 50
        """)
        result = db.session.execute(sql)
        rows = [dict(row._mapping) for row in result]
        return jsonify(rows[::-1])
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5050, debug=True)