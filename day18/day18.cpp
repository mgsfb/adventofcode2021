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
#include <deque>

int main ()
{
  std::ifstream is("day18test2.txt");

  std::vector<std::string> rawLines;
  std::string currLine;

  while (std::getline(is >> std::ws, currLine))
  {
    rawLines.push_back(currLine);
  }

  currLine = "[" + rawLines[0];
  for (auto i=1; i!=rawLines.size()-1; ++i)
  {
    currLine += "," + rawLines[i] + "]";
    std::cout << "input: " << currLine << std::endl;
    std::deque<char> snailIn(currLine.begin(),currLine.end());
    std::deque<char> snailOut;

    int nstLvl=0;
    int flags =0;
    while (snailIn.size()) {
      std::cout << "snailIn.size :" << snailIn.size() << std::endl;
      std::stack<char> tmpStack;
      std::string tmpS;
      int tmpI=0,newL=0,newR=0;
      char tmpC = snailIn.front();
      snailIn.pop_front();
      switch (tmpC) {
        case ('['):
          nstLvl++;
          snailOut.push_back(tmpC);
          break;

        case (']'):
          nstLvl--;
          snailOut.push_back(tmpC);
          break;

        case (','):
          snailOut.push_back(tmpC);
          break;

        default:
          if (std::isdigit(snailIn.front())) {  //split
            std::cout << "SPLIT!" << std::endl;
            tmpS = tmpC+snailIn.front();
            tmpI = std::stoi(tmpS);
            newL = tmpI/2;
            newR = newL + (tmpI & 1);
            snailIn.pop_front();
            tmpS =   ']' + (char)(newR+'0') + ',' + (char)(newL+'0') + '[';
            for (auto c: tmpS) snailIn.push_front(c);
          } else if (nstLvl>4) {  //explode - this could be simpler.
            // first, add. We're at the left number.
            // go left
            std::cout << "EXPLODE! " <<  nstLvl << std::endl;
            snailIn.push_front(tmpC); // put the current number back
            while (snailOut.size() && !std::isdigit(snailOut.back())) {
              tmpStack.push(snailOut.back());
              snailOut.pop_back();
            }
            if (snailOut.size()) {
              tmpI= (tmpC-'0')+(snailOut.back()-'0');
              snailOut.pop_back();
              if (tmpI > 9) {
                flags++;
                tmpS = (char)((tmpI/10)+'0') + (char)((tmpI%10)+'0');
                for (auto c: tmpS) snailOut.push_back(c);
              } else {
                snailOut.push_back((char)(tmpI+'0'));
              }
              while (tmpStack.size()) {
                snailOut.push_back(tmpStack.top());
                tmpStack.pop();
              }
            }
            // still at left num. go right.
            tmpStack.push(tmpC);
            // find right num - exploding numbers "always appear in pairs"

            while (!std::isdigit(snailIn.front()))
            {
              tmpStack.push(snailIn.front());
              snailIn.pop_front();
            }

            tmpC = snailIn.front();
            tmpStack.push(tmpC);
            snailIn.pop_front();

            while (snailIn.size() && !std::isdigit(snailIn.front()))
            {
              tmpStack.push(snailIn.front());
              snailIn.pop_front();
            }

            if (snailIn.size()) {
              tmpI = (tmpC-'0') + (snailIn.front()-'0');
              snailIn.pop_front();
              if (std::isdigit(snailIn.front())) {  // this should never happen
                std::cout << "NEVER!!" << std::endl;
                tmpI+=snailIn.front()-'0';
                snailIn.pop_front();
              }
              if (tmpI > 9) {
                flags++;
                tmpS = (char)((tmpI/10)+'0') + (char)((tmpI%10)+'0');
                for (auto c: tmpS) snailIn.push_front(c);
              } else {
                snailIn.push_front((char)(tmpI+'0'));
              }
              while (tmpStack.size()) {
                snailIn.push_front(tmpStack.top());
                tmpStack.pop();
              }
            }

            // back at left num
            // now convert.
            while (snailIn.front()!='[') {
              snailIn.push_front(snailOut.back());
              snailOut.pop_back();
            }

            char popped;
            while (popped!=']') {
              popped = snailIn.front();
              snailIn.pop_front();
            }

            nstLvl--;
            snailIn.push_front('0');
            if (flags) {
              flags--;
              while (snailOut.size())
              {
                snailIn.push_front(snailOut.back());
                snailOut.pop_back();
              }
              nstLvl =0;
            } else {
              while (snailIn.front()!='[')
              {
                snailIn.push_front(snailOut.back());
                snailOut.pop_back();
              }
            }
          } else {
            snailOut.push_back(tmpC);
          }

      }
    }
    if (i<rawLines.size()-1) currLine="[";
    while (snailOut.size()) {
      currLine+=snailOut.front();
      snailOut.pop_front();
    }
    std::cout << currLine << std::endl;
  }





//  while (std::isdigit(c[ptr])) a+=c[ptr++];
  for (auto l: rawLines) std::cout << l << std::endl;
  std::cout << currLine << std::endl;
  return 0;
}

/*
The final sum of this list is [[[[5,0],[7,4]],[5,5]],[6,6]]:

[1,1]
[2,2]
[3,3]
[4,4]
[5,5]
[6,6]

[[1,1],[2,2]]
[[[1,1],[2,2]],[3,3]]
[[[[1,1],[2,2]],[3,3]],[4,4]]
[[[[[1,1],[2,2]],[3,3]],[4.4]],[5,5]]
-- ...[1,1],[3... --> [[[[0,[3,2]]...
-- [[[[3,[3,2]],[5,3]],[4,4]],[5,5]] --> [[[[3,0],[5,3]],[4,4]],[5,5]]
add, then reduce.
[[[[[3,0],[5,3]],[4,4]],[5,5]],[6,6]]
-- [[[[[3,0],[5,3]]... --> [[[[0,[5,3]],[4,4]... --> [[[[5,[5,3]],[7,4]],[5,5]],[6,6]] --> [[[[5,0],[7,4]],[5,5]],[6,6]]

To reduce a snailfish number, you must repeatedly do the first action in this list that applies to the snailfish number:

check if any pair is nested inside four pairs, the leftmost such pair explodes. (so, the fifth.)
If any regular number is 10 or greater, the leftmost such regular number splits.

During reduction, at most one action applies, after which the process returns to the top of the list of actions.
For example, if split produces a pair that meets the explode criteria, that pair explodes before other splits occur.

To explode a pair, the pair's left value is added to the first regular number to the left of the exploding pair (if any),
and the pair's right value is added to the first regular number to the right of the exploding pair (if any).
Exploding pairs will always consist of two regular numbers. Then, the entire exploding pair is replaced with the regular number 0.

Here are some examples of a single explode action:

[[[[[9,8],1],2],3],4] becomes [[[[0,9],2],3],4]
[9,8] is four levels deep
do the addition
9 + nothing = nothing
8 + 1 = 9 [[[[[9,8],9],2],3],4]
[9,8] -> 0
[[[[0,9],2],3],4]

(the 9 has no regular number to its left, so it is not added to any regular number).
[7,[6,[5,[4,[3,2]]]]] becomes [7,[6,[5,[7,0]]]] (the 2 has no regular number to its right, and so it is not added to any regular number).
[[6,[5,[4,[3,2]]]],1] becomes [[6,[5,[7,0]]],3].
[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]] becomes [[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]] (the pair [3,2] is unaffected because the pair [7,3] is further to the left; [3,2] would explode on the next action).
[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]] becomes [[3,[2,[8,0]]],[9,[5,[7,0]]]].

To split a regular number, replace it with a pair; the left element of the pair should be the regular number divided by two and rounded down,
while the right element of the pair should be the regular number divided by two and rounded up. For example, 10 becomes [5,5], 11 becomes [5,6], 12 becomes [6,6], and so on.
*/
