// day 1, advent of code
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <tuple>
#include <string>

int main ()
{
  std::string com, dummy;
  int amt=0;

  std::ifstream is("day2.txt");
  std::vector<std::tuple<std::string, int>> data;

  int x=0,y=0;
  int aim =0;

  while (std::getline(is >> std::ws, com, ' ') >> amt)
  {
    int d = com.length();

    switch (d) {
      case 2:
        aim-=amt;
        break;
      case 4:
        aim+=amt;
        break;
      case 7:
        x+=amt;
        y+=(amt*aim);
        break;
    }

    std::cout << d << amt << " " << "x=" << x << " " << "y=" << y << std::endl;
  }

  std::cout << (x*y) << std::endl;
  return 0;
}
