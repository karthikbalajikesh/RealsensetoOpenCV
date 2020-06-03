#ifndef DEPTHCAMERA_H
#define DEPTHCAMERA_H
#endif

#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>
#include<librealsense2/rs.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<thread>

using namespace std::chrono;
using namespace rs2;
using namespace cv;

// we will create the Depth Camera Object. This should contain all the functions that we will perform on the depth camera.

// This includes receiving the depth and video frame and the intrinsics.

// This also includes creating a 2D vector of values and converting video frame into depth.


class DepthCamera{

public:

	int width,height; // dimensions of image
	Mat ColorFrame;
	Mat DepthFrame;
	rs2::pipeline pipe;
	rs2::frameset frames;
	rs2::depth_frame* depthptr;
	rs2::video_frame* videoptr;



	// member functions
	DepthCamera();
	void getrs2frame();
	void getRawFrame();
	void getColorFrame();
	void getDepthFrame();
	void getAlignedFrame();
	void convert2openCV();



};
