#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

class Graph{
public:
  class Node{
  public:
    int color;
    int vName;
  };
  Graph(int);
  ~Graph();
  void Display();
  void Grow(int);
private:
  std::map<int,std::vector<Node> > AdjList;
  std::map<int, int> vertices;
};
