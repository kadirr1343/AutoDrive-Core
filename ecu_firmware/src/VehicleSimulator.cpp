#include "VehicleSimulator.h"
#include <algorithm> 
#include <iostream> // Log için

VehicleSimulator::VehicleSimulator() 
    : current_speed(0), current_rpm(800), current_temp(25.0f), accelerating(true) {}

void VehicleSimulator::update() {
    // ÖNCE GÜVENLİK KONTROLÜ
    // Eğer motor 110 dereceyi geçtiyse, fizik kurallarını iptal et ve motoru kapat.
    if (current_temp > 110.0f) {
        checkSafety();
        return; // Fonksiyondan çık, hızlanma kodlarını çalıştırma!
    }

    // --- Normal Sürüş Fiziği ---
    if (accelerating) {
        current_speed += 2.5f;
        if (current_speed >= 180.0f) accelerating = false;
    } else {
        current_speed -= 1.5f;
        if (current_speed <= 0.0f) {
            current_speed = 0.0f;
            accelerating = true;
        }
    }

    current_rpm = 800.0f + (current_speed * 30.0f);

    if (current_rpm > 4000) current_temp += 0.5f;
    else current_temp -= 0.2f;
    
    current_temp = std::max(20.0f, current_temp); 
}

void VehicleSimulator::checkSafety() {
    // SAFETY INTERLOCK (Güvenlik Kilidi)
    // Motor aşırı ısındı! RTOS anında müdahale ediyor.
    
    std::cout << "[RTOS CRITICAL] ISI LIMITI ASILDI! MOTOR DURDURULUYOR!" << std::endl;

    current_speed = 0.0f; // Hız anında kesilir
    current_rpm = 0.0f;   // Motor stop eder
    accelerating = false; // Gaz pedalı iptal edilir
    
    // Motor durduğu için soğuma başlar (Hızlı soğuma simülasyonu)
    current_temp -= 2.0f; 
}

VehicleData VehicleSimulator::getData() const {
    VehicleData data;
    data.speed_kph = current_speed;
    data.engine_rpm = current_rpm;
    data.engine_temp_c = current_temp;
    data.battery_lvl = 100;
    
    // 105 derece üstü uyarıdır, 110 derece ise sistemin kapandığı andır.
    data.is_emergency = (current_temp > 105.0f); 
    
    return data;
}
