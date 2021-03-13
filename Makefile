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

unittest:
	cd build && ctest .

reset:
	git clean -d -f -x

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