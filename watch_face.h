#ifndef CRYPTIC_WATCH_WATCH_FACE_H
#define CRYPTIC_WATCH_WATCH_FACE_H

#include <PalmOS.h>

struct WatchFaceType_;

typedef struct WatchFaceType_ WatchFaceType;

Err WfInitWatchFace(WatchFaceType* watchFace);

Err WfCreateFromRaw(WatchFaceType* watchFace, void* raw);

void WfDrawTime(WatchFaceType* watchFace, DateTimeType* dt);

void WfGetDataPtr(WatchFaceType* watchFace, void** data, UInt32* size);

void WfFree(WatchFaceType* watchFace);

UInt32 WfGetPrefix(WatchFaceType* watchFace);

#endif  // CRYPTIC_WATCH_WATCH_FACE_H
