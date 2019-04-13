#ifndef CRYPTIC_WATCH_WATCH_FACE_H
#define CRYPTIC_WATCH_WATCH_FACE_H

#include <PalmOS.h>

struct WatchFaceType_;

typedef struct WatchFaceType_ WatchFaceType;

/**
 * Init watch face.
 * @param watchFace Pointer to the watchface object.
 * @return errNone on success, memErrorClass otherwise.
 */
Err WfInitWatchFace(WatchFaceType* watchFace);

/**
 * Create watch face of the given type from the raw memory pointer.
 * @param watchFace Pointer to the watchface object.
 * @param raw Raw pointer to create watch face from.
 * @return errNone on success, memErrorClass otherwise.
 */
Err WfCreateFromRaw(WatchFaceType* watchFace, void* raw);

/**
 * Display the current time on the screen.
 * @param watchFace Pointer to the watchface object.
 * @param dt Current time.
 */
void WfDrawTime(WatchFaceType* watchFace, DateTimeType* dt);

/**
 * Return the raw pointer to the internal watch face data.
 * @param watchFace Pointer to the watchface object.
 * @param [out] data Output data pointer.
 * @param [out] size Size of the internal watchface structure.
 */
void WfGetDataPtr(WatchFaceType* watchFace, void** data, UInt32* size);

/**
 * Free the internal watchface structures
 * @param watchFace Pointer to the watchface object.
 */
void WfDestroy(WatchFaceType* watchFace);

/**
 * Get the char prefix of the watch face to distinguish different watch face
 * types.
 * @param watchFace Pointer to the watchface object.
 * @return Char prefix of the watch face.
 */
UInt32 WfGetPrefix(WatchFaceType* watchFace);

#endif  // CRYPTIC_WATCH_WATCH_FACE_H
