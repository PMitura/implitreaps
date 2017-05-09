test:
	g++ -Wall -pedantic -Wextra -std=c++17 -ggdb -O3 tests.cpp -o tests.out
	./tests.out

clean:
	rm -f tests.out
