#include <filesystem/filesystem.h>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <sstream>
#include <string>

// Initialize Directories
std::string
    save_dir =
        "/home/jtiong/objectTracking/data_all_stabilo_2camera/sequenceImg_compressed_color_camera_1_cali/",
    //video_name = "test_output_",
    img_dir = "/home/jtiong/objectTracking/data_all_stabilo_2camera/sequenceImg_compressed_color_camera_1_cali/",
    img_name = "cali_stabilo_A5_20231218_";

int main() {
  // Initialize first frame
  cv::Mat frame, frame_rot;  // frame = cv::imread(img_dir + img_name + "0000.tiff");
  //int down_width = 480;
  //int down_height = 864;

  // Find .tiff count
  std::vector<std::string> img_count;
  cv::glob(img_dir + "*.png", img_count);
  std::cout << img_count.size() << std::endl;
  int img_countIndexMax = img_count.size();

  double angle = 180;

  // Compression lopp
  for (int i = 0; i < img_countIndexMax; i++) {
    //std::stringstream ss;
    //ss << std::setw(4) << std::setfill('0') << i << std::endl;
    //std::string img_num = ss.str();
    //img_num.erase(std::remove(img_num.begin(), img_num.end(), '\n'),
    //              img_num.cend());

    frame = cv::imread(img_dir + img_name + std::to_string(200+i) + ".png");
    cv::Point2f center((frame.cols - 1) / 2.0, (frame.rows - 1) / 2.0);
    cv::Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0);
    if (!frame.data) {
      // no more images
      std::cout << "No more images." << std::endl;
      break;
    }

    if (i % 20 == 0) {
      std::cout << "Rotating... [" << i << "/" << img_countIndexMax << "]"
                << std::endl;
    }
    warpAffine(frame, frame_rot, rotation_matix, frame.size());
    //cv::resize(frame, frame_resized_down, cv::Size(down_width, down_height), cv::INTER_LINEAR);

    cv::imwrite(save_dir + img_name + std::to_string(200+i) + ".png", frame_rot);
  }

  std::cout << "Rotation done!" << std::endl;
  return 0;
}
