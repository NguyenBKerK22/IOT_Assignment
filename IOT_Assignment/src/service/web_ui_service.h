#ifndef WEB_UI_SERVICE_H
#define WEB_UI_SERVICE_H
#pragma once

#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

typedef struct config_data_t {
    String token = "";
    String SSID = "";
    String password = "";
    bool is4G = false;
    bool isWifi = false;
};


extern config_data_t device_config_data;
extern WebServer server;

const char index_html[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
    <html lang="en">
    <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Smart Farm Device</title>
    <style>
        body {
        font-family: Arial, sans-serif;
        background: #f5f7fa;
        margin: 0;
        padding: 0;
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        min-height: 100vh;
        }
        h1 {
        margin-top: 20px;
        color: #2c3e50;
        }
        .container {
        background: white;
        padding: 20px 30px;
        border-radius: 10px;
        box-shadow: 0 4px 8px rgba(0,0,0,0.1);
        max-width: 400px;
        width: 100%;
        }
        label {
        display: block;
        margin-top: 15px;
        color: #34495e;
        }
        input, select {
        width: 100%;
        padding: 10px;
        margin-top: 5px;
        border: 1px solid #ccc;
        border-radius: 5px;
        }
        button {
        margin-top: 20px;
        width: 100%;
        padding: 10px;
        background-color: #27ae60;
        color: white;
        border: none;
        border-radius: 5px;
        cursor: pointer;
        }
        button:hover {
        background-color: #219150;
        }
        #wifi-config {
        display: none;
        }
    </style>
    </head>
    <body>
    <h1>Smart Farm Device</h1>
    <div class="container">
        <form id="config-form">
        <label for="token">Device Token</label>
        <input type="text" id="token" name="token" required />

        <label for="conn-method">Connection Method</label>
        <select id="conn-method" name="conn-method" onchange="toggleWifiFields()">
            <option value="4G">4G</option>
            <option value="WiFi">WiFi</option>
        </select>

        <div id="wifi-config">
            <label for="ssid">WiFi SSID</label>
            <input type="text" id="ssid" name="ssid" />

            <label for="password">WiFi Password</label>
            <input type="password" id="password" name="password" />
        </div>

        <button type="submit">Save Configuration</button>
        </form>
    </div>

    <script>
        function toggleWifiFields() {
        const method = document.getElementById("conn-method").value;
        const wifiConfig = document.getElementById("wifi-config");
        wifiConfig.style.display = method === "WiFi" ? "block" : "none";
        }

        document.getElementById("config-form").addEventListener("submit", function(e) {
        e.preventDefault();
        const formData = new FormData(e.target);
        const data = {};
        formData.forEach((value, key) => data[key] = value);
        fetch("/save-config", {
            method: "POST",
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(data)
        }).then(res => alert("Configuration saved!"));
        });
    </script>
</body>
</html>

)rawliteral";
    
void handleRoot();
void handleSaveConfig();
void startServer();
void stopServer();
void webServerLoop();

String getUniqueSSID();

#endif // WEB_UI_SERVICE_H