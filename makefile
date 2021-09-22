src = 2dgridgraph.cpp AStarAlgorithm.cpp
obj = $(src:.cpp=.o)

CXX = clang++
CXXFLAGS = -std=c++17 -stdlib=libc++
LDDFLAGS = -lgtest

test: $(obj) gtestmain.o
	$(CXX) -o $@ $^ $(LDDFLAGS)

main: $(obj) main.o
	$(CXX) -o $@ $^ $(LDDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj)
	rm -f gtestmain.o test
	rm -f main.o main

