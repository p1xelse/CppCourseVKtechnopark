.PHONY: build check test memtest clear

check:
	./run_linters.sh

build:
	mkdir -p build && cd build && cmake .. && cmake --build .

test: 
	mkdir -p build && cd build && cmake -DTEST=ON .. && cmake --build .
	cd build/project/tests && ./test_vector_array
	cd build && lcov -t "tests/tests_vector_arr" -o coverage.info -c -d project/vector_array
	cd build && genhtml -o report coverage.info  

memtest: build
	./memtest.sh build/project/tests/test_vector_array

clean:
	rm -rf build
	