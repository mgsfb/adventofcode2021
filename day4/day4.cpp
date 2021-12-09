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

struct board {
  int val[5][5];
};

void set_board (board &b,int n)
{
  for(auto i=0;i!=5;i++)
  {
    for (auto j=0;j!=5;j++)
    {
      if (b.val[j][i] == n) b.val[j][i]=999;
    }
  }
}

int test_board (board b)
{
  bool win=false;
  int accum =0;
  for(auto i=0;i!=5;i++)
  {
    bool htrue=true;
    bool vtrue=true;
    for (auto j=0;j!=5;j++)
    {
      if (b.val[i][j]!=999) accum+=b.val[i][j];
      htrue=htrue & (b.val[j][i]==999);
      vtrue=vtrue & (b.val[i][j]==999);

    }
    if (htrue || vtrue) win=true;
  }
  return win ? accum : 0;
}

int main ()
{


  std::ifstream is("day4.txt");
  std::string n;
  std::vector<std::string> raw;
  while (std::getline(is >> std::ws, n)) {
    raw.push_back(n);
  }

  std::cout << raw[0] << std::endl;
  std::vector<int> nums;
  std::stringstream s(raw[0]);
  while (s.good())
  {
    std::string sub;
    std::getline(s,sub,',');
    nums.push_back(std::stoi(sub));
  }

  std::vector<board> boards;

  for (auto i=1;i!=raw.size();++i)
  {
    board tmp;
    if ((i-1)%5 == 0) boards.push_back(tmp);
    std::stringstream s1(raw[i]);
    size_t dex=0;
    while(s1.good())
    {
      std::string sub;
      std::getline(s1 >> std::ws,sub,' ');
      boards[(i-1)/5].val[dex++][(i-1)%5]= (std::stoi(sub));
    }
  }

  std::set<int> still_losing;
  for (int i = 0; i < boards.size(); ++i) still_losing.insert(still_losing.end(), i);
  int win=0;


  for (auto n : nums)
  {
    for (auto &b:boards) set_board(b,n);
    for (auto i=0;i!=boards.size();++i)
    {
      int a = 0;
      if (still_losing.find(i) != still_losing.end()) a=test_board(boards[i]);
      if (a) {
        still_losing.erase(i);
        win=a*n;
      }
    }
  }

  std::cout << win << std::endl;
  return 0;

}
