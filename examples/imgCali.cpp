#include <filesystem/filesystem.h>
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

std::string save_dir = "/home/jtiong/objectTracking/data_all_stabilo_2camera/sequenceImg_compressed_color_camera_2_cali/",
            img_name = "stabilo_slow_camera_2_",
            img_dir = "/home/jtiong/objectTracking/data_all_stabilo_2camera/sequenceImg_compressed_color_camera_2_cali/";

int main(){

    int imgNum = 600;
    cv::Mat frame = cv::imread(img_dir + img_name + std::to_string(200) + ".png");

    std::cout << "Duplicating image for calibration..." << std::endl;

    for (int i = 1; i<imgNum; i++){
        cv::imwrite(save_dir + img_name + std::to_string(200+i) + ".png", frame);
    } 

    std::cout << "Done!" << std::endl;
    return 0;
} 