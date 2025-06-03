#include "hal/module_sim.h"

String APN  = "";
String USERNAME = "";
String PASSWORD = "";

HardwareSerial SerialAT(2); // Same with modbus. will be fail
TinyGsm modem(SerialAT);
TinyGsmClient sim_client(modem); // need to wrap with arduino mqtt client to construct thingsboard object

// void set_apn(const String &apn, const String &username = "", const String &password = ""){
//     if(apn == "0"){
//         APN = APN_VIETTEL;
//         USERNAME = USERNAME_VIETTEL;
//         PASSWORD = PASSWORD_VIETTEL;
//     }else if(apn == "1"){
//         APN = APN_MOBIFONE;
//         USERNAME = USERNAME_MOBIPHONE;
//         PASSWORD = PASSWORD_MOBIPHONE;
//     }else if(apn == "2"){
//         APN = APN_VINAPHONE;
//         USERNAME = USERNAME_VINAPHONE;
//         PASSWORD = PASSWORD_VINAPHONE;
//     }else{
//         APN = apn;
//         USERNAME = username;
//         PASSWORD = password;
//     }
// };

void init_sim(){
    SerialAT.begin(115200, SERIAL_8N1, 16, 17);
    Serial.println(F("Initializing modem..."));
    delay(1000);
    modem.restart();
    String modemInfo = modem.getModemInfo();
    Serial.print(F("Modem: "));
    Serial.println(modemInfo);
};
bool modemConnected = false;
void run_sim(){
    if (!modemConnected) {
        Serial.print(F("Waiting for network..."));
        if (!modem.waitForNetwork()) {
            Serial.println(" fail");
            delay(10000);
            return;
        }
        Serial.println(" OK");

        Serial.print(F("Connecting to "));
        Serial.print(APN);
        if (!modem.gprsConnect(APN.c_str(), USERNAME.c_str(), PASSWORD.c_str())) {
            Serial.println(" fail");
            delay(10000);
            return;
        }
        modemConnected = true;
        Serial.println(" OK");
    }
};

TinyGsmClient get_sim_client(){
    return sim_client;
};