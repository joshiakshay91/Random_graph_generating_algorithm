#include<vector>
#include<map>
#include<fstream>
#include<iostream>
#include <iomanip>
using namespace std;
int main()
{
  std::map<int, vector<int> > map;
  std::fstream myfile("data.txt", std::ios_base::in);
  int a;
  int counter=0;
  while(myfile >> a)
  {
    ++counter;
    map[a].push_back(1);
  }
  for(std::map<int, vector<int> >::iterator it=map.begin();it!=map.end();it++)
  {
    double val=((float(map[it->first].size()))/(float (counter)));
    cout<<"("<<it->first<<"-"<<setprecision(2)<<val<<")"<<"\t";
  }
  cout<<endl;
  return 0;
}
