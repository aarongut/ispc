CXX=g++
CXXFLAGS=-std=c++11 -O2

ISPC=../ispc
ISPCFLAGS=--target=sse4-x2 -O2 --arch=x86-64

%.out : %.cpp %.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$ : $.o

%.o : %.ispc
	$(ISPC) $(ISPCFLAGS) -h $*.h -o $*.o $<
