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
/*
[({(<(())[]>[[{[]{<()<>>
[(()[<>])]({[<{<<[]>>(
{([(<{}[<>[]}>{[]{[(<()>
(((({<>}<{<{<>}{[]{[]{}
[[<[([]))<([[{}[[()]]]
[{[{({}]{}}([{[{{{}}([]
{<[[]]>}<{[{[{[]{()[[[]
[<(<(<(<{}))><([]([]()
<{([([[(<>()){}]>(<<{{
<{([{{}}[<[[[<>{}]]]>[]]
*/

std::map<char,char> brac;

/*
multiply the total score by 5 and then increase the total score by the point value given for the character in the following table:

): 1 point.
]: 2 points.
}: 3 points.
>: 4 points.
*/

std::map<char,int> fail;

int main ()
{
  brac['[']=']';
  brac['(']=')';
  brac['{']='}';
  brac['<']='>';

  fail[')']=1;
  fail[']']=2;
  fail['}']=3;
  fail['>']=4;

  std::ifstream is("day10.txt");
  std::string n;
  std::vector<std::string> raw;
  while (std::getline(is >> std::ws, n)) {
    raw.push_back(n);
  }

  std::vector<long long> tots;
  long long tot=0;
  for (auto l:raw) {
    std::stack<char> next;
    for (auto c:l) {
      if (brac.find(c) != brac.end()) next.push(brac[c]);
      else if (c == next.top()) next.pop();
      else {
        while (next.size()) next.pop();
        break;
      }
    }
    while(next.size()) {
      tot*=5;
      tot+=fail[next.top()];
      std::cout << next.top();
      next.pop();
    }
    if (tot) {
      tots.push_back(tot);
      std::cout << "::" << tot <<std::endl;
    }
    tot=0;
  }


  std::sort(tots.begin(),tots.end());

  size_t mid = tots.size()/2;
  std::cout << tots[mid] << std::endl;

  return 0;

}

// }}]])})]
// }}]])})]
