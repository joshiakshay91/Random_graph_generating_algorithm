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

void Graph::printFile()
{
	ofstream data("output.txt");
	map<int,std::vector<Node> >:: iterator it;
	for(it=AdjList.begin();it!=AdjList.end();it++)
	{
		for(int i=0; i<it->second.size();i++)
			data<<it->first<<" "<<it->second[i].vName<<endl;
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
		bool successFlag=false;
		while(!successFlag)
		{
			while(!myListParent.empty())	myListParent.pop_front();
			while(!myListChild.empty())	myListChild.pop_front();
			successFlag=loopThrough(loc,vSize,lossPercent,ParentPercent);
		}
		if(successFlag)
		{
			AdjList[loc]=TempList[0];
			AdjList[vSize]=TempList[1];
			TempList.erase(0);
			TempList.erase(1);
			while(!myListParent.empty())
		{
			int n=myListParent.front();
			myListParent.pop_front();
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
			if(AdjList[n].size()==0)	cout<<"Error here:"<<endl;
		}
		while(!myListChild.empty())
		{
			int n=myListChild.front();
			myListChild.pop_front();
		//	AdjList[n].pop_back();
			int destroy;
			for(int m=0;m<AdjList[n].size();m++)
			{
				if(AdjList[n][m].vName==vSize)
				{
					destroy=m;
					break;
				}
			}
			AdjList[n].erase(AdjList[n].begin()+destroy);
				if(AdjList[n].size()==0)	cout<<"Error here2:"<<endl;
		}

		}
	}
}

bool Graph::loopThrough(int parentN, int childN, int lossPercent, int ParentPercent)
{
	TempList[0] = AdjList[parentN];
	TempList[1] = AdjList[childN];
	int offset=0;
	for(int z=0;z<TempList[1].size();z++)
	{
			int chance= rand()%100;
			chance=chance+1;
			if (chance<=lossPercent)
			{
				int roll=rand()%100;
				roll=roll+1;
				if(roll<=ParentPercent )
				{
					//parent looses the node
					if((TempList[0].size())<= 1)
					{
						return false;//its going to delete the whole thing return and redo
					}
					int n=TempList[1][z].vName;
					myListParent.push_back(n);
					TempList[0].erase(TempList[0].begin()+(z-(offset)));
					offset++;
				}
				else
				{
					//child looses the node
					if((TempList[1].size())<= 1)
					{return false;//its going to delete the whole thing return and redo
					}
					int n= TempList[1][z].vName;
					myListChild.push_back(n);
					TempList[1].erase(TempList[1].begin()+(z));
					offset--;
				}
			}
	}
	return true;
	/////
}
