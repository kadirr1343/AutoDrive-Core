#ifndef CAN_RECEIVER_H
#define CAN_RECEIVER_H

#include "VehicleData.h"
#include <netinet/in.h>

class CANReceiver {
public:
    CANReceiver();
    ~CANReceiver();

    // Veri gelene kadar bekler (Blocking) ve veriyi döndürür
    bool receiveFrame(VehicleData& outData);

private:
    int sock_fd;
    struct sockaddr_in my_addr;
};

#endif
