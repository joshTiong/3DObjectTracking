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
  if (argc != 6) {
    std::cerr << "Not enough arguments: Provide camera metafile, body "
                 "metafile, detector metafile, temp directory";
    return -1;
  }
  const std::filesystem::path color_camera_1_metafile_path{argv[1]};
  const std::filesystem::path color_camera_2_metafile_path{argv[2]};
  const std::filesystem::path body_metafile_path{argv[3]};
  const std::filesystem::path detector_metafile_path{argv[4]};
  const std::filesystem::path temp_directory{argv[5]};
  //const std::filesystem::path color_camera_1_cali_path{argv[6]};
  //const std::filesystem::path color_camera_2_cali_path{argv[7]};
  // const std::filesystem::path video_path{argv[5]};

  // Video sequencing via openCV
  // std::cout << "Image sequencing..." << std::endl;
  // vidSeq vidSeq_obj;
  // vidSeq_obj.vidSeq_func("stabilo_fast_", video_path);
  // std::cout << "Image sequencing Done!" << std::endl;
 
  //%%%%%%%%%%%%%%%%%%%%Common Functions/Pointers%%%%%%%%%%%%%%%%%%%%
  auto tracker_ptr{std::make_shared<m3t::Tracker>("tracker")};
  auto renderer_geometry_ptr{
      std::make_shared<m3t::RendererGeometry>("renderer_geometry")};

  //%%%%%%%%%%%%%%%%%%%%Stage 1 : Calibration%%%%%%%%%%%%%%%%%%%%

  //%%%%%%%%%%%%%%%%%%%%Stage 2 : Tracking%%%%%%%%%%%%%%%%%%%%
  // Set up tracker and renderer geometry
  


  // Set up camera
  auto camera_ptr_1{std::make_shared<m3t::LoaderColorCamera>(
      "color_camera_1", color_camera_1_metafile_path)};
  auto camera_ptr_2{std::make_shared<m3t::LoaderColorCamera>(
      "color_camera_2", color_camera_2_metafile_path)};

  // Set up viewers
  auto viewer_ptr_1{std::make_shared<m3t::NormalColorViewer>(
      "viewer_1", camera_ptr_1, renderer_geometry_ptr)};
  tracker_ptr->AddViewer(viewer_ptr_1);
  auto viewer_ptr_2{std::make_shared<m3t::NormalColorViewer>(
      "viewer_2", camera_ptr_2, renderer_geometry_ptr)};
  //tracker_ptr->AddViewer(viewer_ptr_2);

  // Set up body
  auto body_ptr{std::make_shared<m3t::Body>("stabilo", body_metafile_path)};
  renderer_geometry_ptr->AddBody(body_ptr);

  // Set up region mode
  auto region_model_ptr{std::make_shared<m3t::RegionModel>(
      "region_model", body_ptr, temp_directory / "region_model.bin")};

  // Set up region modality
  auto region_modality_ptr_1{std::make_shared<m3t::RegionModality>(
      "region_modality_1", body_ptr, camera_ptr_1, region_model_ptr)};
  auto region_modality_ptr_2{std::make_shared<m3t::RegionModality>(
      "region_modality_2", body_ptr, camera_ptr_2, region_model_ptr)};

  // Set up link
  auto link_ptr_1{std::make_shared<m3t::Link>("link_1", body_ptr)};
  //auto link_ptr_2{std::make_shared<m3t::Link>("link_2", body_ptr)};
  link_ptr_1->AddModality(region_modality_ptr_1);
  link_ptr_1->AddModality(region_modality_ptr_2);
  //link_ptr_2->AddModality(region_modality_ptr_1);
  //link_ptr_2->AddModality(region_modality_ptr_2);
  //link_ptr_1->AddChildLink(link_ptr_2);

  // Set up optimizer
  auto optimizer_ptr{std::make_shared<m3t::Optimizer>("optimizer", link_ptr_1)};
  tracker_ptr->AddOptimizer(optimizer_ptr);

  //  Set up detector
  auto detector_ptr_1{std::make_shared<m3t::ManualDetector>(
      "manual_detector_1", detector_metafile_path, optimizer_ptr,
      camera_ptr_1)};
  tracker_ptr->AddDetector(detector_ptr_1);
  //auto detector_ptr_2{std::make_shared<m3t::ManualDetector>(
  //    "manual_detector_2", detector_metafile_path, optimizer_ptr,
  //    camera_ptr_2)};
  //tracker_ptr->AddDetector(detector_ptr_2);
  //  auto detector_ptr{std::make_shared<m3t::StaticDetector>(
  //      "static_detector", detector_metafile_path, optimizer_ptr)};
  //  tracker_ptr->AddDetector(detector_ptr);

  //Start calibration

  // Start tracking
  if (!tracker_ptr->SetUp()) return -1;
  if (!tracker_ptr->RunTrackerProcess(false, false)) return -1;
  return 0;
}
