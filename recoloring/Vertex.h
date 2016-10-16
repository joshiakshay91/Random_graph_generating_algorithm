#ifndef _VERTEX
#define _VERTEX
#include<iostream>
#include<vector>
using namespace std;
class Vertex
	{
	private:
		string name;
		int color;
		int visited;//For BFS 0:white 1:gray 2:black
		vector<string> adjList;
		vector<int> adjColors;
		void sortAdjList();
	public:
		Vertex();
		Vertex(string name);
		~Vertex();
		string getName();
		void setName(string);
		int getColor();
		void setColor(int);
		void setVisited(int);
		int getVisited();
		void addVertextoAdjList(string);
		vector<string> getAdjList();
		vector<int> getAdjColors();
		void setAdjColor(int);
		void print();
		int adjListSize();
	};

#endif
