# 这个很可以参考：https://zhuanlan.zhihu.com/p/103696297

build:
	mkdir build && cd build && cmake .. && cmake --build .

# https://docs.microsoft.com/zh-cn/cpp/build/manage-libraries-with-vcpkg?view=msvc-160&tabs=macos


# 1. 区分交叉编译环境（windows/linux/macosx）
# 2. 区分目标平台（win32/win64/linux/mac64/iOS/android等等）

# MT_TARGET_PLATFORM
# MT_TARGET_PLATFORM_ANDROID
# MT_TARGET_PLATFORM_IOS
# MT_TARGET_PLATFORM_WINDOWS
# ????

# 所有架构
# 1. ios
# 2. android
# 3. windows
# 用 它 来决定主cmakelist中的options
# 主cmakelist中的options，来决定 add_definitions(-Dhha -Dbbb)，从而决定愿代码文件中的 #if #else #endif

# 方式1: cmakelist 直接整合到工程，通过ANDROID APPLE，工程编译时，打不同的包
# 方式2: cmakelist 通过ANDROID APPLE，工程编译时，打不同的包，集成到工程中

toolchain:
	cmake --version

clean:
	rm -rf build

rebuild-ios:
	make clean && mkdir build && cd build
	# cmake .. -DCMAKE_TOOLCHAIN_FILE=~/.cmake_modules/vcpkg/scripts/buildsystems/vcpkg.cmake && cmake --build .
	cmake .. -G Xcode -DCMAKE_TOOLCHAIN_FILE=../../cmake/ios.toolchain.cmake -DPLATFORM=SIMULATOR64
	cmake --build . --config Debug
	cmake --build . --config Release

rebuild-android:
	rm -rf build && mkdir build && cd build && cmake .. -DMT_TARGET_PLATFORM=android -DCMAKE_TOOLCHAIN_FILE=~/.cmake_modules/vcpkg/scripts/buildsystems/vcpkg.cmake && cmake --build .

rebuild:
	rm -rf build && mkdir build && cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=~/.cmake_modules/vcpkg/scripts/buildsystems/vcpkg.cmake && cmake --build . && make install

test:
	cd build && ctest .

reset:
	git clean -d -f -x

gen-macosx:
	# 生成xcode 报错：No CMAKE_C_COMPILER could be found. No CMAKE_CXX_COMPILER could be found.
	# 参考：https://stackoverflow.com/questions/41380900/cmake-error-no-cmake-c-compiler-could-be-found-using-xcode-and-glfw
	# xcrun -find c++
	# xcrun -find cc
	rm -rf _exports && mkdir _exports && cd _exports && cmake -G Xcode -H. -B_build ..

	# https://polly.readthedocs.io/en/latest/toolchains/ios.html
	# ./polly/bin/build.py --ios-multiarch

gen-xcode2:
	# rm -rf _exports && mkdir _exports && cd _exports && cmake .. -G Xcode -DCMAKE_TOOLCHAIN_FILE=../cmake/ios.toolchain.cmake -DPLATFORM=OS64COMBINED
	rm -rf _exports && mkdir _exports && cd _exports && cmake .. -DCMAKE_TOOLCHAIN_FILE=~/.cmake_modules/vcpkg/scripts/buildsystems/vcpkg.cmake -G Xcode -DCMAKE_SYSTEM_NAME=iOS

gen-test:
	cmake -S. -B_builds -GXcode \
    -DCMAKE_SYSTEM_NAME=iOS \
    "-DCMAKE_OSX_ARCHITECTURES=armv7;armv7s;arm64;i386;x86_64" \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=9.3 \
    -DCMAKE_INSTALL_PREFIX=`pwd`/_install \
    -DCMAKE_XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH=NO \
    -DCMAKE_IOS_INSTALL_COMBINED=YES

gen-vs:
	mkdir build-vs2019

gen-pod:
	mkdir build-xcode

gen-gradle:
	mkdir build-gradle


# TODO: 
# 1. 生成 gradle 可以直接集成的库
# 2. 生成 cocoapod 可以直接集成的库
# 3. 生成 vs 可以直接集成的库