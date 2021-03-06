# https://blog.csdn.net/zhuyunier/article/details/83025615
cmake_minimum_required(VERSION 3.17)

project(queue-proj VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

set (CMAKE_CXX_STANDARD 14)

include_directories(${queue_SOURCE_DIR})

add_library(queue SHARED concurrent_queue.cpp concurrent_queue.hpp )


# Debug symbols set in XCode project
if (IOS)
  set_xcode_property(queue GCC_GENERATE_DEBUGGING_SYMBOLS YES "All")
endif (IOS)

set(HEADER_FILES
  concurrent_queue.hpp
)

set(RESOURCE_FILES 
  readme.md 
  # appresourcedir/appres.txt
)

set_target_properties(queue
  PROPERTIES
  FRAMEWORK TRUE
  FRAMEWORK_VERSION A
  MACOSX_FRAMEWORK_IDENTIFIER com.mt.queue
  # MACOSX_FRAMEWORK_INFO_PLIST Info.plist
  # "current version" in semantic format in Mach-O binary file
  VERSION 1.0.0
  # "compatibility version" in semantic format in Mach-O binary file
  SOVERSION 1.0.0
  PUBLIC_HEADER ${HEADER_FILES}
  RESOURCE      ${RESOURCE_FILES}
  # XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
)