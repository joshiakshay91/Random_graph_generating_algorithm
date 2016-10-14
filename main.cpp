#include "Graph.h"
int main()
{
  int NodeNums;
  cout<<"Enter the number of nodes in your complete graph: ";
  cin>>NodeNums;
  Graph Complete(NodeNums);
  cout<<"Adjacency list of Complete graph with "<<NodeNums<<"is: "<<endl;
  Complete.Display();
  cout<<"Legends: N stands for Node name/number, C stands for color"<<endl;
  int growthSize;
  std::cout << "\nplease enter the size the graph has to expand: " << std::endl;
  cin>>growthSize;
  if(growthSize>NodeNums)
  {
    int loss, parentPer;
    std::cout<<"enter the percentage that the either of the duplicated node looses edges"<<endl;
    cin>>loss;
    std::cout<<"\nenter the percentage that a parent node looses its edge"<<endl;
    cin>>parentPer;
    if((loss<100)&&(parentPer<100)) Complete.Grow(growthSize,loss,parentPer);
    else
    {
      cout<<"percentage needs to be below 100" <<endl;
      return 0;
    }
  }
  else
  {
    cout<<"you entered value less than the graph size next time enter properly"<<endl;
    return 0;
  }
  cout<<"Adjacency list after adding duplicating various nodes"<<endl;
  Complete.Display();

  return 0;
}
