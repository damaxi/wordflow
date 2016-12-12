#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QtQml>
#include <QQuickStyle>
#include <QDebug>
#include <QStandardPaths>
#include "vocabulary.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("Wordflow");
    QGuiApplication::setOrganizationName("damaxi");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

//    QSettings settings;
//    QString style = QQuickStyle::name();
//    style = "Material";
//    if (!style.isEmpty())
//        settings.setValue("style", style);
//    else
//        QQuickStyle::setStyle(settings.value("style").toString());

    QQmlApplicationEngine engine;
    Vocabulary vocabulary;
    engine.rootContext()->setContextProperty("vocabularyImpl", &vocabulary);
    engine.setOfflineStoragePath(
                QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0]);
    qDebug() << engine.offlineStoragePath();
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
