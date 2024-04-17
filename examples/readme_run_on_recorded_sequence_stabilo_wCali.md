## run_on_recorded_sequence_stabilo_wCali.cpp

### Introduction
This .cpp file excutes the tracking of stabilo pen using camera 1 with transformation of camera 2 to camera 1. This results in two perspectives during tracking of stabilo pen. The transformation matrix is obtained in stage 1 : calibration. 
Additional perspective is added by adding modality of each perspective into the link. For example, 
link_ptr_1->AddModality(region_modality_ptr_1);
link_ptr_1->AddModality(region_modality_ptr_2);
in run_on_recorded_sequence_stabilo_wCali.cpp

### Edited .h and .cpp files in \include and \src
Some functions in \include and \src with name "my...." are new functions made. Some functions are edited from its original code without making a new function("my...").
Functions are initialized in .h files and its contents are in .cpp files. For example, mySet_camera22camera1_pose(~) are initialized in body.h and its contents are in Body::mySet_camera22camera1_pose(~) of body.cpp.

1. body.h : mySet_camera22camera1_pose()
2. region_model.h : myGetClosestView()
3. region_modality.h : set_phaseNum(), CalculateCorrespondences(), CalculateGradientAndHessian(), PrecalculateIterationDependentVariables()
4. link.h : myUpdatePoses()
5. optimizer.h : myCalculateConsistentPoses(), myUpdatePoses()

### Other additional supplement .cpp files
1. vidSeq_2.cpp : process a video file into image sequence files that are saved in a defined folder.
2. imgCompress.cpp : compress image sequence files in a smaller dimensions(width and height)
3. imgCompress_rotation.cpp : compress image sequence files in a smaller dimensions(width and height) and rotates the images.
4. imgCali.cpp : change name or image type(.png, .tiff, etc) of image sequence files.

### Image sequence files and .yaml, .obj location
Image sequence files, .yaml files and .obj files are located in "data_all_..." folder. For example, "data_all_stabilo_2camera".
"sequenceImg_..." folders holds the image sequence files.
