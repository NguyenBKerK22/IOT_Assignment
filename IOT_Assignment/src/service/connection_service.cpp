#include <connection_service.h>


logger_connection_t initConnection(config_data_t device_config_data)
{
    if(device_config_data.isWifi){
        WiFi.begin(device_config_data.SSID, device_config_data.password);

        unsigned long startAttemptTime = millis();

        while (WiFi.status() != WL_CONNECTED && (millis() - startAttemptTime) < CONNECTION_TIMEOUT) {
            Serial.print(".");
            delay(500);
        }

        if(WiFi.status() == WL_CONNECTED) {
            WiFi.setAutoConnect(true);
            return connected_wifi;
        }
        else {
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

        return connected_4G;

    }
}