#include "nativekeyboardhandler.h"
//#include <xcb/xproto.h>

bool nativeEventFilter(const QByteArray &eventType, void *message, long *) {
  //  if (eventType == "xcb_generic_event_t") {
  //    xcb_generic_event_t *ev = static_cast<xcb_generic_event_t *>(message);
  //    // ...
  //  }
  return false;
}
