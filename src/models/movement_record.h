#ifndef MOVEMENT_RECORD_H
#define MOVEMENT_RECORD_H
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#include <chrono>
#include <list>
using std::list;

class MovementRecord {
   public:
    MovementRecord(int8_t, int8_t);
    void set_record_freq_sec(int);
    std::chrono::system_clock::time_point get_last_record_time();
    bool process();  // put in loop
    struct Record {
        double lng;
        double lat;    // 精度 緯度
        double speed;  // in kph
        double direction;
        std::chrono::system_clock::time_point time;
    };
    list<Record> get_records();

   private:
    SoftwareSerial serial;
    TinyGPSPlus gps;
    int8_t RX_PIN, TX_PIN;
    std::chrono::system_clock::time_point last_record_time;
    int n_records;
    std::chrono::seconds record_freq;
    list<Record> records;
};

#endif
