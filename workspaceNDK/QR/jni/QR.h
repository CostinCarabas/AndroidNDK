#include <jni.h>
#ifndef _Included_org_opencv_samples_fd_DetectionBasedTracker
#define _Included_org_opencv_samples_fd_DetectionBasedTracker
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     org_opencv_samples_fd_DetectionBasedTracker
 * Method:    nativeDetect
 * Signature: (JJJ)V
 */
JNIEXPORT void JNICALL Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeDetect
  (JNIEnv *, jclass, jlong);
#ifdef __cplusplus
}
#endif
#endif
