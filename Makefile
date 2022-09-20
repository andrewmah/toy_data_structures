main: main.o SplayTree.o
	g++ -o main main.o SplayTree.o

main.o: main.cpp src/SplayTree.h
	g++ -c main.cpp 

SplayTree.o: src/SplayTree.cpp src/SplayTree.h
	g++ -c src/SplayTree.cpp

clean:
	rm main main.o SplayTree.o