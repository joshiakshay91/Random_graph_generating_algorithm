CXX = g++ -std=c++11

Greedy: main.o Graph.o Vertex.o
		$(CXX) -o Greedy main.o Graph.o Vertex.o
main.o: main.cpp Graph.h

Graph.o: Graph.cpp Graph.h Vertex.h

Vertex.o:Vertex.cpp Vertex.h

clean:
		rm -f *.o Greedy output.txt
