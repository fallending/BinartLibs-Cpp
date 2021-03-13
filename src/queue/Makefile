

clean:
	rm -rf CMakeFiles
	rm -rf bitbuffer
	rm -rf queue
	rm -rf http
	rm -rf CMakeCache.txt
	rm -rf build
	rm -rf build-ios
	rm -rf build-android

rebuild-ios:
	make clean
	# https://github.com/leetal/ios-cmake
	mkdir build-ios && cd build-ios && cmake .. -G Xcode -DCMAKE_TOOLCHAIN_FILE=../../cmake/ios.toolchain.cmake -DPLATFORM=SIMULATOR64 && cmake --build . --config Debug && cmake --build . --config Release

rebuild-android:
	make clean
	# https://github.com/taka-no-me/android-cmake
	# 需要先export ANDROID_NDK=？？？
	# mkdir build-android && cd build-android && cmake .. -DCMAKE_TOOLCHAIN_FILE=../../cmake/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DANDROID_ABI="x86_64" && cmake --build .
	mkdir build-android && cd build-android && cmake .. -DCMAKE_TOOLCHAIN_FILE="${NDK_HOME}/build/cmake/android.toolchain.cmake" && cmake --build .

# 需要消化的文章：https://www.jianshu.com/p/2c88a03b8b48
# https://juejin.cn/post/6844903681586888718