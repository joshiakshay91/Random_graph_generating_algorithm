#include "Vertex.h"
///////////////////////////////////////////////////////////////////////////////
// Constructors and Destructor for class Vertext
Vertex::Vertex()
{
}

Vertex::Vertex(string name)
{
	this->name=name;
	this->color=0;
}

Vertex::~Vertex()
{
}

///////////////////////////////////////////////////////////////////////////////
//getters and setters functions for class Vertex

int Vertex::getColor()
{
	return color;
}

void Vertex::setColor(int color)
{
	this->color=color;
}

string Vertex::getName()
{
	return name;
}

void Vertex::setName(string name)
{
	this->name=name;
}

vector<string> Vertex::getAdjList()
{
	return adjList;
}

void Vertex::setVisited(int v)
{
	visited=v;
}

int Vertex::getVisited()
{
	return visited;
}
///////////////////////////////////////////////////////////////////////////////
//Member functions for class Vertex

///////////////////////////////////////////////////////////////////////////////
/*
sortAdjList()
	This function uses insertion sort to sort the adjacency list of vertext in ascending order
IN:NA
OUT:NA
*/
void Vertex::sortAdjList()
{
	int i;
	string key;
	for(int j=1;j<(signed int)adjList.size();j++)
	{
		key=adjList[j];
		i=j-1;
		while(i>-1 && adjList[i].compare(key)>0)
		{
			adjList[i+1]=adjList[i];
			i=i-1;
		}
		adjList[i+1]=key;
	}
}
///////////////////////////////////////////////////////////////////////////////
/*
addVertextoAdjList()
	This function adds vertex in adj list of calling vertex and also their weight
IN:
	string vertexName: name of vertex which is to be added in adj List of calling vertex
	int weight: weight between two vertices.
OUT:NA
*/
void Vertex::addVertextoAdjList(string vertexName)
{
	int size=adjList.size();
	adjList.push_back(vertexName);
	if(size>0){}
		//sortAdjList();
}

int Vertex::adjListSize()
{
	return adjList.size();
}

void Vertex::print()
{
	vector<string>::iterator itr;
	for(itr=adjList.begin();itr!=adjList.end();itr++)
	{
		cout<<*itr<<",";
	}
}

void Vertex::setAdjColor(int color)
{
	//if(adjColors.find(color)!=adjColors.end())
	adjColors.push_back(color);	
}

vector<int> Vertex::getAdjColors()
{
	return adjColors;
}
