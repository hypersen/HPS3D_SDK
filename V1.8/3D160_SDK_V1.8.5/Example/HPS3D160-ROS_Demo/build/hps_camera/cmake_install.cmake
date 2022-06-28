# Install script for directory: /home/kevin/eclipse-workspace/HPS3D160-SDK/demo/HPS3D160-ROS_Demo/src/hps_camera

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/kevin/eclipse-workspace/HPS3D160-SDK/demo/HPS3D160-ROS_Demo/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/kevin/eclipse-workspace/HPS3D160-SDK/demo/HPS3D160-ROS_Demo/build/hps_camera/catkin_generated/installspace/hps_camera.pc")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hps_camera/cmake" TYPE FILE FILES
    "/home/kevin/eclipse-workspace/HPS3D160-SDK/demo/HPS3D160-ROS_Demo/build/hps_camera/catkin_generated/installspace/hps_cameraConfig.cmake"
    "/home/kevin/eclipse-workspace/HPS3D160-SDK/demo/HPS3D160-ROS_Demo/build/hps_camera/catkin_generated/installspace/hps_cameraConfig-version.cmake"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hps_camera" TYPE FILE FILES "/home/kevin/eclipse-workspace/HPS3D160-SDK/demo/HPS3D160-ROS_Demo/src/hps_camera/package.xml")
endif()

