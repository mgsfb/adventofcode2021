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
#include <cctype>

int main ()
{
  std::ifstream is("day7.txt");
  std::string com;
  std::vector<long> pos;
  long tot=0;

  while (std::getline(is >> std::ws, com, ',')) {
    long val = std::stoi(com);
    val;
    pos.push_back(val);
    tot+= val;
  }

  std::vector<long> cost (2000,0);

  for (auto v: pos) {
    for (auto c=0;c!=cost.size();++c) {
      long temp = std::abs(v-c);
      temp *= temp+1;
      temp /=2;
      cost[c]+=temp;
    }
  }

  std::sort(cost.begin(),cost.end());

  std::cout << cost[0] << std::endl;
  return 0;
}
