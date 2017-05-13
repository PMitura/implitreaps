test:
	g++ -Wall -pedantic -Wextra -std=c++17 -ggdb -O3 tests.cpp -o tests.out
	./tests.out

valtest:
	g++ -Wall -pedantic -Wextra -std=c++17 -ggdb -O3 tests.cpp -o tests.out
	valgrind ./tests.out

clean:
	rm -f tests.out
