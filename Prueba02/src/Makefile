all:
	make clean
	g++ -std=c++17 -O3 -o searcher frontend.cpp
	g++ -std=c++17 -O3 -o memcache cache.cpp -pthread
	g++ -std=c++17 -O3 -o invertedIndex backend.cpp 
clean:
	rm -f searcher memcache invertedIndex