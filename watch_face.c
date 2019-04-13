#include "watch_face.h"
#include "watch_face_internal.h"

Err WfInitWatchFace(WatchFaceType* watchFace) {
  return watchFace->InitWatchFace(&(watchFace->internal));
}

void WfDrawTime(WatchFaceType* watchFace, DateTimeType* dt) {
  watchFace->DrawTime(watchFace->internal, dt);
}

void WfGetDataPtr(WatchFaceType* watchFace, void** data, UInt32* size) {
  *size = watchFace->GetDataSize();
  *data = watchFace->internal;
}

void WfFree(WatchFaceType* watchFace) {
  watchFace->Free(watchFace->internal);
}

Err WfCreateFromRaw(WatchFaceType* watchFace, void* raw) {
  watchFace->internal = raw;
  return errNone;
}

UInt32 WfGetPrefix(WatchFaceType* watchFace) {
  return watchFace->prefix;
}
