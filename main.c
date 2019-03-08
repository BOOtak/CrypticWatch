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

#define NUM_DIGITS 10

typedef struct {
  int size;
  RectangleType* rect;
} ShapeType;

#define ALLOC_SHAPE(SHAPE, SIZE)                          \
  {                                                       \
    SHAPE.size = SIZE;                                    \
    SHAPE.rect = MemPtrNew(sizeof(RectangleType) * SIZE); \
  }

#define FILL_RECT(RECT, X, Y, W, H) \
  {                                 \
    RECT.topLeft.x = X;             \
    RECT.topLeft.y = Y;             \
    RECT.extent.x = W;              \
    RECT.extent.y = H;              \
  }

/**
 * @brief Initialize digit shapes.
 * @return Pointer to array of the digit shapes.
 */
MemPtr fill_digit_shapes() {
  ShapeType* shapes = MemPtrNew(NUM_DIGITS * sizeof(ShapeType));
  ALLOC_SHAPE(shapes[0], 1);
  FILL_RECT(shapes[0].rect[0], 1, 1, 2, 3);
  ALLOC_SHAPE(shapes[1], 1);
  FILL_RECT(shapes[1].rect[0], 0, 0, 3, 5);
  ALLOC_SHAPE(shapes[2], 2);
  FILL_RECT(shapes[2].rect[0], 0, 1, 3, 1);
  FILL_RECT(shapes[2].rect[1], 2, 3, 3, 1);
  ALLOC_SHAPE(shapes[3], 2);
  FILL_RECT(shapes[3].rect[0], 0, 1, 3, 1);
  FILL_RECT(shapes[3].rect[1], 0, 3, 3, 1);
  ALLOC_SHAPE(shapes[4], 2);
  FILL_RECT(shapes[4].rect[0], 1, 0, 2, 2);
  FILL_RECT(shapes[4].rect[1], 0, 3, 3, 2);
  ALLOC_SHAPE(shapes[5], 2);
  FILL_RECT(shapes[5].rect[0], 2, 1, 3, 1);
  FILL_RECT(shapes[5].rect[1], 0, 3, 3, 1);
  ALLOC_SHAPE(shapes[6], 2);
  FILL_RECT(shapes[6].rect[0], 2, 1, 3, 1);
  FILL_RECT(shapes[6].rect[1], 2, 3, 2, 1);
  ALLOC_SHAPE(shapes[7], 1);
  FILL_RECT(shapes[7].rect[0], 0, 1, 3, 4);
  ALLOC_SHAPE(shapes[8], 2);
  FILL_RECT(shapes[8].rect[0], 1, 1, 2, 1);
  FILL_RECT(shapes[8].rect[1], 1, 3, 2, 1);
  ALLOC_SHAPE(shapes[9], 2);
  FILL_RECT(shapes[9].rect[0], 1, 1, 2, 1);
  FILL_RECT(shapes[9].rect[1], 0, 3, 3, 1);
  return shapes;
}

int free_digit_shapes(ShapeType* shapes) {
  int i = 0;
  int res = 0;
  for (i; i < NUM_DIGITS; ++i) {
    if (MemPtrFree(shapes[i].rect) != 0) {
      return -1;
    }
  }

  if (MemPtrFree(shapes) != 0) {
    return -1;
  }

  return 0;
}

void draw_shape(ShapeType* shape, UInt16 scale, UInt16 x, UInt16 y) {
  RectangleType buf;
  int i = 0;
  for (i; i < shape->size; ++i) {
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
  IndexedColorType foreColor;
  ShapeType* shapes;
  UInt32 seconds = TimGetSeconds();
  TimSecondsToDateTime(seconds, &dt);
  hi_hour = dt.hour / 10;
  lo_hour = dt.hour % 10;
  hi_minute = dt.minute / 10;
  lo_minute = dt.minute % 10;

  // TODO: store this data in database instead of allocating it each time.
  shapes = fill_digit_shapes();

  WinEraseWindow();

  draw_shape(&shapes[hi_hour], 16, 0, 0);
  draw_shape(&shapes[lo_hour], 16, 80, 0);
  draw_shape(&shapes[hi_minute], 16, 0, 80);
  draw_shape(&shapes[lo_minute], 16, 80, 80);

  free_digit_shapes(shapes);
}

void app_handle_event(EventPtr event) {
  switch (event->eType) {
    case nilEvent: {
      draw_time();
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
      event_loop();
      break;
    }
    // Launch application in watch mode
    case wpdaAppLaunchWatchDrawTime: {
      draw_time();
      break;
    }
  }
  return 0;
}

// Turn a5 warning off to prevent it being set off by C++
// static initializer code generation
#pragma warn_a5_access reset
