#include <filesystem/filesystem.h>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Geometry>

// std::string save_path =
// "/home/jtiong/objectTracking/data_all_stabilo_2camera_caliMove/sequenceImg_compressed_color_camera_2_cali/",
//             video_name = "cali_stabilo_xr_20240105_";

int main() {
  std::vector<std::string> save_path(4);
  std::vector<std::string> frame_name(4);
  std::vector<std::string> video_name(4);
  Eigen::MatrixXi cutOff(4,1);
  save_path[0] =
      "/home/jtiong/objectTracking/data_all_stabilo_2camera/"
      "sequenceImg_color_camera_1_cali_diffDistance_easy_vid5/";
  save_path[1] =
      "/home/jtiong/objectTracking/data_all_stabilo_2camera/"
      "sequenceImg_color_camera_2_cali_diffDistance_easy_vid5/";
  save_path[2] =
      "/home/jtiong/objectTracking/data_all_stabilo_2camera/"
      "sequenceImg_color_camera_1_diffDistance_easy_vid5/";
  save_path[3] =
      "/home/jtiong/objectTracking/data_all_stabilo_2camera/"
      "sequenceImg_color_camera_2_diffDistance_easy_vid5/";
  frame_name[0] = "cali_stabilo_A5_";
  frame_name[1] = "cali_stabilo_xr_";
  frame_name[2] = "track_stabilo_A5_";
  frame_name[3] = "track_stabilo_xr_";
  video_name[0] =
      "/home/jtiong/objectTracking/data_all_stabilo_2camera/2cam_diffDistance_easy/"
      "cali_stabilo_A5_20240116.mp4";
  video_name[1] =
      "/home/jtiong/objectTracking/data_all_stabilo_2camera/2cam_diffDistance_easy/"
      "cali_stabilo_xr_20240116.MOV";
  video_name[2] =
      "/home/jtiong/objectTracking/data_all_stabilo_2camera/2cam_diffDistance_easy/"
      "track_stabilo_A5_20240116_5.mp4";
  video_name[3] =
      "/home/jtiong/objectTracking/data_all_stabilo_2camera/2cam_diffDistance_easy/"
      "track_stabilo_xr_20240116_5.MOV";
    cutOff << 239, 266, 254, 250;

  for (int idx = 0; idx < 4; idx++) {
    cv::VideoCapture video(video_name[idx]);

    // Check if camera opened successfully
    if (!video.isOpened()) {
      std::cout << "Error opening video stream or file" << std::endl;
      return -1;
    }

    std::cout << "idx[" << idx << "]" << std::endl;
    std::cout << save_path[idx] << std::endl;
    int j = 200;
    while (1) {
      cv::Mat frame;
      // Capture frame-by-frame
      video >> frame;

      // If the frame is empty, break immediately
      if (frame.empty()) break;

      //std::cout << save_path[idx] + video_name[idx] << std::endl;
      // Display the resulting frame
      if (j > cutOff(idx,0)-1) {
        imwrite(save_path[idx] + frame_name[idx] + std::to_string(j-cutOff(idx,0)+200) + ".png", frame);
      }
      // imwrite(save_path + video_name + std::to_string(j) + ".png", frame);
      j++;
    }
  }

  return 0;
}
