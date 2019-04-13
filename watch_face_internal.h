#ifndef CRYPTIC_WATCH_WATCH_FACE_INTERNAL_H
#define CRYPTIC_WATCH_WATCH_FACE_INTERNAL_H

#include "watch_face.h"

typedef Err (*WfInitWatchFaceFunc)(void** internal);

typedef void (*WfDrawTimeFunc)(void* internal, DateTimeType* dt);

typedef UInt32 (*WfGetDataSizeFunc)();

typedef void (*WfFreeFunc)(void* internal);

struct WatchFaceType_ {
  void* internal;
  WfInitWatchFaceFunc InitWatchFace;
  WfDrawTimeFunc DrawTime;
  WfGetDataSizeFunc GetDataSize;
  WfFreeFunc Free;
  UInt32 prefix;
};

#endif  // CRYPTIC_WATCH_WATCH_FACE_INTERNAL_H
