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
    img_name = "stabilo_slow_camera1_";

int main() {
  // Initialize first frame
  cv::Mat frame, frame_resized_down;  // frame = cv::imread(img_dir + img_name + "0000.tiff");
  int down_width = 480;
  int down_height = 864;

  // Find .tiff count
  std::vector<std::string> img_count;
  cv::glob(img_dir + "*.png", img_count);
  std::cout << img_count.size() << std::endl;
  int img_countIndexMax = img_count.size();

  // Compression lopp
  for (int i = 0; i < img_countIndexMax; i++) {
    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << i << std::endl;
    std::string img_num = ss.str();
    img_num.erase(std::remove(img_num.begin(), img_num.end(), '\n'),
                  img_num.cend());

    frame = cv::imread(img_dir + img_name + std::to_string(200+i) + ".png");
    if (!frame.data) {
      // no more images
      std::cout << "No more images." << std::endl;
      break;
    }

    if (i % 20 == 0) {
      std::cout << "Compressing... [" << i << "/" << img_countIndexMax << "]"
                << std::endl;
    }

    cv::resize(frame, frame_resized_down, cv::Size(down_width, down_height), cv::INTER_LINEAR);

    cv::imwrite(save_dir + img_name + std::to_string(200+i) + ".png", frame_resized_down,
                {cv::IMWRITE_TIFF_COMPRESSION , 8});
  }

  std::cout << "Compression done!" << std::endl;
  return 0;
}
