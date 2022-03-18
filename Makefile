.PHONY: build check test memtest clear

check:
	./run_linters.sh

build:
	mkdir -p build && cd build && cmake .. && cmake --build .

test:
	cd build/project/tests && ./test_vector_array

memtest:
	echo "Testing"

clear:
	rm -rf build
	
