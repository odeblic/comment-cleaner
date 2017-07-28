cmake_minimum_required(VERSION 2.8)

project(comment_cleaner)

set(src_files comment_cleaner.c)

#cmake -DBUILD_SHARED_LIBS:BOOL=ON
#add_library(comment_cleaner ${src_files})

add_library    (comment_cleaner_dyn  SHARED ${src_files})
add_library    (comment_cleaner_sta  STATIC ${src_files})
add_executable (comment_cleaner_app         ${src_files})

set_target_properties(comment_cleaner_dyn PROPERTIES OUTPUT_NAME comment_cleaner)
set_target_properties(comment_cleaner_sta PROPERTIES OUTPUT_NAME comment_cleaner)
set_target_properties(comment_cleaner_app PROPERTIES OUTPUT_NAME comment_cleaner)

