# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "hps_camera: 3 messages, 1 services")

set(MSG_I_FLAGS "-Ihps_camera:/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(hps_camera_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/measureData.msg" NAME_WE)
add_custom_target(_hps_camera_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hps_camera" "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/measureData.msg" "hps_camera/PointCloudData"
)

get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/srv/camera.srv" NAME_WE)
add_custom_target(_hps_camera_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hps_camera" "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/srv/camera.srv" ""
)

get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/distance.msg" NAME_WE)
add_custom_target(_hps_camera_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hps_camera" "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/distance.msg" ""
)

get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg" NAME_WE)
add_custom_target(_hps_camera_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "hps_camera" "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/measureData.msg"
  "${MSG_I_FLAGS}"
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hps_camera
)
_generate_msg_cpp(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/distance.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hps_camera
)
_generate_msg_cpp(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hps_camera
)

### Generating Services
_generate_srv_cpp(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/srv/camera.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hps_camera
)

### Generating Module File
_generate_module_cpp(hps_camera
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hps_camera
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(hps_camera_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(hps_camera_generate_messages hps_camera_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/measureData.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_cpp _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/srv/camera.srv" NAME_WE)
add_dependencies(hps_camera_generate_messages_cpp _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/distance.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_cpp _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_cpp _hps_camera_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hps_camera_gencpp)
add_dependencies(hps_camera_gencpp hps_camera_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hps_camera_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/measureData.msg"
  "${MSG_I_FLAGS}"
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hps_camera
)
_generate_msg_eus(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/distance.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hps_camera
)
_generate_msg_eus(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hps_camera
)

### Generating Services
_generate_srv_eus(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/srv/camera.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hps_camera
)

### Generating Module File
_generate_module_eus(hps_camera
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hps_camera
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(hps_camera_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(hps_camera_generate_messages hps_camera_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/measureData.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_eus _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/srv/camera.srv" NAME_WE)
add_dependencies(hps_camera_generate_messages_eus _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/distance.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_eus _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_eus _hps_camera_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hps_camera_geneus)
add_dependencies(hps_camera_geneus hps_camera_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hps_camera_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/measureData.msg"
  "${MSG_I_FLAGS}"
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hps_camera
)
_generate_msg_lisp(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/distance.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hps_camera
)
_generate_msg_lisp(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hps_camera
)

### Generating Services
_generate_srv_lisp(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/srv/camera.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hps_camera
)

### Generating Module File
_generate_module_lisp(hps_camera
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hps_camera
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(hps_camera_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(hps_camera_generate_messages hps_camera_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/measureData.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_lisp _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/srv/camera.srv" NAME_WE)
add_dependencies(hps_camera_generate_messages_lisp _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/distance.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_lisp _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_lisp _hps_camera_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hps_camera_genlisp)
add_dependencies(hps_camera_genlisp hps_camera_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hps_camera_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/measureData.msg"
  "${MSG_I_FLAGS}"
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hps_camera
)
_generate_msg_nodejs(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/distance.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hps_camera
)
_generate_msg_nodejs(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hps_camera
)

### Generating Services
_generate_srv_nodejs(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/srv/camera.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hps_camera
)

### Generating Module File
_generate_module_nodejs(hps_camera
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hps_camera
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(hps_camera_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(hps_camera_generate_messages hps_camera_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/measureData.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_nodejs _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/srv/camera.srv" NAME_WE)
add_dependencies(hps_camera_generate_messages_nodejs _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/distance.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_nodejs _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_nodejs _hps_camera_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hps_camera_gennodejs)
add_dependencies(hps_camera_gennodejs hps_camera_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hps_camera_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/measureData.msg"
  "${MSG_I_FLAGS}"
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hps_camera
)
_generate_msg_py(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/distance.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hps_camera
)
_generate_msg_py(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hps_camera
)

### Generating Services
_generate_srv_py(hps_camera
  "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/srv/camera.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hps_camera
)

### Generating Module File
_generate_module_py(hps_camera
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hps_camera
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(hps_camera_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(hps_camera_generate_messages hps_camera_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/measureData.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_py _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/srv/camera.srv" NAME_WE)
add_dependencies(hps_camera_generate_messages_py _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/distance.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_py _hps_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/mnt/hgfs/UbuntuShare/HPS3D_SDK_ROS_DEMO/src/hps_camera/msg/PointCloudData.msg" NAME_WE)
add_dependencies(hps_camera_generate_messages_py _hps_camera_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(hps_camera_genpy)
add_dependencies(hps_camera_genpy hps_camera_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS hps_camera_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hps_camera)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/hps_camera
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(hps_camera_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hps_camera)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/hps_camera
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(hps_camera_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hps_camera)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/hps_camera
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(hps_camera_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hps_camera)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/hps_camera
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(hps_camera_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hps_camera)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hps_camera\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/hps_camera
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(hps_camera_generate_messages_py std_msgs_generate_messages_py)
endif()
