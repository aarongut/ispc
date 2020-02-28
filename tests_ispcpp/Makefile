CXX=g++
CXXFLAGS=-std=c++11 -O3 -lm -lpthread

ISPC=../ispc
ISPCFLAGS=--target=avx2 -O3 --arch=x86-64

%.out : %.cpp %.o tasksys.o
	$(CXX) $(CXXFLAGS) -o $@ $^

tasksys.o : ../examples/tasksys.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

$ : $.o

%.o : %.ispc
	$(ISPC) $(ISPCFLAGS) -h $*.h -o $*.o $<
