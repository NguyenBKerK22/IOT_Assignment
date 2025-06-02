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
    String carrier = "";           // "viettel", "mobiphone", "vinaphone"
    bool useAdvancedAPN = false;   // true if select "tùy chọn nâng cao"
    String apn = "";
    String apn_user = "";
    String apn_pass = "";
} config_data_t;


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
    input, select, button {
      width: 100%;
      padding: 10px;
      margin-top: 5px;
      border: 1px solid #ccc;
      border-radius: 5px;
    }
    button {
      background-color: #27ae60;
      color: white;
      border: none;
      cursor: pointer;
    }
    button:hover {
      background-color: #219150;
    }
    #wifi-config,
    #cellular-config,
    #advanced-config {
      display: none;
    }
    .toggle-advanced {
      background-color: #2980b9;
      margin-top: 10px;
    }
    .toggle-advanced:hover {
      background-color: #1f6391;
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
      <select id="conn-method" name="conn-method" onchange="toggleConnFields()">
        <option value="4G">4G</option>
        <option value="WiFi">WiFi</option>
      </select>

      <div id="wifi-config">
        <label for="ssid">WiFi SSID</label>
        <input type="text" id="ssid" name="ssid" />

        <label for="password">WiFi Password</label>
        <input type="password" id="password" name="password" />
      </div>

      <div id="cellular-config">
        <label for="carrier">Nhà mạng</label>
        <select id="carrier" name="carrier">
          <option value="viettel">Viettel</option>
          <option value="mobifone">Mobifone</option>
          <option value="vinaphone">Vinaphone</option>
        </select>

        <button type="button" class="toggle-advanced" onclick="toggleAdvanced()">Tùy chọn nâng cao</button>

        <div id="advanced-config">
          <label for="apn">APN</label>
          <input type="text" id="apn" name="apn" />

          <label for="apn-user">APN Username</label>
          <input type="text" id="apn-user" name="apn-user" />

          <label for="apn-pass">APN Password</label>
          <input type="password" id="apn-pass" name="apn-pass" />
        </div>
      </div>

      <button type="submit">Save Configuration</button>
    </form>
  </div>

  <script>
    let useAdvanceAPN = 0;

    function toggleConnFields() {
      const method = document.getElementById("conn-method").value;
      const wifiConfig = document.getElementById("wifi-config");
      const cellularConfig = document.getElementById("cellular-config");

      wifiConfig.style.display = method === "WiFi" ? "block" : "none";
      cellularConfig.style.display = method === "4G" ? "block" : "none";
    }

    function toggleAdvanced() {
      const advanced = document.getElementById("advanced-config");
      const isVisible = advanced.style.display === "block";
      advanced.style.display = isVisible ? "none" : "block";
      useAdvanceAPN = isVisible ? 0 : 1;
    }

    document.addEventListener("DOMContentLoaded", function () {
      toggleConnFields();
    });

    document.getElementById("config-form").addEventListener("submit", function (e) {
      e.preventDefault();
      const formData = new FormData(e.target);
      const data = {};

      formData.forEach((value, key) => {
        data[key] = value;
      });

      // Thêm giá trị useAdvanceAPN vào dữ liệu gửi
      data["useAdvanceAPN"] = useAdvanceAPN;

      fetch("/save-config", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(data),
      })
      .then(res => {
        if (res.ok) {
          alert("Configuration saved!");
        } else {
          alert("Failed to save configuration.");
        }
      })
      .catch(err => {
        console.error("Error sending config:", err);
        alert("Error saving configuration.");
      });
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