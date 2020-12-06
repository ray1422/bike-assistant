#include "light_main.h"

#include "config.h"
#include "models/bt_cmd.h"

namespace LightMain {

bool light_is_on = false;  // light is on
const int PIN = Config::light_pin;
using namespace std;
string on_turn(std::string parm) {
    if (parm == "on") {
        Serial.println("Turning on!");
        digitalWrite(PIN, HIGH);
        light_is_on = 1;
    } else if (parm == "off") {
        Serial.println("Turning off!");
        digitalWrite(PIN, LOW);
        light_is_on = 0;
    } else if (parm == "status") {
        BtCMD::get_instance()->send_command("light", "status " + (std::string)(light_is_on ? "on" : "off"));
    }
    return "";
}

void setup() {
    pinMode(PIN, OUTPUT);
    BtCMD::get_instance()->add_event_listener("light", on_turn);
    Serial.println("Setup Light");
}
void loop() {}

}  // namespace LightMain