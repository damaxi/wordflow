#include "nativekeyboardhandler.h"

#import <AppKit/AppKit.h>
#include <QDebug>

NativeKeyboardHandler::NativeKeyboardHandler() {}

bool NativeKeyboardHandler::nativeEventFilter(const QByteArray &eventType,
                                              void *message, long *) {
  if (eventType == "mac_generic_NSEvent") {
    NSEvent *event = static_cast<NSEvent *>(message);
    if ([event type] == NSKeyDown) {
      // Handle key event
      //      NSInteger currentChangeCount = [pasteboard changeCount];
      //      if (currentChangeCount == lastChangeCount)
      //        return;
      //      NSLog(@"Pasteboard changed: %@", [pasteboard types]);
      qDebug() << QString::fromNSString([event characters]);
    }
  }
  return false;
}
