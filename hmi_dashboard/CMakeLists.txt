# hmi_dashboard/CMakeLists.txt

# Qt6 Paketlerini Bul
find_package(Qt6 REQUIRED COMPONENTS Core Quick Gui Network)

# --- KRİTİK AYAR ---
# Bu ayar, projedeki Q_OBJECT içeren dosyaları otomatik bulup MOC'lar.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# -------------------

# Header yolları
include_directories(
    ${CMAKE_SOURCE_DIR}/common/include
    src
)

# QML Dosyalarını Tanımla
set(QML_FILES
    qml/Dashboard.qml
)

# Kaynak kodları topla
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Executable oluştur
add_executable(hmi_node WIN32 ${SOURCES} ${QML_FILES})

# Qt Kütüphanelerini Linkle
target_link_libraries(hmi_node
    PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Gui
    Qt6::Network
)

# QML klasörünü build dizinine kopyala
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/qml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
