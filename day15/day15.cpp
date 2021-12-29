#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <set>
#include <cstdint>
#include <bitset>
#include <algorithm>
#include <map>
#include <stack>
#include <cctype>
#include <deque>

std::vector<std::vector<int>> cavern;
std::vector<std::vector<int>> min_cost;
std::deque<std::pair<int,int>> next_dest;

// push the next best spot on the stack - is the top the end?
// push the next best spot

void push_next(int x, int y, int tot) {

  if (x<0 || x>=cavern[0].size() || y<0 || y>=cavern.size()) return;
  if (min_cost[x][y]>tot+cavern[x][y])  {
    min_cost[x][y]=tot+cavern[x][y];
    if (next_dest.size()) {
      auto spot = next_dest.front();
      int fx = spot.first;
      int fy = spot.second;
      if (min_cost[x][y] < min_cost[fx][fy]) {
        next_dest.push_front(std::make_pair(x,y));
        return;
      }
    }
    next_dest.push_back(std::make_pair(x,y));
  }
  return;
}

void find_min ()
{
  int x=0, y=0;
  while (next_dest.size())
  {
    int tot = min_cost[x][y];

    push_next(x-1,y,tot);
    push_next(x+1,y,tot);
    push_next(x,y-1,tot);
    push_next(x,y+1,tot);

    auto spot = next_dest.front();
    x = spot.first;
    y = spot.second;
    tot = min_cost[x][y];
    next_dest.pop_front();

  }
}


int main ()
{
  std::ifstream is("day15.txt");
  std::string tem;

  size_t og_x, og_y;
  while (std::getline(is >> std::ws, tem))
  {
    std::vector<int> temp;
    for (auto c:tem) {
      temp.push_back(c-'0');
    }

    std::vector<int> temp3;
    og_y = temp.size();
    for (int i=0;i!=5;i++) {
      temp3.insert(temp3.end(),temp.begin(),temp.end());
      for (auto &j : temp) if (++j > 9) j=1;
    }

    cavern.push_back(temp3);
    std::vector<int> temp2 (temp3.size(),1000000);
    min_cost.push_back(temp2);
  }
  og_x = cavern[0].size();

  std::vector<std::vector<int>> cavern2 = cavern;
  for (int i=0;i!=4;i++) {
    for (auto &v:cavern) {
      for (auto &val:v) if (++val > 9) val=1;
      cavern2.push_back(v);
      std::vector<int> temp4 (v.size(),1000000);
      min_cost.push_back(temp4);
    }
  }

  cavern = cavern2;


  next_dest.push_back(std::make_pair(0,0));
  min_cost[0][0]=0;
  find_min();

  std::cout << "yes: " << min_cost[min_cost[0].size()-1][min_cost.size()-1] << std::endl;

  return 0;
}
