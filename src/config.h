#include <string>
#ifndef CONFIG_H
#define CONFIG_H
class Config {
   private:
    static Config *instance;
    Config();

   public:
    std::string device_name;
    std::string pin_code;
    const static int light_pin = 17;
    static Config *get_config();

    class GPS {
       public:
        const static unsigned short RX_PIN = 2;
        const static unsigned short TX_PIN = 15;
    };
};

#endif