#include "block_watch_face.h"
#include "watch_face_internal.h"

#define DIGITS_COUNT 10

typedef struct {
  RectangleType rect[2];
} ShapeType;

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
static void* init_watch_face(WatchFaceType* watchFace) {
  ShapeType* shapes;

  shapes = MemPtrNew(sizeof(ShapeType) * DIGITS_COUNT);
  if (shapes == NULL) {
    return NULL;
  }

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

  return shapes;
}

static void draw_shape(ShapeType* shape, UInt16 scale, UInt16 x, UInt16 y) {
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

static Err init(void** internal) {
  if ((*internal = init_watch_face(NULL)) == NULL) {
    return memErrorClass;
  }

  return errNone;
}

static void draw_time(void* internal, DateTimeType* dt) {
  UInt8 hi_hour, lo_hour, hi_minute, lo_minute;
  ShapeType* shapes = (ShapeType*) internal;

  hi_hour = dt->hour / 10;
  lo_hour = dt->hour % 10;
  hi_minute = dt->minute / 10;
  lo_minute = dt->minute % 10;

  WinEraseWindow();

  draw_shape(&(shapes[hi_hour]), 16, 0, 0);
  draw_shape(&(shapes[lo_hour]), 16, 80, 0);
  draw_shape(&(shapes[hi_minute]), 16, 0, 80);
  draw_shape(&(shapes[lo_minute]), 16, 80, 80);
}

static UInt32 get_data_size() {
  return sizeof(ShapeType) * DIGITS_COUNT;
}

static void block_watchface_free(void* internal) {
  MemPtrFree(internal);
}

WatchFaceType* createBlockWatchFace() {
  WatchFaceType* result = MemPtrNew(sizeof (WatchFaceType));
  result->prefix = 'BLOC';
  result->internal = NULL;
  result->GetDataSize = get_data_size;
  result->DrawTime = draw_time;
  result->InitWatchFace = init;
  result->Free = block_watchface_free;
  return result;
}
