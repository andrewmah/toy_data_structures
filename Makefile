CXXFLAGS = -std=c++20 -Wall 

main: bin/main.o bin/splay_tree.o
	$(CXX) $(CXXFLAGS) -o bin/main bin/main.o bin/splay_tree.o

bin/main.o: src/main.cpp src/splay_tree.h
	$(CXX) $(CXXFLAGS) -c -o bin/main.o src/main.cpp 

test: bin/test.o bin/splay_tree.o
	$(CXX) $(CXXFLAGS) -lgtest -o bin/test bin/test.o bin/splay_tree.o

bin/test.o: test/test.cpp
	$(CXX) $(CXXFLAGS) -c -o bin/test.o test/test.cpp

bin/splay_tree.o: src/splay_tree.cpp src/splay_tree.h
	$(CXX) $(CXXFLAGS) -c -o bin/splay_tree.o src/splay_tree.cpp

clean:
	rm bin/*