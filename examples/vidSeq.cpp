#include <filesystem/filesystem.h>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <string>
#include <vector>

std::string save_path = "/home/jtiong/objectTracking/data_all_stabilo_2camera_caliMove/sequenceImg_compressed_color_camera_2_cali/",
            video_name = "cali_stabilo_xr_20240105_";

int main() {
  cv::VideoCapture video(
      "/home/jtiong/objectTracking/data_all_stabilo_2camera_caliMove/caliMove_stabilo_xr_20240105_2.MOV");

  // Check if camera opened successfully
  if (!video.isOpened()) {
    std::cout << "Error opening video stream or file" << std::endl;
    return -1;
  }

  int j = 200;

  while (1) {
    cv::Mat frame;
    // Capture frame-by-frame
    video >> frame;

    // If the frame is empty, break immediately
    if (frame.empty()) break;

    // Display the resulting frame
    if (j > 199){
      imwrite(save_path + video_name + std::to_string(j) + ".png", frame);
    } 
    //imwrite(save_path + video_name + std::to_string(j) + ".png", frame);
    j++;
  }


  return 0;
}
