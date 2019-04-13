#include <DateTime.h>
#include <PalmOS.h>
#include <StringMgr.h>

#include "HAL.h"

#include "WristPDA.h"
#include "res.h"

// NOTE: This program uses *NO* global variables!  Do not introduce any!
//       This program supports custom launch codes and is launched in
//       contexts where global variables are not available.

// All code from here to end of file should use no global variables
#pragma warn_a5_access on

#define FEATURE_CREATOR 'Leyf'
#define FEATURE_GLOBAL_DATA_POINTER 'CW'

typedef struct {
  RectangleType rect[2];
} ShapeType;

typedef struct {
  ShapeType shapes[10];
} WatchGlobalsType;

#define FILL_RECT(RECT, X, Y, W, H) \
  {                                 \
    RECT.topLeft.x = X;             \
    RECT.topLeft.y = Y;             \
    RECT.extent.x = W;              \
    RECT.extent.y = H;              \
  }

/**
 * @brief Initialize digit shapes.
 * @return Pointer to array of the digit shapes on success, NULL otherwise.
 */
MemPtr fill_digit_shapes() {
  WatchGlobalsType* gP;
  ShapeType* shapes;

  // Check if we have already allocated global memory
  gP = NULL;
  if (FtrGet(FEATURE_CREATOR, FEATURE_GLOBAL_DATA_POINTER, (UInt32*) &gP) == 0) {
    if (gP != NULL) {
      return gP;
    }
  }

  if (FtrPtrNew(FEATURE_CREATOR, FEATURE_GLOBAL_DATA_POINTER, sizeof(WatchGlobalsType), (void**) &gP) == 0) {
    int res;
    WatchGlobalsType* data = MemPtrNew(sizeof(WatchGlobalsType));
    shapes = data->shapes;
    FILL_RECT(shapes[0].rect[0], 1, 1, 2, 3)
    FILL_RECT(shapes[0].rect[1], 1, 1, 2, 3)
    FILL_RECT(shapes[1].rect[0], 0, 0, 3, 5)
    FILL_RECT(shapes[1].rect[1], 0, 0, 3, 5)
    FILL_RECT(shapes[2].rect[0], 0, 1, 3, 1)
    FILL_RECT(shapes[2].rect[1], 2, 3, 3, 1)
    FILL_RECT(shapes[3].rect[0], 0, 1, 3, 1)
    FILL_RECT(shapes[3].rect[1], 0, 3, 3, 1)
    FILL_RECT(shapes[4].rect[0], 1, 0, 2, 2)
    FILL_RECT(shapes[4].rect[1], 0, 3, 3, 2)
    FILL_RECT(shapes[5].rect[0], 2, 1, 3, 1)
    FILL_RECT(shapes[5].rect[1], 0, 3, 3, 1)
    FILL_RECT(shapes[6].rect[0], 2, 1, 3, 1)
    FILL_RECT(shapes[6].rect[1], 2, 3, 2, 1)
    FILL_RECT(shapes[7].rect[0], 0, 1, 3, 4)
    FILL_RECT(shapes[7].rect[1], 0, 1, 3, 4)
    FILL_RECT(shapes[8].rect[0], 1, 1, 2, 1)
    FILL_RECT(shapes[8].rect[1], 1, 3, 2, 1)
    FILL_RECT(shapes[9].rect[0], 1, 1, 2, 1)
    FILL_RECT(shapes[9].rect[1], 0, 3, 3, 1)

    res = DmWrite(gP, 0, data, sizeof(WatchGlobalsType));
    MemPtrFree(data);
    if (res == 0) {
      return gP;
    }
  }

  return NULL;
}

void draw_shape(ShapeType* shape, UInt16 scale, UInt16 x, UInt16 y) {
  RectangleType buf;
  int i = 0;
  for (; i < 2; ++i) {
    MemMove(&buf, &(shape->rect[i]), sizeof(RectangleType));
    buf.topLeft.x *= scale;
    buf.topLeft.y *= scale;
    buf.topLeft.x += x;
    buf.topLeft.y += y;
    buf.extent.x *= scale;
    buf.extent.y *= scale;
    WinDrawRectangle(&buf, 0);
  }
}

void draw_time() {
  DateTimeType dt;
  UInt8 hi_hour, lo_hour, hi_minute, lo_minute;
  WatchGlobalsType* gP;
  UInt32 seconds = TimGetSeconds();
  TimSecondsToDateTime(seconds, &dt);
  hi_hour = dt.hour / 10;
  lo_hour = dt.hour % 10;
  hi_minute = dt.minute / 10;
  lo_minute = dt.minute % 10;

  WinEraseWindow();
  gP = fill_digit_shapes();

  if (gP == NULL) {
    return;
  }

  draw_shape(&(gP->shapes[hi_hour]), 16, 0, 0);
  draw_shape(&(gP->shapes[lo_hour]), 16, 80, 0);
  draw_shape(&(gP->shapes[hi_minute]), 16, 0, 80);
  draw_shape(&(gP->shapes[lo_minute]), 16, 80, 80);
}

void app_handle_event(EventPtr event) {
  switch (event->eType) {
    case nilEvent: {
      draw_time();
      break;
    }
    case keyDownEvent: {
      if ((event->data.keyDown.chr == vchrThumbWheelBack) || (event->data.keyDown.chr == vchrThumbWheelPush)) {
        // Translate the Back and Enter keys to an open launcher event.
        EventType newEvent;
        newEvent = *event;
        newEvent.eType = ctlSelectEvent;
        newEvent.tapCount = 1;
        newEvent.eType = keyDownEvent;
        newEvent.data.keyDown.chr = launchChr;
        newEvent.data.keyDown.modifiers = commandKeyMask;
        EvtAddEventToQueue(&newEvent);
      }
      break;
    }
  }
}

void event_loop() {
  EventType event;
  UInt32 delay = SysTicksPerSecond();
  do {
    EvtGetEvent(&event, delay);
    if (!SysHandleEvent(&event)) {
      app_handle_event(&event);
    }
  } while (event.eType != appStopEvent);
}

UInt32 PilotMain(UInt16 cmd, void* cmdPBP, UInt16 launchFlags) {
  switch (cmd) {
    // Normal application launch
    case sysAppLaunchCmdNormalLaunch: {
      draw_time();
      event_loop();
      break;
    }
    // Launch application in watch mode
    case wpdaAppLaunchWatchDrawTime: {
      draw_time();
      break;
    }
    case sysAppLaunchCmdNotify: {
      SysNotifyParamType* pNotify = (SysNotifyParamType*) cmdPBP;
      if (pNotify->notifyType == fossilNotifyWatchModeWakeup) {
        // Exit when receive this notification.
        EventType Event;
        MemSet(&Event, sizeof(Event), 0);
        Event.eType = appStopEvent;
        EvtAddEventToQueue(&Event);
      }
      break;
    }
  }
  return 0;
}

// Turn a5 warning off to prevent it being set off by C++
// static initializer code generation
#pragma warn_a5_access reset
