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

std::vector<uint64_t> ct_letters (std::map<std::string,uint64_t> &dbl, char b, char e)
{
  std::vector<uint64_t> out (26,0);
  for (auto p: dbl) {
    out[p.first[0]-'A']+=p.second;
    out[p.first[1]-'A']+=p.second;
    std::cout << p.first[0] << "," << p.first[1] << ": " << p.second << std::endl;
  }
  out[b-'A']++;
  out[e-'A']++;

  for (auto &n:out) n=n/2;
  return out;
}

int main ()
{
  std::ifstream is("day14.txt");

  std::map<std::string,std::string> prs;
  std::map<std::string,uint64_t> ct;
  char ends[2];

  // everything appears twice except the ends, which never change. add one of those each round.
/*
After step 1: NCNBCHBB - NC CN NB BC CH HB BN BB - N-2 C-2 B-2 H-1 - NB BC / CC CN / NB BB / BB BC / CB BH / HC CB
step 1: BB:2  BC:2  BH:1  BN:1  CC:1  CH:1  CN:2  HB:2  HH:1  NB:2  NC:1  count: 18
After step 2: NB CC NB BB CB HC B - NB BC / CN NC / CN NB BB BB BC HC CB -
After step 3: NB BB CN CC NB BN BN BB CH BH HB CH B
After step 4: NBBNBNBBCCNBCNCCNBBNBBNBBBNBBNBBCBHCBHHNHCBBCBHCB

Template:     NNCB -> N CCNNBBCCHH B
After step 1: N CNBCH B -> N CC NN BB CC HH B -> B-3 C-4 H-2 N-3
After step 2: NBCCNBBBCBHCB -> N BB BB BB CC NN CC CC NN BB BB NN BB NN BB BB CC HH BB HH HH BB CC HH B -> B-21
After step 3: NBBBCNCCNBBNBNBBCHBHHBCHB
After step 4: NBBNBNBBCCNBCNCCNBBNBBNBBBNBBNBBCBHCBHHNHCBBCBHCB
*/


  std::string pr,tem;

  std::getline(is >> std::ws, tem);
  std::vector<std::string> tmp (3,"");
  while (std::getline(is >> std::ws, tmp[0],' ') >> tmp[1] >> tmp[2]) {
    if (tmp[0].size()<1 || tmp[2].size()<1) continue;
    prs[tmp[0]]=tmp[2];
  }

  std::vector<uint64_t> h_freq (26,0);
  std::cout << "setup: " << std::endl;
  for (auto i=0; i < tem.size()-1; ++i) {
    std::string pol=tem.substr(i,2);
    std::string mid = prs[pol];
    ct[pol[0]+mid]++;
    ct[mid+pol[1]]++;
    std::cout << pol[0]+mid << "," << mid+pol[1] << std::endl;
  }

  for (auto steps=0; steps!=39; ++steps) {
    std::map<std::string,uint64_t> ct_new;

    for (auto p : ct) {
      std::string mid = prs[p.first];
      ct_new[p.first[0]+mid]+=p.second;
      ct_new[mid+p.first[1]]+=p.second;
    }
    std:: cout << "step " << steps << ": ";
    ct=ct_new;
    int count=0;
    for (auto p : ct) {
      std::cout << p.first << ":" << p.second << "  ";
      count+=p.second;
    }
    std::cout << "count: " << count+1 << std::endl;
  }

  h_freq = ct_letters (ct,tem[0],tem.back());

  uint64_t lil=UINT64_MAX,big=0;

  for (auto i=0; i!= h_freq.size(); i++) {
    uint64_t f = h_freq[i];
    if (h_freq[i]) std::cout << (char)('A'+i) << ": "<< h_freq[i] << ",";
    if (h_freq[i]) lil = lil < f ? lil : f;
    big = big > f ? big : f;
  }
  std::cout << std::endl;
  std::cout << big << "- " << lil << "= " << big-lil << std::endl;

  return 0;
}
