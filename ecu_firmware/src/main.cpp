#include <iostream>
#include <iomanip>
#include "VehicleSimulator.h"
#include "CANTransmitter.h" // <--- YENİ

extern "C" {
    #include "FreeRTOS.h"
    #include "task.h"
}

void vSensorTask(void *pvParameters) {
    (void) pvParameters; 

    VehicleSimulator myCar;
    CANTransmitter myRadio; // <--- YENİ: Vericiyi başlat

    for (;;) {
        myCar.update();
        VehicleData data = myCar.getData();

        // 1. Veriyi Ağa Gönder
        myRadio.sendFrame(data);

        // 2. Log Bas (Sadece çalıştığını görmek için)
        std::cout << "[ECU] TX -> Hiz: " << (int)data.speed_kph << " km/h" << std::endl;
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// ... Geri kalan (Hook'lar ve Main) AYNI kalsın ...
extern "C" {
    void vApplicationIdleHook( void ) {}
    void vApplicationTickHook( void ) {}
    void vAssertCalled( void ) {
    std::cerr << "RTOS ASSERT HATASI!" << std::endl;
    exit(1); // Bunu alt satıra alıyoruz
}
}

int main() {
    xTaskCreate(vSensorTask, "SensorTask", 2048, NULL, 1, NULL);
    vTaskStartScheduler();
    return 0;
}
