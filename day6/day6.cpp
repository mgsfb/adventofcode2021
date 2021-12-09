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
  std::ifstream is("day6.txt");
  std::string com;
  std::vector<long long> fish(9,0);

  while (std::getline(is >> std::ws, com, ',')) {
    fish[(std::stoi(com))]++;
  }

  for (auto n:fish) std::cout << n << ",";
  std::cout << std::endl;

  int time=0;

  while (time < 256)
  {
    std::cout << "day " << time << ":";
    for (auto n:fish) std::cout << n << ",";
    std::cout << std::endl;

    std::vector<long long> temp (9,0);
    for (auto i=0;i!=temp.size();i++)
    {
      if (i>0) temp[i-1]+=fish[i];
      else {
        temp[6]+=fish[0];
        temp[8]+=fish[0];
      }
    }

    fish.swap(temp);
    time++;
//    std::cout << "after " << time << "days: ";
//    for (auto f:fish) std::cout << f << ",";
//    std::cout << std::endl;
  }

  long long accum =0;
  for (auto f:fish) accum+=f;

  std::cout << accum << std::endl;


  return 0;
}
