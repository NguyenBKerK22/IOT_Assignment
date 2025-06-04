#include <ota_service.h>

/*
    We can send some telemetry or update attribute to notify server that we are going to update new firmware
    or just pending all tasks which are running to focus on OTA update progress.
*/
void update_starting_callback()
{
}

/*
    We must update firmware to notify that the OTA update progress is success or not and resume all the tasks
    suspended
*/
void finished_callback(const bool &success)
{
    if (success)
    {
        Serial.println("Done, Reboot now");

        esp_restart();
        return;
    }
}

/*
    Send telemtry during the OTA update progress for monitoring.
*/
void progress_callback(const size_t &current, const size_t &total)
{
    float ota_progress = static_cast<float>(current * 100U) / total;
    Serial.printf("Progress %.2f%%\n", ota_progress);
}
