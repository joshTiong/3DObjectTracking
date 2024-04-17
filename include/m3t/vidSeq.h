#include <filesystem/filesystem.h>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

class vidSeq {
 public:
  void vidSeq_func(std::filesystem::path video_path) {
    std::string save_path =
                    "/home/jtiong/objectTracking/data_all/sequenceImg/",
                seqImg_name = "stabilo_fast_";

    cv::VideoCapture video(video_path);

    // Check if camera opened successfully
    if (!video.isOpened()) {
      std::cout << "Error opening video stream or file" << std::endl;
      abort();
    }

    int j = 0;

    while (1) {
      cv::Mat frame;
      // Capture frame-by-frame
      video >> frame;

      // If the frame is empty, break immediately
      if (frame.empty()) break;

      imshow("frame", frame);
      // Display the resulting frame
      imwrite(save_path + seqImg_name + std::to_string(j+200) + ".png", frame);
      j++;
    }

    // When everything done, release the video capture object
    video.release();
  }
};