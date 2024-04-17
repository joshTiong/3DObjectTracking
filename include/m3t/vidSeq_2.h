#include <filesystem/filesystem.h>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

class vidSeq {
 public:
  void vidSeq_func(std::string seqImg_name, std::filesystem::path video_path) {
    std::string save_path =
                    "/home/jtiong/objectTracking/data_all/sequenceImg/";

    cv::VideoCapture video(video_path);

    // Check if camera opened successfully
    if (!video.isOpened()) {
      std::cout << "Error opening video stream or file" << std::endl;
      abort();
    }

    int frame_max = video.get(cv::CAP_PROP_FRAME_COUNT);

    for (int j = 0; j < frame_max; j++) {
      cv::Mat frame;
      video >> frame;

      cv::Mat dst;
      cv::transpose(frame, dst);
      cv::flip(dst, dst, 1);

      // Display the resulting frame
      cv::imwrite(save_path + seqImg_name + std::to_string(j + 200) + ".png",
                  dst);
    }
  }
};