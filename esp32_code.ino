// ChatGPT prompt: 請幫我撰寫一段 ESP32 程式，讀取 DHT11 溫濕度資料，透過 WiFi 傳送至 PHP 網頁，並上傳到 MySQL 資料庫。

#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// ✅ DHT11 設定
#define DHTPIN 15      // DHT11 接在 GPIO 4（可更改）
#define DHTTYPE DHT11 // 使用 DHT11
DHT dht(DHTPIN, DHTTYPE);

// ✅ WiFi 設定
const char* ssid = "林健勛的iPhone";   // WiFi SSID
const char* password = "bangbang";      // WiFi 密碼

// ✅ 伺服器 URL（你的 `addData.php`）
const char* serverName = "http://172.20.10.4:5050/add"; 

void setup() {
    Serial.begin(115200);
    
    // 初始化 DHT11
    dht.begin();

    // 連接 WiFi
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n✅ WiFi connected!");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) { // 確保 WiFi 仍然連線
        HTTPClient http;

        // 讀取 DHT11 感測器數據
        float temp = dht.readTemperature(); // 攝氏溫度
        float humid = dht.readHumidity();   // 濕度

        // 確保感測數據有效
        if (isnan(temp) || isnan(humid)) {
            Serial.println("❌ Failed to read from DHT sensor!");
            return;
        }

        // 構造 HTTP GET 請求
        String url = String(serverName) + "?temp=" + String(temp) + "&humid=" + String(humid);
        Serial.println("Sending GET request to: " + url);

        http.begin(url);
        int httpResponseCode = http.GET(); // 執行請求

        if (httpResponseCode > 0) {
            Serial.print("✅ Server Response: ");
            Serial.println(http.getString()); // 顯示伺服器回應
        } else {
            Serial.print("❌ Error: ");
            Serial.println(httpResponseCode);
        }
        http.end(); // 關閉 HTTP 連線
    } else {
        Serial.println("❌ WiFi Disconnected!");
    }

    delay(5000); // 每 5 秒發送一次
}