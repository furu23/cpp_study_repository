# CMake 학습중
# CMake 최소 요구 버전
cmake_minimum_required(VERSION 3.14)

#project 이름
project(ChatManage)

#표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#실행 파일 지정
add_executable(ChatManageApp src/main.cpp)

#헤더 파일 경로 지정
target_include_directories(ChatManageApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)