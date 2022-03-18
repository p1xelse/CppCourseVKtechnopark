check:
	./run_linters.sh

build:
	mkdir -p build && cd build && cmake .. && cmake --build .

test:
	echo "Testing"

test:
	echo "Testing"

clear:
	rm -rf build
	
