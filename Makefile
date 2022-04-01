.PHONY: build check test memtest clear

check:
	./run_linters.sh

build:
	mkdir -p build && cd build && cmake .. && cmake --build .

test: 
	mkdir -p build && cd build && cmake -DTEST=ON .. && cmake --build .
	./build/project/tests/test_words_array
	./build/project/tests/test_dyn_largest_word
	./build/project/tests/test_st_largest_word
	cd build && lcov -t "tests" -o coverage.xml -c -d project/words_array -d project/dyn_largest_word -d project/st_largest_word
	cd build && genhtml -o report coverage.xml  

memtest: build
	./memtest.sh build/project/tests/test_dyn_largest_word
	./memtest.sh build/project/tests/test_st_largest_word
	./memtest.sh build/project/tests/test_words_array

clean:
	rm -rf build