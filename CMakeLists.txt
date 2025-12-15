cmake_minimum_required(VERSION 3.16)

project(AutoDrive-Core VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

add_subdirectory(ecu_firmware)
add_subdirectory(hmi_dashboard)