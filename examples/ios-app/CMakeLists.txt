# https://github.com/maketea-tech/tvm_phone/blob/master/tvm-cmake-ios.md


cmake_minimum_required(VERSION 3.14)

 Project (tvm_demo_ios C CXX)

 set(SRC_FILES tvm_demo_ios/main.m)

 add_executable(tvm_demo_ios MACOSX_BUNDLE ${SRC_FILES})

 include_directories(SYSTEM ../tvm_model/build.ios/Debug-iphonesimulator/tvm_model.framework)

 target_link_libraries(tvm_demo_ios "-framework Foundation  -framework UIKit -framework tvm_model")

 set_target_properties(tvm_demo_ios PROPERTIES
   LINK_FLAGS "-Wl,-F../tvm_model/build.ios/Debug-iphonesimulator"
   MACOSX_BUNDLE_GUI_IDENTIFIER "com.example.\${PRODUCT_NAME:identifier}"
 )

 install(TARGETS tvm_demo_ios DESTINATION tvm_demo_ios.app)


 为了编译 ios app,需要连接到 UIKit.framework: target_link_libraries(tvm_demo_ios "-framework UIKit")

添加 MACOSX_BUNDLE_GUI_IDENTIFIER 属性
  上面的cmake文件，能编译通过，但不能被启动运行: Bundle id can't be determined。
  参照参考11，添加 MACOSX_BUNDLE_GUI_IDENTIFIER  属性，才能在ios模拟器内，运行起来。
  `  MACOSX_BUNDLE_GUI_IDENTIFIER "com.example.\${PRODUCT_NAME:identifier}")`
复制 resource
把 data 目录，作为 resource, 打包进 app:

 # copy resource phase

 set(APP_NAME \${TARGET_BUILD_DIR}/\${FULL_PRODUCT_NAME})
 set(RES_DIR  ./data)
 add_custom_command(
     TARGET tvm_demo_ios
     POST_BUILD
     COMMAND mkdir ${APP_NAME}/Resources/ && echo "." || echo "."
     COMMAND cp -Rf ../resources/*  ${APP_NAME}/Resources/
 )   
cmake把自定义脚本，生成在一个文件内，在xcode编译的时候，会调用这个文件：
tvm_demo_ios/build.ios/CMakeScripts/tvm_demo_ios_postBuildPhase.makeDebug. 脚本运行的当前目录是: tvm_demo_ios/build.ios.