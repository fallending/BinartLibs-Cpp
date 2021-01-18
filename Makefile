
build:
	mkdir build && cd build && cmake .. && cmake --build .

utest:
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