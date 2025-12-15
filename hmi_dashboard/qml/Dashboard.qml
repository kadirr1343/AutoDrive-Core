import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 800
    height: 480
    visible: true
    title: "AutoDrive Pro Dashboard"
    color: "#121212" // Deep Dark Background

    // --- ACİL DURUM ALARMI (Yanıp Sönen Arka Plan) ---
    Rectangle {
        id: alarmOverlay
        anchors.fill: parent
        color: "#ff0000"
        opacity: 0.0
        z: 0 // En altta ama background'un üstünde

        // Backend'den gelen sıcaklık verisine göre animasyonu tetikle
        // Sıcaklık > 105 ise alarm başlar
        property bool isEmergency: backend.temperature > 105.0

        onIsEmergencyChanged: {
            if (isEmergency) alarmAnim.start()
            else {
                alarmAnim.stop()
                alarmOverlay.opacity = 0
            }
        }

        SequentialAnimation {
            id: alarmAnim
            loops: Animation.Infinite
            PropertyAnimation { target: alarmOverlay; property: "opacity"; to: 0.5; duration: 500 }
            PropertyAnimation { target: alarmOverlay; property: "opacity"; to: 0.0; duration: 500 }
        }
    }

    // --- ANA DÜZEN ---
    ColumnLayout {
        anchors.centerIn: parent
        width: parent.width * 0.8
        spacing: 30

        // BAŞLIK
        Text {
            text: "AUTODRIVE CORE SYSTEM"
            color: "#555"
            font.pixelSize: 16
            font.letterSpacing: 2
            Layout.alignment: Qt.AlignHCenter
        }

        // HIZ GÖSTERGESİ (Büyük Rakam)
        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: -10
            Text {
                text: backend.speed.toFixed(0)
                color: "#00e5ff" // Cyan Neon
                font.pixelSize: 120
                font.bold: true
                font.family: "Arial" // Varsa "Eurostile" gibi fontlar harika olur
                Layout.alignment: Qt.AlignHCenter
            }
            Text {
                text: "KM/H"
                color: "#00e5ff"
                font.pixelSize: 20
                opacity: 0.7
                Layout.alignment: Qt.AlignHCenter
            }
        }

        // RPM BAR (Custom Progress Bar)
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 5
            
            RowLayout {
                Layout.fillWidth: true
                Text { text: "RPM"; color: "white"; font.pixelSize: 14 }
                Item { Layout.fillWidth: true } // Spacer
                Text { 
                    text: backend.rpm.toFixed(0)
                    color: "white"
                    font.pixelSize: 14 
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 20
                color: "#333"
                radius: 4

                Rectangle {
                    width: parent.width * (backend.rpm / 8000.0) // 8000 max devir kabul ettik
                    height: parent.height
                    radius: 4
                    
                    // Renk Animasyonu: Devir arttıkça Yeşilden Kırmızıya döner
                    color: {
                        if (backend.rpm < 4000) return "#00ff00" // Yeşil
                        if (backend.rpm < 6000) return "#ffff00" // Sarı
                        return "#ff0000" // Kırmızı
                    }
                    
                    // Yumuşak geçiş efekti
                    Behavior on width { NumberAnimation { duration: 100 } }
                    Behavior on color { ColorAnimation { duration: 200 } }
                }
            }
        }

        // BİLGİ PANELİ (Sıcaklık ve Batarya)
        RowLayout {
            Layout.fillWidth: true
            spacing: 50
            Layout.alignment: Qt.AlignHCenter

            // Sıcaklık
            RowLayout {
                Text { text: "TEMP:"; color: "#aaa"; font.pixelSize: 18 }
                Text { 
                    text: backend.temperature.toFixed(1) + "°C"
                    color: backend.temperature > 90 ? "red" : "white"
                    font.pixelSize: 24
                    font.bold: true
                }
            }

            // Batarya (Statik şimdilik)
            RowLayout {
                Text { text: "BATT:"; color: "#aaa"; font.pixelSize: 18 }
                Text { 
                    text: "100%"
                    color: "#00ff00"
                    font.pixelSize: 24
                    font.bold: true
                }
            }
        }
    }
}
