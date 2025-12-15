#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext> // <--- YENİ: Context Erişimi İçin
#include <iostream>
#include "DashboardBackend.h" // <--- YENİ: Sınıfımızı ekledik

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    // Backend Sınıfımızı Örneklendiriyoruz
    DashboardBackend myBackend;

    QQmlApplicationEngine engine;

    // --- ENJEKSİYON ---
    // QML tarafında "backend" kelimesi artık bizim C++ nesnemizi temsil edecek.
    engine.rootContext()->setContextProperty("backend", &myBackend);
    // ------------------
    
    const QUrl url(u"qml/Dashboard.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
