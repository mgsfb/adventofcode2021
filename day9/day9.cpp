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

std::vector<std::vector<int>> floor;
std::vector<std::vector<int>> visited;

int basin_size (size_t x, size_t y, int steps, int last)
{
  if (x<0 || x>=floor.size() || y<0 || y>=floor[0].size()) return 0;
  if (visited[x][y] || floor[x][y]==9 || floor[x][y] < last) return 0;
  visited[x][y]=1;
  steps=std::max(steps,basin_size(x-1,y,steps+1,floor[x][y]));
  steps=std::max(steps,basin_size(x,y-1,steps+1,floor[x][y]));
  steps=std::max(steps,basin_size(x+1,y,steps+1,floor[x][y]));
  steps=std::max(steps,basin_size(x,y+1,steps+1,floor[x][y]));
  std::cout << "step " << steps << ",";

  return steps;
}

int main ()
{


  std::ifstream is("day9.txt");
  std::string n;
  std::vector<std::string> raw;
  while (std::getline(is >> std::ws, n)) {
    raw.push_back(n);
  }

  for (auto l:raw) {
    std::vector<int> tmp;
    for (auto c:l) {
      tmp.push_back(c-'0');
    }
    floor.push_back(tmp);
  }

  visited = floor;
  for(auto &elem : visited) std::fill(elem.begin(), elem.end(), 0);

  for (auto l:floor) {
    for (auto c:l) {
      std::cout << c;
    }
    std::cout << std::endl;
  }

  std::vector<int> basins;
  for (auto x=0;x!=floor.size();++x) {
    for (auto y=0;y!=floor[0].size();++y) {
//      std::cout << floor[x][y];
      bool l=false,r=false,u=false,d=false;
      if (!x || (x && floor[x-1][y]>floor[x][y])) u=true;
      if (!y || (y && floor[x][y-1]>floor[x][y])) l=true;
      if (x==floor.size()-1 || (x<floor.size()-1 && floor[x+1][y] > floor[x][y])) d=true;
      if (y== floor[0].size()-1 || (y<floor[0].size()-1 && floor[x][y+1] > floor[x][y])) r=true;

      if (u && l && r && d) {
        std::cout << x << "," << y << ":" ;
        int totsize = basin_size(x,y,1,floor[x][y]);
        std::cout << " tot:" << totsize << std::endl;
        basins.push_back(totsize);
      }
    }
  }

  std::sort(basins.begin(),basins.end(),[](int a, int b){return b<a;});
  std::cout << basins[0] * basins[1] * basins[2] << std::endl;
  return 0;

}
