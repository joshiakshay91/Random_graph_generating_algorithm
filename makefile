CXX = g++

Grow: Graph.o main.o
		$(CXX) -o Grow Graph.o main.o

main.o: main.cpp Graph.h

Graph.o: Graph.cpp Graph.h

clean:
		rm -f *.o Grow
