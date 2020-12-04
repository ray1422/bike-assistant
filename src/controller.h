#ifndef CONTROLLERS_H
#define CONTROLLERS_H
#include <vector>

class Controller {
   public:
    Controller();
    virtual void setup();
    virtual void loop();
};
extern std::vector<Controller*> controllers;
#endif