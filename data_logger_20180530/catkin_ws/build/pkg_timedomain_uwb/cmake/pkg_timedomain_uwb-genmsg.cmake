# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "pkg_timedomain_uwb: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ipkg_timedomain_uwb:/home/york1/catkin_ws/src/pkg_timedomain_uwb/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(pkg_timedomain_uwb_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/york1/catkin_ws/src/pkg_timedomain_uwb/msg/msg_timedomain_uwb.msg" NAME_WE)
add_custom_target(_pkg_timedomain_uwb_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "pkg_timedomain_uwb" "/home/york1/catkin_ws/src/pkg_timedomain_uwb/msg/msg_timedomain_uwb.msg" "std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(pkg_timedomain_uwb
  "/home/york1/catkin_ws/src/pkg_timedomain_uwb/msg/msg_timedomain_uwb.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pkg_timedomain_uwb
)

### Generating Services

### Generating Module File
_generate_module_cpp(pkg_timedomain_uwb
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pkg_timedomain_uwb
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(pkg_timedomain_uwb_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(pkg_timedomain_uwb_generate_messages pkg_timedomain_uwb_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/york1/catkin_ws/src/pkg_timedomain_uwb/msg/msg_timedomain_uwb.msg" NAME_WE)
add_dependencies(pkg_timedomain_uwb_generate_messages_cpp _pkg_timedomain_uwb_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pkg_timedomain_uwb_gencpp)
add_dependencies(pkg_timedomain_uwb_gencpp pkg_timedomain_uwb_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pkg_timedomain_uwb_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(pkg_timedomain_uwb
  "/home/york1/catkin_ws/src/pkg_timedomain_uwb/msg/msg_timedomain_uwb.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pkg_timedomain_uwb
)

### Generating Services

### Generating Module File
_generate_module_eus(pkg_timedomain_uwb
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pkg_timedomain_uwb
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(pkg_timedomain_uwb_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(pkg_timedomain_uwb_generate_messages pkg_timedomain_uwb_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/york1/catkin_ws/src/pkg_timedomain_uwb/msg/msg_timedomain_uwb.msg" NAME_WE)
add_dependencies(pkg_timedomain_uwb_generate_messages_eus _pkg_timedomain_uwb_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pkg_timedomain_uwb_geneus)
add_dependencies(pkg_timedomain_uwb_geneus pkg_timedomain_uwb_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pkg_timedomain_uwb_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(pkg_timedomain_uwb
  "/home/york1/catkin_ws/src/pkg_timedomain_uwb/msg/msg_timedomain_uwb.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pkg_timedomain_uwb
)

### Generating Services

### Generating Module File
_generate_module_lisp(pkg_timedomain_uwb
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pkg_timedomain_uwb
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(pkg_timedomain_uwb_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(pkg_timedomain_uwb_generate_messages pkg_timedomain_uwb_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/york1/catkin_ws/src/pkg_timedomain_uwb/msg/msg_timedomain_uwb.msg" NAME_WE)
add_dependencies(pkg_timedomain_uwb_generate_messages_lisp _pkg_timedomain_uwb_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pkg_timedomain_uwb_genlisp)
add_dependencies(pkg_timedomain_uwb_genlisp pkg_timedomain_uwb_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pkg_timedomain_uwb_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(pkg_timedomain_uwb
  "/home/york1/catkin_ws/src/pkg_timedomain_uwb/msg/msg_timedomain_uwb.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pkg_timedomain_uwb
)

### Generating Services

### Generating Module File
_generate_module_nodejs(pkg_timedomain_uwb
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pkg_timedomain_uwb
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(pkg_timedomain_uwb_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(pkg_timedomain_uwb_generate_messages pkg_timedomain_uwb_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/york1/catkin_ws/src/pkg_timedomain_uwb/msg/msg_timedomain_uwb.msg" NAME_WE)
add_dependencies(pkg_timedomain_uwb_generate_messages_nodejs _pkg_timedomain_uwb_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pkg_timedomain_uwb_gennodejs)
add_dependencies(pkg_timedomain_uwb_gennodejs pkg_timedomain_uwb_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pkg_timedomain_uwb_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(pkg_timedomain_uwb
  "/home/york1/catkin_ws/src/pkg_timedomain_uwb/msg/msg_timedomain_uwb.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pkg_timedomain_uwb
)

### Generating Services

### Generating Module File
_generate_module_py(pkg_timedomain_uwb
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pkg_timedomain_uwb
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(pkg_timedomain_uwb_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(pkg_timedomain_uwb_generate_messages pkg_timedomain_uwb_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/york1/catkin_ws/src/pkg_timedomain_uwb/msg/msg_timedomain_uwb.msg" NAME_WE)
add_dependencies(pkg_timedomain_uwb_generate_messages_py _pkg_timedomain_uwb_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(pkg_timedomain_uwb_genpy)
add_dependencies(pkg_timedomain_uwb_genpy pkg_timedomain_uwb_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS pkg_timedomain_uwb_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pkg_timedomain_uwb)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/pkg_timedomain_uwb
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(pkg_timedomain_uwb_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pkg_timedomain_uwb)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/pkg_timedomain_uwb
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(pkg_timedomain_uwb_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pkg_timedomain_uwb)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/pkg_timedomain_uwb
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(pkg_timedomain_uwb_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pkg_timedomain_uwb)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/pkg_timedomain_uwb
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(pkg_timedomain_uwb_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pkg_timedomain_uwb)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pkg_timedomain_uwb\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/pkg_timedomain_uwb
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(pkg_timedomain_uwb_generate_messages_py std_msgs_generate_messages_py)
endif()
