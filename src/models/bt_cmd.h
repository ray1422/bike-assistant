#ifndef BT_CMD_H
#define BT_CMD_H
#include <BluetoothSerial.h>

#include <map>
#include <string>

class BtCMD {
   public:
    const int READ_TIMEOUT = 1000000;
    static BtCMD* get_instance();
    bool process();
    class Action {
       public:
        Action(std::string cmd, std::string (*listener)(std::string parm));
        std::string (*listener)(std::string parm);
    };
    void send_command(std::string cmd, std::string parm);    
   private:
    BtCMD();
    BluetoothSerial serial;
    std::map<std::string, BtCMD::Action*> actions;
    static BtCMD* instance;
};
#endif