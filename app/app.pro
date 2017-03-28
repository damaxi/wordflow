QT += qml quickcontrols2 sql charts quick

CONFIG += c++11
#CONFIG-=app_bundle

LIBS += -framework AppKit

SOURCES += main.cpp \
    vocabularypresenter.cpp

unit:!macx: {
    SOURCES += linuxkeyboardhandler.cpp
}

macx: {
    OBJECTIVE_SOURCES += osxkeyboardhandler.mm
}

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lwordflow
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lwordflow
else:unix: LIBS += -L$$OUT_PWD/../lib/ -lwordflow

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/release/libwordflow.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/debug/libwordflow.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/release/lib.wordflow
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/debug/lib.wordflow
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lib/libwordflow.a

HEADERS += \
    vocabularypresenter.h \
    nativekeyboardhandler.h

TARGET = wordflow

unix:!macx: {
    target.path = /usr/local/bin
    desktop.path = /usr/share/applications
    desktop.files += dist/wordflow.desktop
    icons.path = /usr/share/icons/hicolor/48x48/apps
    icons.files += dist/wordflow.png

    INSTALLS += target desktop icons
}

win32: {
    RC_ICONS = dist/wordflow.ico
}

macx: {
    ICON = dist/wordflow.icns
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../translate/lib/release/ -ltranslate
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../translate/lib/debug/ -ltranslate
else:unix: LIBS += -L$$OUT_PWD/../translate/lib/ -ltranslate

INCLUDEPATH += $$PWD/../translate/lib
DEPENDPATH += $$PWD/../translate/lib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../translate/lib/release/libtranslate.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../translate/lib/debug/libtranslate.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../translate/lib/release/translate.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../translate/lib/debug/translate.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../translate/lib/libtranslate.a
