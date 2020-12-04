#include <config.h>

#include <cstdio>
#include <string>

Config::Config() {
    this->device_name = "單車助理";
    this->pin_code = "www";
}
Config* Config::get_config() {
    if (Config::instance == NULL) Config::instance = new Config();
    return Config::instance;
};
Config* Config::instance = NULL;