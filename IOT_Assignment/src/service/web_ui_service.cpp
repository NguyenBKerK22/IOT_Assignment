#include <web_ui_service.h>

WebServer server(80);
config_data_t device_config_data;

void handleRoot()
{
    server.send_P(200, "text/html", index_html);
}

void handleSaveConfig()
{
    if (server.method() == HTTP_POST)
    {
        StaticJsonDocument<512> jsonDoc;
        DeserializationError error = deserializeJson(jsonDoc, server.arg("plain"));

        if (!error)
        {
            String token = jsonDoc["token"] | "";
            String method = jsonDoc["conn-method"] | "";
            String ssid = jsonDoc["ssid"] | "";
            String password = jsonDoc["password"] | "";
            String carrier = jsonDoc["carrier"] | "";
            String useAdvancedAPN = jsonDoc["useAdvanceAPN"] | "";
            String apn = jsonDoc["apn"] | "";
            String apn_user = jsonDoc["apn-user"] | "";
            String apn_pass = jsonDoc["apn-pass"] | "";

            bool isWifi = method == "WiFi";
            bool is4G = method == "4G";

            device_config_data.token = token;
            device_config_data.SSID = ssid;
            device_config_data.password = password;
            device_config_data.isWifi = isWifi;
            device_config_data.is4G = is4G;

            if(carrier == "viettel"){
                device_config_data.carrier = viettel;    
            }
            else if(carrier == "mobiphone"){
                device_config_data.carrier = mobiphone;    
            }
            else if(carrier == "vinaphone"){
                device_config_data.carrier = vinaphone;    
            }

            device_config_data.useAdvancedAPN = useAdvancedAPN;
            device_config_data.apn = apn;
            device_config_data.apn_user = apn_user;
            device_config_data.apn_pass = apn_pass;

            Serial.println("=== Received Config ===");
            Serial.println("Token: " + token);
            Serial.println("Method: " + method);
            if (isWifi)
            {
                Serial.println("SSID: " + ssid);
                Serial.println("Password: " + password);
            }
            else if (is4G)
            {
                Serial.println("Carrier: " + carrier);                
                Serial.println("Use Advanced APN: " + useAdvancedAPN);                            
                
                if((apn != "") && (apn_pass != "") && (apn_user != "")){
                    device_config_data.useAdvancedAPN = true;
                    Serial.println("APN: " + apn);
                    Serial.println("APN User: " + apn_user);
                    Serial.println("APN Pass: " + apn_pass);                                
                }
                else{
                    device_config_data.useAdvancedAPN = false;
                }
            }
            device_config_data.config_status = true;
            server.send(200, "application/json", "{\"status\":\"ok\"}");
        }
        else
        {
            server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
        }
    }
}

String getUniqueSSID()
{
    String mac = WiFi.macAddress();
    mac.replace(":", "");
    return "SmartFarm_" + mac.substring(6); // ví dụ: SmartFarm_A1B2C3
}

void startServer()
{
    WiFi.softAP(getUniqueSSID().c_str(), "12345678");
    Serial.println("AP started. Connect to SSID: SmartFarm_Config");

    server.on("/", handleRoot);
    server.on("/save-config", HTTP_POST, handleSaveConfig);

    server.begin();
}

void stopServer()
{
    server.stop();
}

void webServerLoop()
{
    server.handleClient();
}
