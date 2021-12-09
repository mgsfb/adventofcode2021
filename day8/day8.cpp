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
#include <map>

std::map<char,unsigned int> conv_map;

void reset_map (void) {
  conv_map['a']=0b1111111;
  conv_map['b']=0b1111111;
  conv_map['c']=0b1111111;
  conv_map['d']=0b1111111;
  conv_map['e']=0b1111111;
  conv_map['f']=0b1111111;
  conv_map['g']=0b1111111;
}

/*
   0:      1:      2:      3:      4:
 aaaa    ....    aaaa    aaaa    ....
b    c  .    c  .    c  .    c  b    c
b    c  .    c  .    c  .    c  b    c
 ....    ....    dddd    dddd    dddd
e    f  .    f  e    .  .    f  .    f
e    f  .    f  e    .  .    f  .    f
 gggg    ....    gggg    gggg    ....

  5:      6:      7:      8:      9:
 aaaa    aaaa    aaaa    aaaa    aaaa
b    .  b    .  .    c  b    c  b    c
b    .  b    .  .    c  b    c  b    c
 dddd    dddd    ....    dddd    dddd
.    f  e    f  .    f  e    f  .    f
.    f  e    f  .    f  e    f  .    f
 gggg    gggg    ....    gggg    gggg

              gfedcba
2 - 1 (1)     0100100
3 - 1 (7)     0100101 (1&3 gives a) (3&5 == 3)
4 - 1 (4)     0101110 (4&6 == 9)
5 - 3 (2,3,5) 1011101, 1101101, 1101011
6 - 3 (0,6,9) 1110111, 1111011, 1101111, if (2 & 6 are diff == 6) : if 2 6s aren't equal c,d,e are missing.
7 - 1 (8)     1111111
*/

int main ()
{
  std::ifstream is("day8.txt");
  std::istream_iterator<std::string> start(is), end;
  std::vector<std::string> words(start,end);

  std::map<unsigned int,int> bin2char_map;
  std::map<int,unsigned int> char2bin_map;

  int out =0;

  std::vector<std::vector<std::string>> lines;
  std::vector<std::vector<std::string>> ends;
  std::vector<std::string> temp;
  std::vector<std::string> tempEnd;
  int endCt =0, lastFour=0;
  for (auto com: words) {
    std::sort(com.begin(),com.end());
    if (com != "|") {
      temp.push_back(com);
      if (lastFour) tempEnd.push_back(com);
      endCt+=lastFour;

      if (endCt==4) {
        std::sort(temp.begin(),temp.end(),[](std::string a,std::string b) {return a.size()<b.size();});
        lines.push_back(temp);
        ends.push_back(tempEnd);
        temp.clear();
        tempEnd.clear();
        endCt=0;
        lastFour=0;
      }
    } else {
      lastFour=1;
    }
  }

  bin2char_map[0b0100100]=1;
  bin2char_map[0b0100101]=7;
  bin2char_map[0b0101110]=4;
  bin2char_map[0b1011101]=2;
  bin2char_map[0b1101101]=3;
  bin2char_map[0b1101011]=5;
  bin2char_map[0b1110111]=0;
  bin2char_map[0b1111011]=6;
  bin2char_map[0b1101111]=9;
  bin2char_map[0b1111111]=8;

  std::string all = "abcdefg";

  for (auto i=0;i!=lines.size();i++) {
    reset_map();
    std::set<char> allFives;
    std::set<char> someFives;
    std::vector<std::string> fives;
    std::vector<std::string> sixes;
    std::set<char> allSixes;
    std::set<char> someSixes;
    for (auto w:lines[i]) {
      switch (w.size()) {
        case 2:
          conv_map[w[0]] &= 0b0100100;
          conv_map[w[1]] &= 0b0100100;
          for (auto c: all) {
            if (w.find(c) == std::string::npos) conv_map[c] &=0b1011011;
          }
          break;

        case 3:
          conv_map[w[0]] &= 0b0100101;
          conv_map[w[1]] &= 0b0100101;
          conv_map[w[2]] &= 0b0100101;
          for (auto c: all) {
            if (w.find(c) == std::string::npos) conv_map[c] &=0b1011010;
          }
          break;

        case 4:
          conv_map[w[0]] &= 0b0101110;
          conv_map[w[1]] &= 0b0101110;
          conv_map[w[2]] &= 0b0101110;
          conv_map[w[3]] &= 0b0101110;
          for (auto c: all) {
            if (w.find(c) == std::string::npos) conv_map[c] &=0b1010001;
          }
          break;

        case 5:
          if (allFives.size() == 0 ) for (auto c:w) allFives.insert(c);
          else {
            for (auto c:w) {
              if (allFives.find(c) == allFives.end()) someFives.insert(c);
            }
            std::string tmp;
            for (auto c:allFives) tmp+=c;
            for (auto c:tmp) {
              if (w.find(c) == std::string::npos) {
                someFives.insert(c);
                allFives.erase(c);
              }
            }
          }

          fives.push_back(w);
          break;

        case 6:
          if (allSixes.size() == 0 ) for (auto c:w) allSixes.insert(c);
          else {
            for (auto c:w) {
              if (allSixes.find(c) == allSixes.end()) someSixes.insert(c);
            }
            std::string tmp;
            for (auto c:allSixes) tmp+=c;
            for (auto c:tmp) {
              if (w.find(c) == std::string::npos) {
                someSixes.insert(c);
                allSixes.erase(c);
              }
            }
          }

          sixes.push_back(w);
          break;

        case 7:
          break;
      }
    }

    // fives
    unsigned int allmask = 0, somemask =0;
    if (allFives.size()==4) {
      allmask = 0b1001101;
      somemask = 0b0110000;
    } else if (allFives.size()==3) {
      allmask =  0b1001001;
      somemask = 0b0110110;
    }

    if (allmask) {
      for (auto c:allFives) {
        conv_map[c] &=allmask;
      }

      for (auto c:all) {
        if(allFives.find(c) == allFives.end()) conv_map[c] &= ~allmask;
      }

      for (auto c:someFives) {
        conv_map[c] &=somemask;
      }
    }

    // sixes
    if (allSixes.size()==4) {
      allmask =  0b1100011;
      somemask = 0b0011100;
    }

    if (allmask) {
      for (auto c:allSixes) {
        conv_map[c] &=allmask;
      }

      for (auto c:all) {
        if(allSixes.find(c) == allSixes.end()) conv_map[c] &= ~allmask;
      }

      for (auto c:someSixes) {
        conv_map[c] &=somemask;
      }
    }

    for (auto c: all) {
      std::cout << c << ":" << conv_map[c] << ",";
    }

    int place=1000,result=0;

    for (auto w:ends[i]) {
      unsigned int tmp=0;
      for (auto c:w) {
        tmp |= conv_map[c];
      }
      std::cout << w << ":" << tmp << " " << bin2char_map[tmp] << "!!";
      result+=(bin2char_map[tmp]*place);
      place/=10;
    }
    out+=result;
    std::cout << std::endl;

  }
  std::cout << out << std::endl;

  return 0;
}
