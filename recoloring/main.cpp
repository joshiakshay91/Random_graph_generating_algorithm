#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> 
#include <vector>
#include "Graph.h"
using namespace std;
int main()
{
	Graph g;
	vector<string> vertexList;
	vector<string>::iterator it;
	int vertices,graphs,edges;
	string line,v1,v2;
	while(getline(cin,line))
	{
		stringstream sstr(line);
		sstr>>v1>>v2;
		g.addEdge(v1,v2);
	}
	g.greedyColoring();
	cout<<"Greedy Coloring:"<<g.getNoOfColors()<<" "<<g.validColoring()<<endl;
	g.optimizeColoring();
	cout<<"Optimised Coloring"<<g.getOptimisedNo()<<" "<<g.validColoring()<<endl;
	g.print();
	return 0;
}
