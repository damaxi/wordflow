#ifndef MACKEYBOARDHANDLER_H
#define MACKEYBOARDHANDLER_H

#include <QAbstractNativeEventFilter>

class NativeKeyboardHandler : public QAbstractNativeEventFilter {
public:
  NativeKeyboardHandler();
  bool nativeEventFilter(const QByteArray &eventType, void *message,
                         long *) Q_DECL_OVERRIDE;
};

#endif // MACKEYBOARDHANDLER_H
