src = 2dgridgraph.cpp
obj = $(src:.cpp=.o)

CXX = clang++
CXXFLAGS = -std=c++17 -stdlib=libc++

test: $(obj) gtestmain.o
	$(CXX) -o $@ $^ -lgtest

main: $(obj) main.o
	$(CXX) -o $@ $^ 

.PHONY: clean
clean:
	rm -f $(obj)
	rm -f gtestmain.o test
	rm -f main.o main

