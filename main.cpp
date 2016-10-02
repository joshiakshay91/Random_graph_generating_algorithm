#include "Graph.h"
int main()
{
  cout<<"The Graph of 5 nodes is represented each node alphabet indicates color"<<endl;
  Graph Complete(5);
  cout<<"Adjacency list of Complete graph"<<endl;
  Complete.Display();

  cout<<"\nNow making copy of node a"<<endl;
  Complete.Grow(9);
  cout<<"Adjacency list after adding duplicate of a as a'"<<endl;
  Complete.Display();
  return 0;
}
