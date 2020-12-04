#include <Arduino.h>
#include <config.h>
#include <models/bt_cmd.h>
#include <models/movement_record.h>

#include <chrono>
#include <string>

#include "controller.h"

MovementRecord mr(Config::GPS::RX_PIN, Config::GPS::TX_PIN);
void setup() {
    Serial.begin(115200);
    for (const auto &c : controllers) {
        c->setup();
    }
}
int i = 0;

std::string hello_listener(std::string parm) {
    Serial.printf("hello # parm: %s\n", parm.c_str());
    BtCMD::get_instance()->send_command("hello", "LUL");
    return "";
}
void loop() {
    for (const auto &c : controllers) {
        c->loop();
    }
    mr.process();
    BtCMD::get_instance()->process();
    BtCMD::Action action("hello", hello_listener);

    // Serial.println(i++);
    // MovementRecord::Record record = mr.get_records().back();
    // Serial.print(Serial.read());
    // Serial.printf("[%10d] speed: %.2f last update: ", i++, record.speed);
    // Serial.print(std::chrono::system_clock::to_time_t(mr.get_last_record_time()));
    // Serial.print("\tnow: ");
    // Serial.println(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
}