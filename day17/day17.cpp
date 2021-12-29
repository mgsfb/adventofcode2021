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
#include <cstdlib>
#include <cmath>

int main ()
{
  std::ifstream is("day17.txt");
  std::string a,b,c,d;
  std::string hexIn;

  std::getline(is >> std::ws, a, ' ') >> b >> c >> d;
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << c << std::endl;
  std::cout << d << std::endl;

  int xMin,xMax,yMin,yMax;
  int ptr = 2;
  a="";
  while (std::isdigit(c[ptr])) a+=c[ptr++];
  ptr+=2;
  xMin = std::stoi(a);
  a="";
  while (std::isdigit(c[ptr])) a+=c[ptr++];
  ptr+=2;
  xMax = std::stoi(a);
  ptr=2;
  a=d[ptr++];
  while (std::isdigit(d[ptr])) a+=d[ptr++];
  ptr+=2;
  yMin = std::stoi(a);
  a=d[ptr++];
  while (std::isdigit(d[ptr])) a+=d[ptr++];
  ptr+=2;
  yMax = std::stoi(a);

  int xVMin=(int) std::sqrt(xMin*2);

  int yVMin = yMin;
  int yVMax = std::abs(yMin+1);

  int count =0;
  for (int xV =xVMin; xV<=xMax; xV++) {
    for (int yV=yVMin; yV<=yVMax; yV++) {
      int pX=0,pY=0;
      int vX=xV, vY=yV;
      while (pX<=xMax && pY>=yMin) {
        if (pX>=xMin && pX<=xMax && pY>=yMin && pY<=yMax) {
          count++;
          break;
        }
        pX += vX;
        if (vX>0) vX--;
        pY += vY;
        vY--;
      }
    }
  }

  std::cout << count << std::endl;
  return 0;
}
