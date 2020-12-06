#include <Arduino.h>
#include <config.h>

#include <chrono>
#include <string>

#include "controllers/light_main.h"
#include "models/bt_cmd.h"
#include "models/movement_record.h"

std::string hello_listener(std::string parm) {
    Serial.printf("hello # parm: %s\n", parm.c_str());
    return "";
}
void setup() {
    Serial.begin(115200);
    LightMain::setup();
    BtCMD::get_instance()->add_event_listener("hello", hello_listener);
}
int i = 0;

void loop() {
    BtCMD::get_instance()->process();
    LightMain::loop();
}