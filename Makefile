

build:
	mkdir build && cd build && cmake .. && cmake --build .

# https://docs.microsoft.com/zh-cn/cpp/build/manage-libraries-with-vcpkg?view=msvc-160&tabs=macos

rebuild:
	rm -rf build && mkdir build && cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=~/.cmake_modules/vcpkg/scripts/buildsystems/vcpkg.cmake && cmake --build .

unittest:
	cd build && ctest .

clean:
	rm -rf build

reset:
	git clean -d -f -x

gen-vs2019:
	mkdir build-vs2019

gen-vs:
	make gen-vs2019

gen-xcode:
	mkdir build-xcode