CXX = g++
CXXFLAGS = -g -Wall

.PHONY: clean 

all: sst_shipping util_test

file_watcher : file_watcher.cc
	$(CXX) $(CXXFLAGS) $@.cc -o$@  -std=c++11 -lstdc++fs -lpthread -lboost_system -lboost_thread


 clean:
	rm -f file_watcher

