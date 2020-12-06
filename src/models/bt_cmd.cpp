#include "bt_cmd.h"

#include <map>
#include <sstream>
#include <string>

#include "config.h"
BtCMD::BtCMD() {
    this->serial.begin(Config::get_config()->device_name.c_str());
}
BtCMD* BtCMD::get_instance() {
    if (BtCMD::instance == NULL) {
        BtCMD::instance = new BtCMD();
    }
    return BtCMD::instance;
}
BtCMD* BtCMD::instance = NULL;

void BtCMD::add_event_listener(std::string cmd, std::string (*listener)(std::string parm)) {
    BtCMD::get_instance()->actions[cmd] = listener;
}

bool BtCMD::process() {
    if (!this->serial.available()) return 0;
    std::string buf;
    if (this->serial.read() != 0x2) {
        Serial.println("broken pipe!");
        return false;
    }
    while (true) {
        for (int i = 0; (!this->serial.available()) && i < this->READ_TIMEOUT; i++) {
            delay(1);
        }
        if (!this->serial.available()) return 0;
        long long c = serial.read();
        if (c == 0x3) break;
        buf += c;
    }
    std::stringstream ss;
    std::string cmd;
    std::string parm;
    ss << buf;
    ss >> cmd;
    while (ss >> parm) {
        parm += " ";
    };
    if (parm[parm.length() - 1] == ' ') {
        parm = parm.substr(0, parm.length() - 1);
    }
    if (this->actions.find(cmd) != this->actions.end()) {
        Serial.println("command found!");
        Serial.println(cmd.c_str());
        Serial.println("");
        (*(this->actions[cmd]))(parm);
    } else {

    }
    std::string s;
    Serial.println(buf.c_str());
    return true;
}
void BtCMD::send_command(std::string cmd, std::string parm) {
    std::string q = (char)0x2 + cmd + " " + parm + (char)0x3;
    this->serial.print(q.c_str());
}