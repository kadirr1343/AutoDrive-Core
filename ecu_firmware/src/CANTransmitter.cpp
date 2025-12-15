#include "CANTransmitter.h"
#include "NetworkConfig.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

CANTransmitter::CANTransmitter() {
    // 1. UDP Soketi oluştur (SOCK_DGRAM = UDP)
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "[ECU] Socket olusturulamadi!" << std::endl;
        return;
    }

    // 2. Hedef adresi ayarla
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(VCAN_PORT); // Port 3000
    dest_addr.sin_addr.s_addr = inet_addr(VCAN_IP_ADDRESS); // 127.0.0.1
}

CANTransmitter::~CANTransmitter() {
    if (sock_fd >= 0) {
        close(sock_fd);
    }
}

void CANTransmitter::sendFrame(const VehicleData& data) {
    // Veriyi "struct" boyutu kadar doğrudan gönderiyoruz (Raw Byte Send)
    sendto(sock_fd, 
           &data, 
           sizeof(VehicleData), 
           0, 
           (const struct sockaddr *)&dest_addr, 
           sizeof(dest_addr));
}
