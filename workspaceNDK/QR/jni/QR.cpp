#include <jni.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/detection_based_tracker.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/features2d/features2d.hpp>
#include <opencv2/flann/flann.hpp>
//#include <opencv2/calib3d/calib3d.hpp>
//#include <opencv2/ml/ml.hpp>
//#include <opencv2/objdetect/objdetect.hpp>
//#include <opencv2/ocl/ocl.hpp>
//#include <opencv2/photo/photo.hpp>
//#include <opencv2/video/video.hpp>
//#include <opencv2/legacy/legacy.hpp>

#include <zbar.h>
//#include "/usr/include/zbar.h"

#include <string>
#include <vector>
#include <iostream>

#include <android/log.h>

#define LOG_TAG "FaceDetection/DetectionBasedTracker"
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))

using namespace std;
using namespace cv;
using namespace zbar;

inline void vector_Rect_to_Mat(vector<Rect>& v_rect, Mat& mat) {
	mat = Mat(v_rect, true);
}

JNIEXPORT void JNICALL Java_com_example_qr_MainActivity_nativeDetect(
		JNIEnv * jenv, jclass, jlong imageGray) {
	LOGD(
			"Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeDetect enter");
	try {
		vector<Rect> RectFaces;
		//       ((DetectionBasedTracker*)thiz)->process(*((Mat*)imageGray));
		//       ((DetectionBasedTracker*)thiz)->getObjects(RectFaces);
		//       vector_Rect_to_Mat(RectFaces, *((Mat*)faces));

		Mat img = *((Mat*) imageGray);
		Mat imgout;
		cvtColor(img, imgout, CV_GRAY2RGB);
		int width = img.cols;
		int height = img.rows;
		uchar *raw = (uchar *) img.data;
//		uchar *raw = (uchar *) imageGray;
		// wrap image data
		Image image(width, height, "Y800", raw, width * height);
		// scan the image for barcodes
		ImageScanner scanner;
		scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

		int n = scanner.scan(image);
		// extract results
		for (Image::SymbolIterator symbol = image.symbol_begin();
				symbol != image.symbol_end(); ++symbol) {
			vector<Point> vp;
			// do something useful with results
			cout << "decoded " << symbol->get_type_name() << " symbol \""
					<< symbol->get_data() << '"' << " " << endl;
			int n = symbol->get_location_size();
			for (int i = 0; i < n; i++) {
				vp.push_back(
						Point(symbol->get_location_x(i),
								symbol->get_location_y(i)));

			}
			RotatedRect r = minAreaRect(vp);
			Point2f pts[4];
			r.points(pts);
			for (int i = 0; i < 4; i++) {
				line(imgout, pts[i], pts[(i + 1) % 4], Scalar(255, 0, 0), 3);
			}
			cout << "Angle: " << r.angle << endl;
		}
		imshow("imgout.jpg", imgout);
		// clean up
		image.set_data(NULL, 0);
		waitKey();

	} catch (cv::Exception& e) {
		LOGD("nativeCreateObject caught cv::Exception: %s", e.what());
		jclass je = jenv->FindClass("org/opencv/core/CvException");
		if (!je)
			je = jenv->FindClass("java/lang/Exception");
		jenv->ThrowNew(je, e.what());
	} catch (...) {
		LOGD("nativeDetect caught unknown exception");
		jclass je = jenv->FindClass("java/lang/Exception");
		jenv->ThrowNew(je,
				"Unknown exception in JNI code DetectionBasedTracker.nativeDetect()");
	}
	LOGD(
			"Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeDetect exit");
}

