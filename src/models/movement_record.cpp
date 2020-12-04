#include <SoftwareSerial.h>

#include <chrono>

#include "movement_record.h"

MovementRecord::MovementRecord(int8_t rx_pin, int8_t tx_pin)
    : serial(rx_pin, tx_pin) {
    this->RX_PIN = rx_pin;
    this->TX_PIN = tx_pin;
    // this->serial(rx_pin, tx_pin);
    this->last_record_time = std::chrono::system_clock::now();
    this->set_record_freq_sec(10);
    this->n_records = 0;
}

void MovementRecord::set_record_freq_sec(int sec) {
    this->record_freq = (std::chrono::seconds)sec;
}
std::chrono::system_clock::time_point MovementRecord::get_last_record_time() { return this->last_record_time; }
bool MovementRecord::process() {
    if (((std::chrono::duration_cast<std::chrono::seconds>)(std::chrono::system_clock::now() - this->last_record_time)) >= this->record_freq) {
        while (this->serial.available()) {
            gps.encode(this->serial.read());
        }
        MovementRecord::Record rec;
        rec.direction = gps.course.deg();
        rec.speed = gps.speed.mph();
        rec.lng = gps.location.lng();
        rec.lat = gps.location.lat();
        rec.time = std::chrono::system_clock::now();
        this->records.emplace_back(rec);
        this->last_record_time = std::chrono::system_clock::now();
        // Serial.printf("%.15f km/hr %3.10f, %3.10f\r", gps.speed.kmph(), gps.location.lng(), gps.location.lat());

        return true;
    }
    return false;
}
list<MovementRecord::Record> MovementRecord::get_records() {
    return this->records;
}