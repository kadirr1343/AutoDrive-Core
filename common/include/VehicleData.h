#ifndef VEHICLE_DATA_H
#define VEHICLE_DATA_H

#include <cstdint>

// Bu yapı (struct) ağ üzerinden gönderileceği için
// "Memory Alignment" sorunlarını engellemek adına packed attribute kullanabiliriz
// ama şimdilik basit tutalım.

struct VehicleData {
    float speed_kph;      // Hız (km/h)
    float engine_rpm;     // Motor Devri
    float engine_temp_c;  // Motor Sıcaklığı (Celcius)
    uint8_t battery_lvl;  // Batarya Yüzdesi (0-100)
    bool is_emergency;    // Acil Durum Var mı?
};

#endif // VEHICLE_DATA_H
