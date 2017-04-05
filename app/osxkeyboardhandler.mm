#include "nativekeyboardhandler.h"

#import <AppKit/AppKit.h>
#include <QDebug>

NativeKeyboardHandler::NativeKeyboardHandler() {}

bool NativeKeyboardHandler::nativeEventFilter(const QByteArray &eventType,
                                              void *message, long *) {
  if (eventType == "mac_generic_NSEvent") {
    NSEvent *event = static_cast<NSEvent *>(message);
    if ([event type] == NSKeyDown) {
      NSPasteboard *myPasteboard = [NSPasteboard generalPasteboard];
      NSString *myString = [myPasteboard stringForType:NSPasteboardTypeString];
      qDebug() << QString::fromNSString([event characters]);
      qDebug() << QString::fromNSString(myString);
    }
  }
  return false;
}
