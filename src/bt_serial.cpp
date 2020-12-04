// #include <BluetoothSerial.h>
// #include <WiFi.h>

// #include "config.h"

// BluetoothSerial SerialBT;  //宣告藍芽物件=SerialBT

// void setup() {
//     // put your setup code here, to run once:
//     WiFi.mode(WIFI_OFF);
//     Serial.begin(115200);  //序列視窗
//     SerialBT.begin(Config::get_config()->device_name.c_str());
//     Config *config = Config::get_config();
//     Serial.println(config->device_name.c_str());
//     // pinMode(4, OUTPUT);         //風扇relay
//     // pinMode(16, OUTPUT);        //電燈relay
// }

// void loop() {
//     if (SerialBT.available()) {
//         Serial.println("");
//     }
//     while (SerialBT.available()) {
//         char btdata = SerialBT.read();
//         Serial.print(btdata);  //查看藍芽輸入的值
//     }
//     while (Serial.available()) {
//         SerialBT.print((char)Serial.read());
//     }
//     //   delay(100);
// }
