#include "Graph.h"
Graph::Graph(int numVertex)
{
	for(int i=0;i<numVertex;i++)
	{
		Node vert;
		vert.color=i;
		vert.vName=i;
		vertices[vert.vName]=vert.color;
		for(int j=0;j<numVertex;j++)
		{
			Node comp;
			comp.color=j;
			comp.vName=j;
			if(comp.vName != vert.vName)  AdjList[vert.vName].push_back(comp);
		}
	}
}

Graph::~Graph()
{}

void Graph::Display()
{
	map<int,std::vector<Node> >:: iterator it;
	for(it=AdjList.begin();it!=AdjList.end();it++)
	{
		cout<<"N: "<<it->first<<" C: "<<vertices[it->first]<<" =>";
		for(int i=0;i<it->second.size();i++)
		{
			cout<<" N:"<<it->second[i].vName<<" C:"<<it->second[i].color<<", ";
		}
		cout<<endl;
	}
}

void Graph::Grow(int size)
{
	srand(time(NULL));
	int diff=size-vertices.size();
	for(int k=0;k<diff;k++)
	{
		int vSize=vertices.size();
		int loc=rand() % vSize;
		vertices[vSize]=vertices[loc];
		AdjList[vSize]=AdjList[loc];
		Node m;
		m.color=vertices[vSize];
		m.vName=vSize;
		for(int i=0;i<AdjList[vSize].size();i++)
		{
			int n=AdjList[vSize][i].vName;
			AdjList[n].push_back(m);
		}
	}
}
