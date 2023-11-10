all:
	make clean
	g++ -o searcher frontend.cpp -O3 -pthread
	g++ -o memcache cache.cpp -O3 -pthread
	g++ -o invertedIndex backend.cpp -O3 -pthread
clean:
	rm -f searcher memcache invertedIndex
