#include "DashboardBackend.h"
#include <iostream>

DashboardBackend::DashboardBackend(QObject *parent)
    : QObject(parent), m_running(true) {
    
    // Başlangıç değerleri (Boş)
    m_data = {0.0f, 0.0f, 0.0f, 0, false};

    // Arka plan thread'ini başlat
    // "this" pointer'ını veriyoruz ki workerLoop sınıfın üyelerine erişebilsin.
    m_thread = std::thread(&DashboardBackend::workerLoop, this);
}

DashboardBackend::~DashboardBackend() {
    m_running = false;
    // Thread'in bitmesini bekle (Gerçek projede socket'i de kapatmak gerekir)
    if(m_thread.joinable()) {
        m_thread.detach(); // Şimdilik detach ediyoruz (Hızlı kapanış için)
    }
}

void DashboardBackend::workerLoop() {
    VehicleData tempData;
    std::cout << "[Backend] Dinleme thread'i baslatildi..." << std::endl;

    while (m_running) {
        // receiveFrame BLOKE EDİCİDİR (Veri gelene kadar bekler)
        // Bu yüzden bunu ana UI thread'inde yapamayız, yoksa ekran donar.
        if (m_receiver.receiveFrame(tempData)) {
            
            // Veriyi güncelle
            m_data = tempData;

            // KRİTİK NOKTA: QML'e "Veri Değişti" sinyali gönder.
            // Qt sinyalleri thread-safe'dir (farklı thread'den atılabilir).
            emit dataChanged();
        }
    }
}
