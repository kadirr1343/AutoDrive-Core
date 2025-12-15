# AutoDrive Core - Heterogeneous Vehicle Control System

![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20FreeRTOS-lightgrey.svg)
![GUI](https://img.shields.io/badge/GUI-Qt6%20%2F%20QML-green.svg)
![Build](https://img.shields.io/badge/Build-CMake-orange.svg)

**AutoDrive Core** is a simulation of a modern automotive Electronic Control Unit (ECU) architecture demonstrating **Heterogeneous Computing**. It bridges the gap between Hard Real-Time constraints (RTOS) and high-level HMI visualization (Linux/Qt).

---

## 🏗 Architecture Overview

The project simulates a "Vehicle Gateway" architecture consisting of two distinct nodes communicating via **UDP Sockets (Simulating CAN Bus)**.

### 1. The Safety Controller (ECU Node)
* **Kernel:** Runs on a **FreeRTOS** simulation (Linux Port).
* **Role:** Handles "Hard Real-Time" tasks such as sensor fusion and safety interlocks.
* **Safety Feature:** Implements an automatic engine cutoff mechanism if the temperature exceeds **110°C**, overriding all user inputs.
* **Physics Engine:** Simulates vehicle dynamics (Speed, RPM, Thermal dynamics).

### 2. The Cockpit (HMI Node)
* **Framework:** Built with **Qt 6 & QML**.
* **Role:** Visualizes real-time telemetry data received via IPC.
* **Concurrency:** Uses `std::thread` for non-blocking UDP listening while maintaining a fluid 60 FPS UI.
* **Features:** Reactive RPM bar, dynamic emergency alarms, and modern cyberpunk aesthetics.

---

## 🛠 Tech Stack

| Component | Technology Used |
|-----------|----------------|
| **Languages** | C++17, C, QML |
| **Real-Time OS** | FreeRTOS Kernel (v10.x) |
| **UI Framework** | Qt 6.5+ (Qt Quick) |
| **Networking** | BSD Sockets (UDP/IP) |
| **Concurrency** | `std::thread`, `std::atomic`, FreeRTOS Tasks |
| **Build System** | CMake |

---

## 🚀 How to Build & Run

### Prerequisites (Ubuntu/Debian)
Ensure you have C++ compilers, CMake, and Qt6 libraries installed:
```bash
sudo apt update
sudo apt install build-essential cmake qt6-base-dev qt6-declarative-dev qml6-module-qtquick-layouts
```
Installation
```
git clone [https://github.com/kadirr1343/AutoDrive-Core.git](https://github.com/kadirr1343/AutoDrive-Core.git)
cd AutoDrive-Core
```
Build Process
The project uses a Monorepo structure. You can build both nodes with a single command:
```
mkdir build && cd build
cmake ..
make
```
Running the System
You need two terminal windows to observe the full interaction:

Terminal 1: Start the Dashboard
```
cd hmi_dashboard
./hmi_node
```
Terminal 2: Start the ECU (Engine)
```
# From the 'build' directory
./ecu_firmware/ecu_node
```

##📜 License

This project is open-source and available under the MIT License.
