#include <connection_service.h>


logger_connection_t initConnection(config_data_t device_config_data)
{
    if(device_config_data.isWifi){
        // Serial.printf("SSID: %s | Password: %s\n", device_config_data.SSID, device_config_data.password);        
        WiFi.begin(device_config_data.SSID.c_str(), device_config_data.password.c_str());        

        unsigned long startAttemptTime = millis();

        while (WiFi.status() != WL_CONNECTED && (millis() - startAttemptTime) < CONNECTION_TIMEOUT) {
            Serial.print(".");
            vTaskDelay(500);
        }

        if(WiFi.status() == WL_CONNECTED) {
            Serial.println("connected wifi");
            vTaskDelay(500);
            WiFi.setAutoConnect(true);
            return connected_wifi;
        }
        else {
            Serial.println("cant connect wifi");
            return timeout_wifi;
        }
    }

    if(device_config_data.is4G){
        if(!device_config_data.useAdvancedAPN){
            switch (device_config_data.carrier)
            {
            case viettel:
                /* code */
                set_apn("0");
                break;
            case mobiphone:
                /* code */
                set_apn("1");
                break;
            case vinaphone:
                /* code */
                set_apn("2");
                break;
            default:
                break;
            }
        }
        else{
            set_apn(device_config_data.apn, device_config_data.apn_user, device_config_data.apn_pass);
        }
        init_sim();
        run_sim();

        return connected_4G;
    }

    return unknown_state;
}