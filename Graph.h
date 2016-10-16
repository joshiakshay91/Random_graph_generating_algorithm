#include <string>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

class Graph{
public:
  class Node{
  public:
    Node();
    ~Node();
    int color;
    int vName;
  };
  Graph(int);
  ~Graph();
  void Display();
  void Grow(int, int, int);
private:
  std::map<int,std::vector<Node> > AdjList;
  std::map<int,std::vector<Node> > TempList;
  std::map<int, int> vertices;
  bool loopThrough(int, int, int, int);
  std::list<int> myListParent;
  std::list<int> myListChild;
};
