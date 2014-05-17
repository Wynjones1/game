all:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=debug ../
	cd build && make -f Makefile -j5

run: all
	./build/game

clean:
	rm -Rf build
