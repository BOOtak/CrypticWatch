#include <DateTime.h>
#include <PalmOS.h>
#include <StringMgr.h>

#include "HAL.h"

#include "WristPDA.h"
#include "block_watch_face.h"
#include "res.h"
#include "watch_face.h"

// NOTE: This program uses *NO* global variables!  Do not introduce any!
//       This program supports custom launch codes and is launched in
//       contexts where global variables are not available.

// All code from here to end of file should use no global variables
#pragma warn_a5_access on

#define FEATURE_CREATOR 'Leyf'
#define FEATURE_GLOBAL_DATA_POINTER 'CW'

/**
 * @brief Initialize digit shapes.
 * @return Pointer to array of the digit shapes on success, NULL otherwise.
 */
Err init_watch_face(WatchFaceType* watchFace) {
  void* watch_raw;
  UInt32 watch_size;
  Err res;

  // Check if we have already allocated global memory
  MemPtr gP = NULL;
  if (FtrGet(FEATURE_CREATOR, FEATURE_GLOBAL_DATA_POINTER, (UInt32*) &gP) ==
      0) {
    if (gP != NULL) {
      // TODO: check if this data is compatible with the current watch face
      return WfCreateFromRaw(watchFace, gP);
    }
  }

  WfInitWatchFace(watchFace);
  WfGetDataPtr(watchFace, &watch_raw, &watch_size);

  if (FtrPtrNew(FEATURE_CREATOR, FEATURE_GLOBAL_DATA_POINTER, watch_size,
                (void**) &gP) == 0) {
    res = DmWrite(gP, 0, watch_raw, watch_size);
    MemPtrFree(watch_raw);
    if (res == 0) {
      return WfCreateFromRaw(watchFace, gP);
    }
  }

  return memErrorClass;
}

void draw_time() {
  DateTimeType dt;
  WatchFaceType* watchFace;
  Err init_success;
  UInt32 seconds = TimGetSeconds();
  TimSecondsToDateTime(seconds, &dt);

  watchFace = createBlockWatchFace();
  if (watchFace != NULL) {
    init_success = init_watch_face(watchFace);
    if (init_success == errNone) {
      WfDrawTime(watchFace, &dt);
    }

    MemPtrFree(watchFace);
    return;
  }

  WinDrawLine(0, 0, 160, 160);
  WinDrawLine(0, 160, 160, 0);
}

void app_handle_event(EventPtr event) {
  switch (event->eType) {
    case nilEvent: {
      draw_time();
      break;
    }
    case keyDownEvent: {
      if ((event->data.keyDown.chr == vchrThumbWheelBack) ||
          (event->data.keyDown.chr == vchrThumbWheelPush)) {
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
