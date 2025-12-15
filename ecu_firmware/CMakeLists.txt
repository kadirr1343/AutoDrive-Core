# ecu_firmware/CMakeLists.txt

# 1. FreeRTOS Yollarını Tanımla
set(FREERTOS_DIR ${CMAKE_SOURCE_DIR}/libs/FreeRTOS-Kernel)
set(FREERTOS_PORT_DIR ${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix)

# 2. Include Yolları (Header dosyaları nerede?)
include_directories(
    ${CMAKE_SOURCE_DIR}/common/include      # <--- YENİ EKLENEN SATIR
    include                                 # config dosyası
    ${FREERTOS_DIR}/include
    ${FREERTOS_PORT_DIR}
    ${FREERTOS_DIR}/portable/MemMang
)

# 3. Kaynak Dosyaları (Source Files)
# Kendi kodlarımız
file(GLOB_RECURSE APP_SOURCES "src/*.cpp")

# FreeRTOS Çekirdek Kodları (Bunlar C dosyalarıdır)
set(FREERTOS_SOURCES
    ${FREERTOS_DIR}/croutine.c
    ${FREERTOS_DIR}/event_groups.c
    ${FREERTOS_DIR}/list.c
    ${FREERTOS_DIR}/queue.c
    ${FREERTOS_DIR}/stream_buffer.c
    ${FREERTOS_DIR}/tasks.c
    ${FREERTOS_DIR}/timers.c
    ${FREERTOS_DIR}/portable/MemMang/heap_3.c    # Standart malloc/free kullanır
    ${FREERTOS_PORT_DIR}/port.c                  # Linux entegrasyonu
    ${FREERTOS_PORT_DIR}/utils/wait_for_event.c
)

# 4. Executable Oluştur
add_executable(ecu_node 
    ${APP_SOURCES} 
    ${FREERTOS_SOURCES}
)

# 5. Linux Thread Kütüphanesini Bağla (Çok Önemli!)
# FreeRTOS Linux üzerinde 'pthread' kullanır.
target_link_libraries(ecu_node pthread)
