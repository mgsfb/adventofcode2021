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

std::vector<std::vector<int>> floor;
std::stack<std::pair<int,int>> flashes;

bool clean_up (void)
{
  bool all=true;
  for (auto x = 0;x!=floor.size();x++) {
    for (auto y=0;y!=floor[0].size(); y++) {
      if (floor[x][y]>9) floor[x][y]=0;
      else all=false;
    }
  }
  return all;
}

void flash_handler (int x, int y)
{
  if (x<0 || x>=floor.size()) return;
  if (y<0 || y>=floor[0].size()) return;
  if (floor[x][y]!=10 && ++floor[x][y]==10) flashes.push(std::make_pair(x,y));
}

int flash_math(void) {
  int ct =0;
  while(flashes.size()) {
    auto x_mid= flashes.top().first;
    auto y_mid= flashes.top().second;
    flashes.pop();
    ct++;
    for (auto x=x_mid-1; x<=x_mid+1; x++) {
      for (auto y=y_mid-1; y<=y_mid+1; y++) {
        flash_handler(x,y);
      }
    }


  }
  return ct;
}

void inc_floor(void) {
  for (auto x = 0;x!=floor.size();x++) {
    for (auto y=0;y!=floor[0].size(); y++) {
      flash_handler(x,y);
    }
  }
}

int main ()
{
  std::ifstream is("day11.txt");
  std::string n;
  std::vector<std::string> raw;
  while (std::getline(is >> std::ws, n)) {
    raw.push_back(n);
    std::cout << n << std::endl;
  }

  for (auto l:raw) {
    std::vector<int> tmp;
    for (auto c:l) {
      tmp.push_back(c-'0');
    }
    floor.push_back(tmp);
  }

  int flash_ct =0, steps=0;

  while (!clean_up()) {

    steps++;
    inc_floor();
    flash_ct+=flash_math();

    std::cout << "after step " << steps << ": " << std::endl;
    for (auto x = 0;x!=floor.size();x++) {
      for (auto y=0;y!=floor[0].size(); y++) {
        std::cout << floor[x][y];
      }
      std::cout << std::endl;
    }
    std::cout << "flashes:" << flash_ct << std::endl;
    std::cout << std::endl;
  }

  std::cout << steps << std::endl;
  return 0;

}
