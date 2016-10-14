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
{
	int sizer=AdjList.size();
	std::map<int,std::vector <Node> >::iterator it;
	for(int i=0;i<sizer; i++)
	{
		it=AdjList.find(i);
		AdjList.erase(it);
	}
	int LSize=vertices.size();
	std::map<int,int>:: iterator itr;
	for(int i=0;i<LSize;i++)
	{
		itr=vertices.find(i);
		vertices.erase(itr);
	}
}

Graph::Node::Node(){}

Graph::Node::~Node(){}


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

void Graph::Grow(int size, int lP, int PP)
{
	int lossPercent=lP;
	int ParentPercent=PP;
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
		int iterations=AdjList[vSize].size();
		int offset=0;
		for(int z=0;z<AdjList[vSize].size();z++)
		{
			bool execute=false;
			while(!execute)
			{
				int chance=rand()%100;
				chance=chance+1;
				if(chance<=lossPercent)
				{
					int roll=rand()%100;
					roll=roll+1;
					if(roll<=ParentPercent && (AdjList[loc].size()>1))
					{//parent looses the node;
						execute=true;
						int n=AdjList[vSize][z].vName;
						int destroy;
						for(int m=0;m<AdjList[n].size();m++)
						{
							if(AdjList[n][m].vName==loc)
							{
								destroy=m;
								break;
							}
						}
						AdjList[n].erase(AdjList[n].begin()+destroy);
						AdjList[loc].erase(AdjList[loc].begin()+(z-(offset)));
						offset++;
					}
					else if(roll>ParentPercent && (AdjList[vSize].size()>1))
					{//child looses the node;
						execute=true;
						int n=AdjList[vSize][z].vName;
						AdjList[n].pop_back();
						AdjList[vSize].erase(AdjList[vSize].begin()+(z));
						offset--;
					}
				}
				else
				{
					execute=true;
				}
			}
		}
	}
}
