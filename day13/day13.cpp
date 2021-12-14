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


int main ()
{
  std::set<std::vector<int>> pts;
  std::vector<std::pair<char,int>> folds;
  std::ifstream is("day13.txt");
  std::string input;

  int a,b;
  while (std::getline(is >> std::ws, input)) {
    if (std::isdigit(input[0])) {
      std::string t1;
      int a,b;
      for (auto c : input) {
        if (std::isdigit(c)) {
          t1+=c;
        } else {
          a=std::stoi(t1);
          t1="";
        }
      }
      b=std::stoi(t1);
      pts.insert({a,b});
    } else {
      char t1;
      std::string t2;
      bool edge = false;
      for (auto c: input) {
        if (c=='x' || c=='y') t1=c;
        if (edge && std::isdigit(c)) t2+=c;
        if (c=='=') edge=true;
      }
      folds.push_back(std::make_pair(t1,std::stoi(t2)));
    }
  }
// reflect across y = fold, 0,0 is upper left. y=fold means fold up
//  for y > fold x_new=x, y_new= fold-(y-fold) (while y>0);

  std::vector<int> min_fold (2,10000);
  for (auto f:folds) {
    std::set<std::vector<int>> new_pts;
    size_t dex=0; // 0==x
    if (f.first=='y') {
      dex=1;
    }
    min_fold[dex] = min_fold[dex] < f.second ? min_fold[dex] : f.second;
    for (auto p: pts) {
      auto pnew =p;
      if (p[dex]>f.second) {
        pnew[dex]=(f.second-(p[dex]-f.second));
      }
      if (pnew[dex] >=0) new_pts.insert(pnew);
    }
    pts = new_pts;
    new_pts.clear();
  }

  for (auto x=0; x<=min_fold[0]; ++x) {
    for (auto y=0; y<=min_fold[1]; ++y) {
      if (pts.find({x,y}) !=pts.end()) std::cout << '#';
      else std::cout << '.';
    }
    std::cout << std:: endl;
  }


  return 0;
}
