#ifndef DASHBOARD_BACKEND_H
#define DASHBOARD_BACKEND_H

#include <QObject>
#include <thread>
#include <atomic>
#include "CANReceiver.h"
#include "VehicleData.h"

class DashboardBackend : public QObject {
    Q_OBJECT
    // QML'in okuyacağı özellikler (Properties)
    // NOTIFY: Değer değişince QML'e haber ver demek.
    Q_PROPERTY(float speed READ speed NOTIFY dataChanged)
    Q_PROPERTY(float rpm READ rpm NOTIFY dataChanged)
    Q_PROPERTY(float temperature READ temperature NOTIFY dataChanged)

public:
    explicit DashboardBackend(QObject *parent = nullptr);
    ~DashboardBackend();

    // Getter Metotları (QML bunları çağırır)
    float speed() const { return m_data.speed_kph; }
    float rpm() const { return m_data.engine_rpm; }
    float temperature() const { return m_data.engine_temp_c; }

signals:
    // QML'i uyaran sinyal
    void dataChanged();

private:
    void workerLoop(); // Arka plan işçisi

    CANReceiver m_receiver;
    VehicleData m_data;
    
    std::thread m_thread;      // Socket dinleyen thread
    std::atomic<bool> m_running; // Thread kontrolü
};

#endif
