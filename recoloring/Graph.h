//#pragma once

#include <map>
#include <set>
#include <fstream>
#include "Vertex.h"
//#include "KempeChain.h"
template <typename T1, typename T2>
struct valueCompair {
    typedef pair<T1, T2> type;
    bool operator ()(type const& a, type const& b) const {
        return a.second < b.second;
    }
};
class Graph
{
private:
	map<string,Vertex*> vertices;
	int noOfColors;
	int optimisedNo;
	vector<string>criticalVertices;
	map<int,int> criticalColorCount;
	vector<int>eliminatedColors;
public:
	Graph(void);
	~Graph(void);
	void addEdge(string,string);
	void print();
	void greedyColoring();
   	void findCriticalVertices();
	void sortCrticalVertices();
	void optimizeColoring();
	bool eliminateCritical(Vertex *);
	vector<string> eliminateColor(int,string,bool &);
	bool validColoring();
	int getNoOfColors();
	int getOptimisedNo();
};

