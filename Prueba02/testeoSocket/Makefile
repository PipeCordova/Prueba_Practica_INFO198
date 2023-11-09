all:
	make clean
	g++ -o front frontend.cpp -O3 -pthread
	g++ -o cache cache.cpp -O3 -pthread
	g++ -o back backend.cpp -O3 -pthread
clean:
	rm -f front cache back
