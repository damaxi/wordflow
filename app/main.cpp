#include <QApplication>
#include <QSysInfo>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QtQml>
#include <QQuickStyle>
#include <QDebug>
#include <QStandardPaths>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include <QQuickWindow>
#include "vocabularypresenter.h"
#include "sqlmodel/sqlwordseditmodel.h"
#include "sqlmodel/sqlvocabularyquerymodel.h"
#include "sqlmodel/sqllearningwordsmodel.h"
#include "sqlmodel/sqlvocabularyeditmodel.h"
#include "model/statisticchartmodel.h"
#include "model/localemodel.h"
#include "helpers/datehelper.h"

#include <QSqlRecord>

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("Wordflow");
    QApplication::setOrganizationName("damaxi");
    QString osType = QSysInfo::productType();
    if (osType == "macos" || osType == "osx")
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("Couldn't detect any system tray"));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    qmlRegisterType<SqlWordsEditModel>("io.github.damaxi", 1, 0, "WordsEditModel");
    qmlRegisterType<SqlVocabularyQueryModel>("io.github.damaxi", 1, 0, "VocabulariesQueryModel");
    qmlRegisterType<SqlLearningWordsModel>("io.github.damaxi", 1, 0, "WordsLearningModel");
    qmlRegisterType<SqlVocabularyEditModel>("io.github.damaxi", 1, 0, "VocabulariesEditModel");
    qmlRegisterType<StatisticChartModel>("io.github.damaxi", 1, 0, "StatisticChartModel");
    qmlRegisterType<LocaleModel>("io.github.damaxi", 1, 0, "LocaleModel");
    qmlRegisterType<DateHelper>("io.github.damaxi", 1, 0, "DateHelper");
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

    QObject *root = nullptr;
    if (engine.rootObjects().isEmpty())
        return -1;
    else
    {
        root = engine.rootObjects().first();
        QQuickWindow *qmlWindow = qobject_cast<QQuickWindow*>(root);

        QAction *minimizeAction = new QAction(QObject::tr("Mi&nimize"), qmlWindow);
        root->connect(minimizeAction, &QAction::triggered, qmlWindow, &QQuickWindow::hide);
        QAction *maximizeAction = new QAction(QObject::tr("Ma&ximize"), qmlWindow);
        root->connect(maximizeAction, &QAction::triggered, qmlWindow, &QQuickWindow::showMaximized);
        QAction *restoreAction = new QAction(QObject::tr("&Restore"), qmlWindow);
        root->connect(restoreAction, &QAction::triggered, qmlWindow, &QQuickWindow::showNormal);
        QAction *quitAction = new QAction(QObject::tr("&Quit"), qmlWindow);
        root->connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

        QMenu *trayIconMenu = new QMenu();
        trayIconMenu->addAction(minimizeAction);
        trayIconMenu->addAction(maximizeAction);
        trayIconMenu->addAction(restoreAction);
        trayIconMenu->addSeparator();
        trayIconMenu->addAction(quitAction);

        QSystemTrayIcon *trayIcon = new QSystemTrayIcon(root);
        trayIcon->setContextMenu(trayIconMenu);
        trayIcon->setIcon(QIcon(":/images/wordflow.png"));
        trayIcon->show();

        qmlWindow->setIcon(QIcon(":/images/wordflow@4x.png"));
    }


    return app.exec();
}
