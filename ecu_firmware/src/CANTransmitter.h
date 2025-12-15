#ifndef CAN_TRANSMITTER_H
#define CAN_TRANSMITTER_H

#include "VehicleData.h"
#include <string>
#include <netinet/in.h> // Linux Socket yapıları

class CANTransmitter {
public:
    CANTransmitter();
    ~CANTransmitter();

    // Veriyi ağa gönderir
    void sendFrame(const VehicleData& data);

private:
    int sock_fd; // Socket File Descriptor
    struct sockaddr_in dest_addr; // Hedef adres bilgisi
};

#endif
