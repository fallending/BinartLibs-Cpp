
# ????

build:
	mkdir build && cd build && cmake .. && cmake --build .

utest:
	cd build && ctest .

clean:
	rm -rf build

purge:
	git clean -d -f -x