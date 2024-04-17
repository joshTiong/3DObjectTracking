// SPDX-License-Identifier: MIT
// Copyright (c) 2023 Manuel Stoiber, German Aerospace Center (DLR)

#include <filesystem/filesystem.h>
#include <m3t/basic_depth_renderer.h>
#include <m3t/body.h>
#include <m3t/common.h>
#include <m3t/loader_camera.h>
#include <m3t/manual_detector.h>
#include <m3t/normal_viewer.h>
#include <m3t/region_modality.h>
#include <m3t/renderer_geometry.h>
#include <m3t/static_detector.h>
#include <m3t/tracker.h>
#include <m3t/vidSeq_2.h>

#include <Eigen/Geometry>
#include <memory>

int main(int argc, char *argv[]) {
  if (argc != 8) {
    std::cerr << "Not enough arguments: Provide camera metafile, body "
                 "metafile, detector metafile, temp directory";
    return -1;
  }

/**
 * Directory(folders) and path(files) are inputed into std::filesystem::path type variable here. 
 * The paths are inserted in the terminal.
 * Check .txt file in Joshua linux profile for full examples.
 * 
 * color_camera_1_metafile_path{argv[1]} : 
 * camera intrinsics values and image sequence name for camera 1 during tracking(stage 2). color_camera_1.yaml 
 * color_camera_1_metafile_path{argv[2]} : 
 * camera intrinsics values and image sequence name for camera 2 during tracking(stage 2). color_camera_2.yaml
 * body_metafile_path{argv[3]} : 
 * .obj file path for object. stabilo.obj
 * detector_metafile_path{argv[4]} : 
 * manual detector file path. Reference points are manually chosen by clicking. stabilo_manual_detector.yaml
 * temp_directory{argv[5]} : 
 * temp folder directory where region_model.bin is stored. region_model.bin is the data for every viewpoints.
 * color_camera_cali_1_metafile_path{argv[6]} : 
 * camera intrinsics values and image sequence name for camera 1 during calibration(stage 1). color_camera_cali_1.yaml 
 * color_camera_cali_2_metafile_path{argv[7]} :
 * camera intrinsics values and image sequence name for camera 2 during calibration(stage 1). color_camera_cali_1.yaml 
 */
  const std::filesystem::path color_camera_1_metafile_path{argv[1]};
  const std::filesystem::path color_camera_2_metafile_path{argv[2]};
  const std::filesystem::path body_metafile_path{argv[3]};
  const std::filesystem::path detector_metafile_path{argv[4]};
  const std::filesystem::path temp_directory{argv[5]};
  const std::filesystem::path color_camera_cali_1_metafile_path{argv[6]};
  const std::filesystem::path color_camera_cali_2_metafile_path{argv[7]};

 /**
  * Pointers are set up from here. Pointers points to .h files that can access functions in .cpp.
  * Common pointers are first set up in "Common Functions/Pointers".
  * Then pointers used in calibration stage are set up in "Stage 1 : Calibration"
  * Pointers used in tracking stage are set up in "Stage 2 : Tracking"
  * 
  * Stage 1 is set up by :
  * if (!tracker_ptr->SetUp()) return -1;
  * Stage 1 is excuted by calling :
  * if (!tracker_ptr->RunTrackerProcess(loop_cali_track, false, false)) return -1;
 */

  //%%%%%%%%%%%%%%%%%%%%Common Functions/Pointers%%%%%%%%%%%%%%%%%%%%
  // Set up tracker and renderer geometry
  auto tracker_ptr{std::make_shared<m3t::Tracker>("tracker")};
  auto renderer_geometry_ptr{
      std::make_shared<m3t::RendererGeometry>("renderer_geometry")};

  // Set up body
  auto body_ptr{std::make_shared<m3t::Body>("stabilo", body_metafile_path)};
  renderer_geometry_ptr->AddBody(body_ptr);

  // Set up region mode
  auto region_model_ptr{std::make_shared<m3t::RegionModel>(
       "region_model", body_ptr, temp_directory / "region_model.bin")};

  int loop_cali_track = 0;
  //%%%%%%%%%%%%%%%%%%%%Stage 1 : Calibration%%%%%%%%%%%%%%%%%%%%
  // Set up camera
  auto camera_cali_ptr_1{std::make_shared<m3t::LoaderColorCamera>(
      "color_camera_cali_1", color_camera_cali_1_metafile_path)};
  auto camera_cali_ptr_2{std::make_shared<m3t::LoaderColorCamera>(
      "color_camera_cali_2", color_camera_cali_2_metafile_path)};

  // Set up viewers
  auto viewer_cali_ptr_1{std::make_shared<m3t::NormalColorViewer>(
      "viewer_cali_1", camera_cali_ptr_1, renderer_geometry_ptr)};
  auto viewer_cali_ptr_2{std::make_shared<m3t::NormalColorViewer>(
      "viewer_cali_2", camera_cali_ptr_2, renderer_geometry_ptr)};
  //tracker_ptr->AddViewer(viewer_cali_ptr_2);

  // Set up region modality
  auto region_modality_cali_ptr_1{std::make_shared<m3t::RegionModality>(
      "region_modality_cali_1", body_ptr, camera_cali_ptr_1, region_model_ptr)};
  auto region_modality_cali_ptr_2{std::make_shared<m3t::RegionModality>(
      "region_modality_cali_2", body_ptr, camera_cali_ptr_2, region_model_ptr)};

  // Set up link
  auto link_cali_ptr_1{std::make_shared<m3t::Link>("link_cali_1", body_ptr)};
  auto link_cali_ptr_2{std::make_shared<m3t::Link>("link_cali_2", body_ptr)};
  link_cali_ptr_1->AddModality(region_modality_cali_ptr_1);
  link_cali_ptr_2->AddModality(region_modality_cali_ptr_2);

  // Set up optimizer 
  auto optimizer_cali_ptr_1{std::make_shared<m3t::Optimizer>("optimizer_cali_1", link_cali_ptr_1)};
  auto optimizer_cali_ptr_2{std::make_shared<m3t::Optimizer>("optimizer_cali_2", link_cali_ptr_2)};

  //  Set up detector
  auto detector_cali_ptr_1{std::make_shared<m3t::ManualDetector>(
      "manual_detector_cali_1", detector_metafile_path, optimizer_cali_ptr_1, camera_cali_ptr_1)};
  auto detector_cali_ptr_2{std::make_shared<m3t::ManualDetector>(
      "manual_detector_cali_1", detector_metafile_path, optimizer_cali_ptr_2, camera_cali_ptr_2)};

  //  Start calibration of camera 1
  //  set phase number. phase 0 is for calibration of camera 1
  region_modality_cali_ptr_1->set_phaseNum(0);
  optimizer_cali_ptr_1->set_phaseNum(0);
  tracker_ptr->AddViewer(viewer_cali_ptr_1);
  tracker_ptr->AddOptimizer(optimizer_cali_ptr_1);
  tracker_ptr->AddDetector(detector_cali_ptr_1);
  //  set up and excute calibration of camera 1
  if (!tracker_ptr->SetUp()) return -1;
  if (!tracker_ptr->RunTrackerProcess(loop_cali_track, false, false)) return -1;
  std::cout << "Calibration of camera 1 Done!" << std::endl; 
  // save body2world_pose as body2camera1_pose and take its average in body2camera1_avg
  Eigen::Transform<float, 3, Eigen::Affine> body2world_pose = body_ptr->body2world_pose_;
  Eigen::Transform<float, 3, Eigen::Affine> body2camera1_pose = region_modality_cali_ptr_1->body2camera_pose_;
  Eigen::Transform<float, 3, Eigen::Affine> body2camera1_pose_avg = region_modality_cali_ptr_1->body2camera_pose_avg();
  std::cout << "body2camera1_pose = \n" << std::endl << body2camera1_pose.matrix() << std::endl;
  std::cout << "body2camera1_pose_avg = \n" << std::endl << body2camera1_pose_avg.matrix() << std::endl;
  std::cout << "projection_matrix_ = \n" << viewer_cali_ptr_1->getProjectionMatrix() << std::endl;
  cv::destroyWindow("viewer_cali_1");

  //Start calibration of camera 2
  //  set phase number. phase 1 is for calibration of camera 2.
  region_modality_cali_ptr_2->set_phaseNum(1);
  optimizer_cali_ptr_2->set_phaseNum(1);
  tracker_ptr->DeleteViewer("viewer_cali_1");
  tracker_ptr->DeleteOptimizer("optimizer_cali_1");
  tracker_ptr->DeleteDetector("manual_detector_cali_1");
  tracker_ptr->AddViewer(viewer_cali_ptr_2);
  tracker_ptr->AddOptimizer(optimizer_cali_ptr_2);
  tracker_ptr->AddDetector(detector_cali_ptr_2);
  //  set up and excute calibration of camera 2
  if (!tracker_ptr->SetUp()) return -1;
  if (!tracker_ptr->RunTrackerProcess(loop_cali_track, false, false)) return -1;
  std::cout << "Calibration of camera 2 Done!" << std::endl;
  // save body2world_pose as body2camera2_pose and take its average in body2camera2_avg
  // using body2camera1_avg and body2camera2_avg to get camera22body_pose_av
  Eigen::Transform<float, 3, Eigen::Affine> body2camera2_pose = region_modality_cali_ptr_2->body2camera_pose_;;
  Eigen::Transform<float, 3, Eigen::Affine> camera22body_pose = body2camera2_pose.inverse();
  Eigen::Transform<float, 3, Eigen::Affine> body2camera2_pose_avg = region_modality_cali_ptr_2->body2camera_pose_avg();
  Eigen::Transform<float, 3, Eigen::Affine> camera22body_pose_avg = body2camera2_pose_avg.inverse();

  body_ptr->mySet_camera22camera1_pose(body2camera1_pose_avg, camera22body_pose_avg);
  std::cout << "body2camera1_pose = \n" << std::endl << body2camera1_pose.matrix() << std::endl;
  std::cout << "body2camera2_pose = \n" << std::endl << body2camera2_pose.matrix() << std::endl;
  std::cout << "body2camera2_pose_avg = \n" << std::endl << body2camera2_pose_avg.matrix() << std::endl;
  std::cout << "camera22camera1_pose_ = \n" << std::endl << body_ptr->camera22camera1_pose_.matrix() << std::endl;
  std::cout << "projection_matrix_ = \n" << viewer_cali_ptr_2->getProjectionMatrix() << std::endl;
  cv::destroyWindow("viewer_cali_2");

  //Clear all calibration pointers for tracking
  tracker_ptr->ClearOptimizers();
  tracker_ptr->ClearDetectors();
  tracker_ptr->ClearViewers();

  //%%%%%%%%%%%%%%%%%%%%Stage 2 : Tracking%%%%%%%%%%%%%%%%%%%%
  // Set up camera
  auto camera_ptr_1{std::make_shared<m3t::LoaderColorCamera>(
      "color_camera_1", color_camera_1_metafile_path)};
  auto camera_ptr_2{std::make_shared<m3t::LoaderColorCamera>(
      "color_camera_2", color_camera_2_metafile_path)};

  // Set up viewers
  auto viewer_ptr_1{std::make_shared<m3t::NormalColorViewer>(
      "viewer_1", camera_ptr_1, renderer_geometry_ptr)};
  auto viewer_ptr_2{std::make_shared<m3t::NormalColorViewer>(
      "viewer_2", camera_ptr_2, renderer_geometry_ptr)};

  // Set up region modality
  auto region_modality_ptr_1{std::make_shared<m3t::RegionModality>(
      "region_modality_1", body_ptr, camera_ptr_1, region_model_ptr)};
  auto region_modality_ptr_2{std::make_shared<m3t::RegionModality>(
      "region_modality_2", body_ptr, camera_ptr_2, region_model_ptr)};

  // Set up link
  auto link_ptr_1{std::make_shared<m3t::Link>("link_1", body_ptr)};
  auto link_ptr_2{std::make_shared<m3t::Link>("link_2", body_ptr)};
  link_ptr_1->AddModality(region_modality_ptr_1);
  link_ptr_1->AddModality(region_modality_ptr_2);
  //link_ptr_2->AddModality(region_modality_ptr_2);
  //link_ptr_2->AddModality(region_modality_ptr_2);

  // Set up optimizer
  auto optimizer_ptr_1{std::make_shared<m3t::Optimizer>("optimizer_1", link_ptr_1)};
  auto optimizer_ptr_2{std::make_shared<m3t::Optimizer>("optimizer_2", link_ptr_2)};

  // Set up detector
  auto detector_ptr_1{std::make_shared<m3t::ManualDetector>(
      "manual_detector_1", detector_metafile_path, optimizer_ptr_1, camera_ptr_1)};
  auto detector_ptr_2{std::make_shared<m3t::ManualDetector>(
      "manual_detector_2", detector_metafile_path, optimizer_ptr_2, camera_ptr_2)};

  // Start tracking
  // set phase number. phase 2 is for tracking of camera 1.
  region_modality_ptr_1->set_phaseNum(2);
  region_modality_ptr_2->set_phaseNum(2);
  optimizer_ptr_1->set_phaseNum(2);
  tracker_ptr->AddViewer(viewer_ptr_1);
  tracker_ptr->AddViewer(viewer_ptr_2);
  tracker_ptr->AddOptimizer(optimizer_ptr_1);
  tracker_ptr->AddDetector(detector_ptr_1);
  // tracking is set up and excuted 
  if (!tracker_ptr->SetUp()) return -1;
  if (!tracker_ptr->RunTrackerProcess(loop_cali_track, false, false)) return -1;
  return 0;
}
