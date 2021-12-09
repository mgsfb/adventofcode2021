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

int main ()
{
  std::ifstream is("day3.txt");
  std::string n;
  std::vector<std::string> raw;
  while (std::getline(is >> std::ws, n)) {
    raw.push_back(n);
//    std::cout << n << " ";
  }

  std::cout << std::endl;
  std::vector<uint16_t> o2r;

  for (auto n: raw) {
    uint16_t temp=0;
    for (auto i=0;i!=n.size();++i) {
      if (n[i] == '1') temp |= 1;
      if (i<n.size()-1) temp<<=1;
    }

//    std::cout << n << " " << std::bitset<12>(temp) << ",";

    o2r.push_back(temp);
  }
//  std:: cout << std:: endl;
  std::vector<uint16_t> co2r (o2r);

  uint16_t mask = 0x800, o2_final=0, co2_final=0;

  while (mask)
  {
    std::sort(o2r.begin(),o2r.end());
    std::sort(co2r.begin(),co2r.end());
    std::vector<uint16_t> temp;
    int ocount=0,zcount=0;
    bool more_ones = false;
    if (o2r.size()>1)
    {
      for (auto n: o2r)
      {
        if (n & mask) ocount++;
        else zcount++;

//        if (mask == 2048) std::cout << std::bitset<12>(n) << " " << mask << " " << count << std::endl;
      }

      more_ones = (ocount >= zcount);

      for (auto n: o2r)
      {
        if ((more_ones && (mask & n)) || (!more_ones && !(mask & n)))
        {
          temp.push_back(n);
//          std::cout << std::bitset<12>(n) << ",";
        }
      }
      std::cout << std::endl;

//      std::cout << "o2r: " << mask << " " << zcount << " " << ocount << " " << o2r.size() << " " << temp.size() << std::endl;
      o2r.swap(temp);
      temp.clear();

    }

    ocount=0;
    zcount=0;
    if (co2r.size()>1)
    {
      for (auto n: co2r)
      {
        if (n & mask) ocount++;
        else zcount++;
      }

      more_ones = (ocount >= zcount);

      for (auto n:co2r)
      {
        if ((more_ones && !(mask & n)) || (!more_ones && (mask & n)))
        {
          temp.push_back(n);
          std::cout << std::bitset<12>(n) << ",";
        }
      }
      std::cout << std::endl;

      std::cout << "co2r: " << mask<< " " << zcount << " " << ocount << " " << co2r.size() << " " << temp.size() << std::endl;
      co2r.swap(temp);
      temp.clear();
    }

    mask >>=1;
  }

  std::cout << o2r[0] << " " << co2r[0] << std::endl;
  std::cout << (o2r[0] * co2r[0]) << std::endl;

  return 0;
}
