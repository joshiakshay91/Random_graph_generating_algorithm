#include "Graph.h"
#include <string>
#include <algorithm> 
///////////////////////////////////////////////////////////////////////////////
//Constructor and destructor for class Graph
Graph::Graph(void)
{
		
}


Graph::~Graph(void)
{
	
}

///////////////////////////////////////////////////////////////////////////////
//Member functions for class Graph

/*
addEdge()
	It will add one vertix of the edge to adj List of other vertex. 
IN:
	string vertexname1,vertexname2: two vertices of the edge.
OUT:NA
*/
void Graph::addEdge(string vertexname1,string vertexname2)
{
	Vertex *v1,*v2;
	map<string, Vertex*>::iterator itr;
	if(vertices.empty())
	{
		v1=new Vertex(vertexname1);
		v2=new Vertex(vertexname2);
		vertices.insert(make_pair(vertexname1,v1));
		vertices.insert(make_pair(vertexname2,v2));
		v1->addVertextoAdjList(vertexname2);
		v2->addVertextoAdjList(vertexname1);
	}
	else
	{
		itr=vertices.find(vertexname1);
		if(itr!=vertices.end())
			itr->second->addVertextoAdjList(vertexname2);
		else
		{
			v1=new Vertex(vertexname1);
			vertices.insert(make_pair(vertexname1,v1));
			v1->addVertextoAdjList(vertexname2);
		}
		itr=vertices.find(vertexname2);
		if(itr!=vertices.end())
			itr->second->addVertextoAdjList(vertexname1);
		else
		{
			v2=new Vertex(vertexname2);
			vertices.insert(make_pair(vertexname2,v2));
			v2->addVertextoAdjList(vertexname1);
		}
	}
}

/*
print(): Print graph vertex and its color.
*/
void Graph::print()
{
	map<string, Vertex*>::iterator itr;
	for(itr=vertices.begin();itr!=vertices.end();itr++)
	{
		cout<<itr->first<<","<<itr->second->getColor()<<":";
		//itr->second->print();
		cout<<endl;
	}
}
/*
greedyColoring(): Color a given graph with greedy approach.
*/
void Graph::greedyColoring()
{
	map<string,Vertex*>::iterator itr;
	int size,color;
	noOfColors=0;
	for(itr=vertices.begin();itr!=vertices.end();itr++)
	{
		Vertex *v=itr->second;
		vector<string>adjList=v->getAdjList();
		size=v->adjListSize();
		vector<bool>colorList(size+1);
		for(int i=0;i<size;i++)
		{
			color=vertices[adjList[i]]->getColor();
			colorList[color]=true;
		}
		for(int i=1;i<size+1;i++)
		{
			if(!colorList[i])
			{
				v->setColor(i);
				break;
			}
		}
		if(v->getColor()==0)
			v->setColor(colorList.size());
		if(v->getColor()>noOfColors)
			noOfColors=v->getColor();
	}
}

/*
findCriticalVertices(): Once graph is colored find critical vertices and colors in graph.
*/
void Graph::findCriticalVertices()
{
	Vertex *v;
	map<string,Vertex*>::iterator itr;
	vector<string> adjList;
	set<int> colorSet;
	int tempColor;
	validColoring();
	criticalVertices.clear();
	for(int i=0;i<optimisedNo;i++)
	{
		criticalColorCount.insert(make_pair(i+1,0));
	}
	for(itr=vertices.begin();itr!=vertices.end();itr++)
	{
		v=itr->second;
		adjList=v->getAdjList();
		for(int i=0;i<adjList.size();i++)
		{
			tempColor=vertices[adjList[i]]->getColor();
			colorSet.insert(tempColor);
			v->setAdjColor(tempColor);
		}
		if(colorSet.size()==optimisedNo-1)
		{
			criticalVertices.push_back(itr->first);
			criticalColorCount[v->getColor()]+=1;
		}
		colorSet.clear();
	}
}


void Graph::sortCrticalVertices()
{
        vector<pair<int,int> > item;
	map<int,int>::iterator itr;
	findCriticalVertices();
	for(itr=criticalColorCount.begin();itr!=criticalColorCount.end();itr++)
	{
		item.push_back(make_pair(itr->first,itr->second));
	}
        std::sort(item.begin(), item.end(), valueCompair<int,int>());
	for(int i=0;i<item.size();i++)
	{
		cout<<item[i].first<<" "<<item[i].second<<endl;
	}
}

/*
optimizeColoring(): Once graph is colored with greedy approach, then eliminate colors with critical count of 1.
*/
void Graph::optimizeColoring()
{
	vector<pair<int,int> > item;
	map<int,int>::iterator itr;
	Vertex *critical;
	int count=0;
	lable:
	findCriticalVertices();
	for(itr=criticalColorCount.begin();itr!=criticalColorCount.end();itr++)
	{
		item.push_back(make_pair(itr->first,itr->second));
	}
        std::sort(item.begin(), item.end(), valueCompair<int,int>());
	for(int i=0;i<item.size();i++)
	{
		if(item[i].second==1)
		{
			critical=NULL;
			for(int j=0;j<criticalVertices.size();j++)
			{
				if(vertices[criticalVertices[j]]->getColor()==item[i].first)
				{
					critical=vertices[criticalVertices[j]];
					break;
				}
			}
			if(critical!=NULL && eliminateCritical(critical))
			{
				item.clear();
				count++;
				goto lable;
			}
		}
	}
}

/*
eliminateCritical(): Find color and it's respective vertex, which can be replaced with
		     critical color to be eliminated.
*/
bool Graph::eliminateCritical(Vertex *critical)
{
	vector<string> adjList;
	map<int,int> adjColorCount;
	map<int,int>::iterator itr;
	adjList=critical->getAdjList();
	for(int i=0;i<adjList.size();i++)
	{
		if(adjColorCount.find(vertices[adjList[i]]->getColor())==adjColorCount.end())
			adjColorCount.insert(make_pair(vertices[adjList[i]]->getColor(),1));
		else
			adjColorCount[vertices[adjList[i]]->getColor()]+=1;
	}
	for(int i=0;i<adjList.size();i++)
	{
		if(adjColorCount[vertices[adjList[i]]->getColor()]==1)
		{
			bool flag=false;
			for(int j=0;j<criticalVertices.size();j++)
			{
				if(criticalVertices[j]==adjList[i])
				{flag=true; break;}
			}
			if(flag==false)
			{
				int criticalColor,rpColor;
				bool eliminated=false;
				vector<string> elinimatedVertices;
				criticalColor=critical->getColor();
				rpColor=vertices[adjList[i]]->getColor();
				elinimatedVertices=eliminateColor(criticalColor,critical->getName(),eliminated);
				critical->setColor(rpColor);
				vertices[adjList[i]]->setColor(criticalColor);
				eliminated=false;
				eliminateColor(criticalColor,"",eliminated);
				if(!validColoring() || !eliminated)
				{
					for(int k=0;k<elinimatedVertices.size();k++)
					{
						vertices[elinimatedVertices[k]]->setColor(criticalColor);
						critical->setColor(criticalColor);
						vertices[adjList[i]]->setColor(rpColor);
					}
				}
				else
				{	cerr<<adjList[i]<<"\n";
					eliminatedColors.push_back(criticalColor);
					return true;
				}
			}
		}
	}
	return false;
}

/*
eliminateColor(): eliminate given color.
*/
vector<string> Graph::eliminateColor(int color,string critical, bool &eliminated)
{
	map<string,Vertex*>::iterator graphItr;
	vector<int>colors;
	vector<string> adjList, elinimatedVertices;
	Vertex *v;
	for(graphItr=vertices.begin();graphItr!=vertices.end();graphItr++)
	{
		v=graphItr->second;
		if(v->getName()!=critical && v->getColor()==color)
		{
			adjList=v->getAdjList();
			colors.resize(noOfColors+1);
			for(int i=0;i<adjList.size();i++)
			{
				colors[vertices[adjList[i]]->getColor()]=1;
			}
			for(int i=0;i<eliminatedColors.size();i++)
				colors[eliminatedColors[i]]=1;
			colors[color]=1;

			for(int i=1;i<noOfColors+1;i++)
			{
				if(colors[i]==0)
				{
					v->setColor(i);
					eliminated=true;
				}
			}
			elinimatedVertices.push_back(v->getName());
			colors.clear();
		}
	}
	return elinimatedVertices;
}

/*
validColoring(): Verify if graph coloring proper. i.e no to adjacent vertices have same color.
*/
bool Graph::validColoring()
{
	map<string,Vertex*>::iterator graphItr;
	vector<string> adjList;
	set<int>colorCount;
	Vertex *v;
	int tempColor;
	for(graphItr=vertices.begin();graphItr!=vertices.end();graphItr++)
	{
		v=graphItr->second;
		adjList=v->getAdjList();
		for(int i=0;i<adjList.size();i++)
		{
			tempColor=vertices[adjList[i]]->getColor();
			if(tempColor==v->getColor())
				return false;
		}
		colorCount.insert(v->getColor());
	}
	optimisedNo=colorCount.size();
	return true;
}

int Graph::getNoOfColors()
{
	return noOfColors;
}

int Graph::getOptimisedNo()
{
	return optimisedNo;
}
