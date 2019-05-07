# Install script for directory: /mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/install")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hps_camera/msg" TYPE FILE FILES
    "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/distance.msg"
    "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg"
    "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/measureData.msg"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hps_camera/srv" TYPE FILE FILES "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/srv/camera.srv")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hps_camera/cmake" TYPE FILE FILES "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/build/hps_camera/catkin_generated/installspace/hps_camera-msg-paths.cmake")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/devel/include/hps_camera")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/devel/share/roseus/ros/hps_camera")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/devel/share/common-lisp/ros/hps_camera")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/devel/share/gennodejs/ros/hps_camera")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python" -m compileall "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/devel/lib/python2.7/dist-packages/hps_camera")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/devel/lib/python2.7/dist-packages/hps_camera")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/build/hps_camera/catkin_generated/installspace/hps_camera.pc")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hps_camera/cmake" TYPE FILE FILES "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/build/hps_camera/catkin_generated/installspace/hps_camera-msg-extras.cmake")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hps_camera/cmake" TYPE FILE FILES
    "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/build/hps_camera/catkin_generated/installspace/hps_cameraConfig.cmake"
    "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/build/hps_camera/catkin_generated/installspace/hps_cameraConfig-version.cmake"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/hps_camera" TYPE FILE FILES "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/package.xml")
endif()

