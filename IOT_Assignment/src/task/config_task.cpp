
#include "config_task.h"

TaskHandle_t configTask_handle = NULL;
TaskHandle_t handlerResetTask_handle = NULL;
Preferences preferences;

void saveConfigToFlash(const config_data_t &config)
{
  preferences.begin("device-config", false);

  preferences.putString("token", config.token);
  preferences.putString("ssid", config.SSID);
  preferences.putString("pass", config.password);

  preferences.putBool("is4G", config.is4G);
  preferences.putBool("isWifi", config.isWifi);
  preferences.putInt("carrier", (int)config.carrier);
  preferences.putBool("useAdvAPN", config.useAdvancedAPN);
  preferences.putString("apn", config.apn);
  preferences.putString("apn_user", config.apn_user);
  preferences.putString("apn_pass", config.apn_pass);
  preferences.putBool("configured", config.config_status);

  preferences.end();
}

bool loadConfigFromFlash(config_data_t &config)
{
  preferences.begin("device-config", true); // true = readonly

  config.token = preferences.getString("token", "");
  config.SSID = preferences.getString("ssid", "");
  config.password = preferences.getString("pass", "");

  config.is4G = preferences.getBool("is4G", false);
  config.isWifi = preferences.getBool("isWifi", false);
  config.carrier = (isp_name_t)preferences.getInt("carrier", 0);
  config.useAdvancedAPN = preferences.getBool("useAdvAPN", false);
  config.apn = preferences.getString("apn", "");
  config.apn_user = preferences.getString("apn_user", "");
  config.apn_pass = preferences.getString("apn_pass", "");
  config.config_status = preferences.getBool("configured", false);

  preferences.end();

  return device_config_data.config_status;
}

void clearConfigFromFlash(void)
{
  preferences.begin("device-config", false);
  preferences.clear();
  preferences.end();
}

void configTask(void *pvParameters)
{
  if (loadConfigFromFlash(device_config_data))
  {
    logger_connection_t status = initConnection(device_config_data);
    if ((status == connected_4G) || (status == connected_wifi))
    {
      Serial.println("Load config successful, start connection");
    }
    vTaskResume(serverTask_handle);
    Serial.println("resume serverTask");
    vTaskDelay(pdMS_TO_TICKS(100));
    Serial.println("Suspending configTask");
    vTaskDelete(NULL);
  }
  else{
    startServer();
  }

  while (true)
  {
    webServerLoop();
    if (device_config_data.config_status)
    {
      logger_connection_t status = initConnection(device_config_data);
      if ((status == connected_4G) || (status == connected_wifi))
      {
        Serial.println("done config, stop server");
        stopServer();
        WiFi.softAPdisconnect(true);
        saveConfigToFlash(device_config_data);
        Serial.println("saved config to flash");

        vTaskResume(serverTask_handle);

        

        Serial.println("resume server task");
        vTaskDelay(pdMS_TO_TICKS(100));
        Serial.println("Suspending configTask");
        vTaskDelete(NULL);  // An toàn hơn
      }
    }

    vTaskDelay(pdMS_TO_TICKS(10));  // Đừng để while(true) chạy liên tục gây stack tràn
  }
}

void handlerResetTask(void *pvParameters)
{

  while (true)
  {
    if (get_button_state())
    {
      Serial.println("ESP32 Clear Configuration and Restart");
      clearConfigFromFlash();
      ESP.restart();
    }
    deboucing_run();
    vTaskDelay(10);
  }
}

void initConfigTask(void)
{
  xTaskCreate(configTask, "configTask", 1024 * 5, NULL, 2, &configTask_handle);
  xTaskCreate(handlerResetTask, "handleResetTask", 1024 * 3, NULL, 1, &handlerResetTask_handle);
}