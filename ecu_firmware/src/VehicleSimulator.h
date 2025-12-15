#ifndef VEHICLE_SIMULATOR_H
#define VEHICLE_SIMULATOR_H

#include "VehicleData.h"

class VehicleSimulator {
public:
    VehicleSimulator();
    
    // Aracı bir adım (tick) ilerletir
    void update();

    // Güncel veriyi döndürür
    VehicleData getData() const;

private:
    float current_speed;
    float current_rpm;
    float current_temp;
    bool accelerating; // Hızlanıyor mu yavaşlıyor mu?

    void checkSafety(); // Sıcaklık kontrolü
};

#endif
