cmake_minimum_required(VERSION 3.5)

#add_executable(evaluate_rbot_dataset evaluate_rbot_dataset.cpp rbot_evaluator.cpp rbot_evaluator.h)
#target_link_libraries(evaluate_rbot_dataset PUBLIC m3t)

#add_executable(parameter_study_rbot_dataset parameter_study_rbot_dataset.cpp rbot_evaluator.cpp rbot_evaluator.h)
#target_link_libraries(parameter_study_rbot_dataset PUBLIC m3t)

#add_executable(evaluate_choi_dataset evaluate_choi_dataset.cpp choi_evaluator.cpp choi_evaluator.h)
#target_link_libraries(evaluate_choi_dataset PUBLIC m3t)

#add_executable(parameter_study_choi_dataset parameter_study_choi_dataset.cpp choi_evaluator.cpp choi_evaluator.h)
#target_link_libraries(parameter_study_choi_dataset PUBLIC m3t)

#add_executable(evaluate_opt_dataset evaluate_opt_dataset.cpp opt_evaluator.cpp opt_evaluator.h)
#target_link_libraries(evaluate_opt_dataset PUBLIC m3t)

#add_executable(parameter_study_opt_dataset parameter_study_opt_dataset.cpp opt_evaluator.cpp opt_evaluator.h)
#target_link_libraries(parameter_study_opt_dataset PUBLIC m3t)

#add_executable(evaluate_ycb_dataset evaluate_ycb_dataset.cpp ycb_evaluator.cpp ycb_evaluator.h)
#target_link_libraries(evaluate_ycb_dataset PUBLIC m3t)

#add_executable(parameter_study_ycb_dataset parameter_study_ycb_dataset.cpp ycb_evaluator.cpp ycb_evaluator.h)
#target_link_libraries(parameter_study_ycb_dataset PUBLIC m3t)

#add_executable(evaluate_rtb_dataset evaluate_rtb_dataset.cpp rtb_evaluator.cpp rtb_evaluator.h)
#target_link_libraries(evaluate_rtb_dataset PUBLIC m3t)

#add_executable(parameter_study_rtb_dataset parameter_study_rtb_dataset.cpp rtb_evaluator.cpp rtb_evaluator.h)
#target_link_libraries(parameter_study_rtb_dataset PUBLIC m3t)

add_executable(run_on_recorded_sequence run_on_recorded_sequence.cpp)
target_link_libraries(run_on_recorded_sequence PUBLIC m3t)

add_executable(run_generated_tracker run_generated_tracker.cpp)
target_link_libraries(run_generated_tracker PUBLIC m3t)

add_executable(run_pen_paper_demo run_pen_paper_demo.cpp)
target_link_libraries(run_pen_paper_demo PUBLIC m3t)

add_executable(constraint_convergence constraint_convergence.cpp)
target_link_libraries(constraint_convergence PUBLIC m3t)

add_executable(optimization_time optimization_time.cpp)
target_link_libraries(optimization_time PUBLIC m3t)

######## Mycpp files ########
add_executable(vidSeq vidSeq.cpp)
target_link_libraries(vidSeq PUBLIC m3t)

add_executable(vidSeq_2 vidSeq_2.cpp)
target_link_libraries(vidSeq_2 PUBLIC m3t)

add_executable(run_on_recorded_sequence_stabilo run_on_recorded_sequence_stabilo.cpp)
target_link_libraries(run_on_recorded_sequence_stabilo PUBLIC m3t)

add_executable(run_on_recorded_sequence_stabilo_wCali run_on_recorded_sequence_stabilo_wCali.cpp)
target_link_libraries(run_on_recorded_sequence_stabilo_wCali PUBLIC m3t)

add_executable(imgCompress imgCompress.cpp)
target_link_libraries(imgCompress PUBLIC m3t)

add_executable(imgCompress_rotation imgCompress_rotation.cpp)
target_link_libraries(imgCompress_rotation PUBLIC m3t)

add_executable(imgCali imgCali.cpp)
target_link_libraries(imgCali PUBLIC m3t)

######## end ########

if (USE_AZURE_KINECT)
    add_executable(record_camera_sequence record_camera_sequence.cpp)
    target_link_libraries(record_camera_sequence PUBLIC m3t)

    add_executable(run_on_camera_sequence run_on_camera_sequence.cpp)
    target_link_libraries(run_on_camera_sequence PUBLIC m3t)
endif ()
