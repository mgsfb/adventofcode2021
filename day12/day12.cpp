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

// bidirectional map of cave.
// stack of path vectors;
// pop top
// push vector + new cave for each legal (not a lower-case cave already visited) unless it's the end
// if it's the end, increment paths.


int main ()
{
  std::multimap<std::string,std::string> cave;
  std::ifstream is("day12.txt");
  std::string n;
  std::vector<std::string> raw;
  while (std::getline(is >> std::ws, n)) {
    std::string a;
    std::string b;

    bool first = true;
    for(auto c:n) {
      if (c=='-') {
        first=false;
        continue;
      }
      if (first) a+=c;
      else b+=c;
    }

    cave.insert({a,b});
    cave.insert({b,a});
  }

  std::stack<std::vector<std::string>> paths;
  paths.push({"start"});
  int tot_paths =0;

  while (paths.size()) {

    auto it = cave.equal_range(paths.top().back());
    std::vector<std::string> curr = paths.top();
    paths.pop();
    for(auto i = it.first; i!= it.second; ++i) {
      std::vector<std::string> tmp = curr;
      if (i->second == "end") {
        tot_paths++;
        continue;
      }
      int max_lil = 2;
      for (auto c : tmp) {
        if (islower(c[0]) && std::count(tmp.begin(),tmp.end(),c) > 1) max_lil = 1;
      }
      if (isupper((i->second)[0]) || (i->second != "start" && std::count(tmp.begin(),tmp.end(),i->second) < max_lil)) {
        tmp.push_back(i->second);
        paths.push(tmp);
      }
    }
  }

  std::cout << tot_paths << std::endl;
  return 0;
}
