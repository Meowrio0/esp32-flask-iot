# 🌡️ ESP32 + Flask IoT 溫濕度監控系統

本專案為一個基於 ESP32 的 IoT 溫濕度感測系統，使用 DHT11 感測器讀取數據，透過 WiFi 傳送至 Flask Web Server，並存入 MySQL 資料庫。網頁端使用 Highcharts 將資料以圖表方式呈現，並支援每 5 秒自動更新。

---

## 專案亮點

- 使用 ESP32 + DHT11 進行環境溫濕度量測
- WiFi 傳輸資料至 Flask 後端伺服器
- 將資料寫入 MySQL 資料庫（透過 SQLAlchemy）
- 使用 Highcharts 建立動態圖表介面（自動更新）
- 適用於物聯網初學者作為端到端實作練習

---

## 使用技術

| 技術 | 說明 |
|------|------|
| ESP32 | 感測器主控晶片，搭配 DHT11 讀取環境數據 |
| Arduino C++ | 控制 ESP32 運作與 HTTP 通訊 |
| Flask | 後端伺服器，接收資料並與資料庫互動 |
| MySQL | 儲存溫濕度資料 |
| SQLAlchemy | ORM，簡化與資料庫的連接與操作 |
| Highcharts | 將資料以圖表方式即時呈現於網頁前端 |

---

## 📁 專案結構
esp32_flask_app/
├── app.py
    → Flask 主後端程式
├── esp32_code.ino
    → ESP32 程式（Arduino 格式）
├── requirements.txt
    → Python 相依套件清單
├── README.md
    → 本說明文件
├── templates/
│   └── index.html
        → 使用 Highcharts 顯示圖表
└── screenshots/
    → 成果截圖資料夾
---

##  快速啟動說明

###  安裝 Python 環境與相依套件

```bash
# 建立並啟動虛擬環境（可選）
python -m venv venv
source venv/bin/activate  # macOS / Linux
# venv\Scripts\activate    # Windows

# 安裝 Flask 與相關套件
pip install -r requirements.txt
python app.py
# 或指定 port:
# python app.py --host=0.0.0.0 --port=5050
http://<你的電腦 IP>:5050/
