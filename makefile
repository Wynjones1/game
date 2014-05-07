all:
	cmake -DCMAKE_BUILD_TYPE=debug .
	make -f Makefile -j5

run: all
	./game

clean:
	rm -rf CMakeCache.txt cmake_install.cmake CMakeFiles ./game*
