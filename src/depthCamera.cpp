#include "depthCamera.h"

DepthCamera::DepthCamera():depthptr(NULL),videoptr(NULL){
  pipe = rs2::pipeline();
  width = 640;
  height = 480;
  rs2::config cfg;

    //Add desired streams to configuration
  cfg.enable_stream(RS2_STREAM_DEPTH, width,height, RS2_FORMAT_Z16, 60);
  cfg.enable_stream(RS2_STREAM_COLOR, width,height, RS2_FORMAT_BGR8, 60);

    //Instruct pipeline to start streaming with the requested configuration
  pipe.start(cfg);

  frames = rs2::frameset();

  while(waitKey(1) < 0){
    getrs2frame();
    convert2openCV();
  }

}

// Method to fetch depth and color frame in rs2 format
void DepthCamera::getrs2frame(){
  // This function is just to create the frame objects.
  // Might have parallel functions for converting to cv::Mat for
  // individual frames for the purpose of running as threads.
  frames = pipe.wait_for_frames();
  depth_frame depth = frames.get_depth_frame();
  video_frame video = frames.get_color_frame();
  depthptr = &depth;
  videoptr = &video;
}

// function to create CV::Mat file for color frames
void DepthCamera::convert2openCV(){
  ColorFrame = Mat(Size(width, height), CV_8UC3,
          (void*)videoptr->get_data(), Mat::AUTO_STEP);

  namedWindow("Color Frame" , WINDOW_NORMAL);
  imshow("Color Frame", ColorFrame);
  std::cout<<ColorFrame.at<double>(40,40)<<std::endl;

}

// Checking for the width and height of the frames after grabbing them
void DepthCamera::getRawFrame(){
  auto start = high_resolution_clock::now();
  frames = pipe.wait_for_frames();

  std::thread th1(&DepthCamera::getColorFrame,this);
  std::thread th2(&DepthCamera::getDepthFrame,this);
  th1.join();
  th2.join();

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  std::cout<< "Duration is :"<<duration.count()<<"\n"<<std::endl;
}

// Function using Align to generate Aligned Depth and COlor images
void DepthCamera::getAlignedFrame(){
  rs2::align align_to_color(RS2_STREAM_DEPTH);

  frames = pipe.wait_for_frames();
  frames = align_to_color.process(frames);
  depth_frame depth = frames.get_depth_frame();
  video_frame video = frames.get_color_frame();
  depthptr = &depth;
  std::cout<<"depth : "<<depthptr->get_width()<<"\t"<<depthptr->get_height()<<std::endl;

  std::cout<<video.get_width()<<"\t"<<video.get_height()<<std::endl;
}


// Generating depth frame
void DepthCamera::getDepthFrame(){
  depth_frame depth = frames.get_depth_frame();
  std::cout<<depth.get_width()<<"\t"<<depth.get_height()<<std::endl;
}

// Generating color frame
void DepthCamera::getColorFrame(){
  video_frame video = frames.get_color_frame();
  std::cout<<"video  "<<video.get_width()<<"\t"<<video.get_height()<<std::endl;
}
