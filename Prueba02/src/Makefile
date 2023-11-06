TARGETS = searcher invertedindex memcache
CXX = g++
CXXFLAGS = -std=c++17 -O3

frontend: frontend.cpp
	$(CXX) $(CXXFLAGS) -o searcher frontend.cpp

backend: backend.cpp
	$(CXX) $(CXXFLAGS) -o invertedindex backend.cpp

cache: cache.cpp
	$(CXX) $(CXXFLAGS) -o memcache cache.cpp

clean:
	$(RM) $(TARGETS)