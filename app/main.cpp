#include <QGuiApplication>
#include <QSysInfo>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QtQml>
#include <QQuickStyle>
#include <QDebug>
#include <QStandardPaths>
#include "vocabularypresenter.h"
#include "sqlwordsmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("Wordflow");
    QGuiApplication::setOrganizationName("damaxi");
    QString osType = QSysInfo::productType();
    if (osType == "macos" || osType == "osx")
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<SqlWordsModel>("io.github.damaxi", 1, 0, "WordsModel");
//    QSettings settings;
//    QString style = QQuickStyle::name();
//    style = "Material";
//    if (!style.isEmpty())
//        settings.setValue("style", style);
//    else
//        QQuickStyle::setStyle(settings.value("style").toString());

    QQmlApplicationEngine engine;
    VocabularyPresenter vocabulary;
    engine.rootContext()->setContextProperty("vocabularyImpl", &vocabulary);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
