#include "CANReceiver.h"
#include "NetworkConfig.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

CANReceiver::CANReceiver() {
    // UDP Socket oluştur
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "[HMI] Socket hatasi!" << std::endl;
        return;
    }

    // Adres bilgilerini ayarla (Dinleyici olduğumuz için BIND yapacağız)
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY; // Her yerden gelen veriyi kabul et
    my_addr.sin_port = htons(VCAN_PORT);  // Port 3000'i dinle

    // Port'u rezerve et (Bind)
    if (bind(sock_fd, (const struct sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
        std::cerr << "[HMI] Bind hatasi! Port dolu olabilir." << std::endl;
    }
}

CANReceiver::~CANReceiver() {
    if (sock_fd >= 0) close(sock_fd);
}

bool CANReceiver::receiveFrame(VehicleData& outData) {
    // Veri gelene kadar burada bekler (Block olur)
    ssize_t len = recvfrom(sock_fd, &outData, sizeof(VehicleData), 0, NULL, NULL);
    return len == sizeof(VehicleData);
}
