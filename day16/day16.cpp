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

#define VER_SIZE  3
#define TYPE_ID_SIZE  3
#define LIT_NUM_SIZE  5
#define HEADER_SIZE 6
#define LENGTH_TYPE_0_SIZE  15
#define LENGTH_TYPE_1_SIZE  11

uint64_t parse_pkt (const std::string &binIn, int &binPtr, int &pSize);

std::string c_hex (char c) {
  switch (c) {
    default: return "";
    case '0': return "0000";
    case '1': return "0001";
    case '2': return "0010";
    case '3': return "0011";
    case '4': return "0100";
    case '5': return "0101";
    case '6': return "0110";
    case '7': return "0111";
    case '8': return "1000";
    case '9': return "1001";
    case 'A': return "1010";
    case 'B': return "1011";
    case 'C': return "1100";
    case 'D': return "1101";
    case 'E': return "1110";
    case 'F': return "1111";
  }
}


std::vector<std::string> get_header (std::string pkt, int &ptr)
{
  std::string ver = pkt.substr(ptr,VER_SIZE);
  ptr+=VER_SIZE;
  std::string type = pkt.substr(ptr,TYPE_ID_SIZE);
  ptr+=TYPE_ID_SIZE;
  std::string ltID = pkt.substr(ptr,1);  // not used if type == 4
  // ptr not moved past ltID
  return {ver,type,ltID};
}

// returns literal
uint64_t parse_literal (const std::string &binIn, int &binPtr)
{
  char inPt = binIn[binPtr];
  uint64_t lit = 0;
  std::string binlit;

  do {
    inPt = binIn[binPtr];
    binlit += binIn.substr(binPtr+1,4);
    binPtr+= LIT_NUM_SIZE;
  } while (inPt =='1');

  return std::stoull(binlit,nullptr,2);
}

std::vector<uint64_t> parse_elType (const std::string &binIn, int &binPtr, std::string elType)
{

    binPtr++; // ltId bit
    int bitsUsed=0;
    std::vector<uint64_t> outVec;
    std::cout << "elType!! " << elType << std::endl;
    if (elType=="0") {

      uint16_t length = std::stoi(binIn.substr(binPtr,LENGTH_TYPE_0_SIZE),nullptr,2);
      uint16_t initLength = length;
      binPtr+=LENGTH_TYPE_0_SIZE;

      while (length) {
        std:: cout << length << " of " << initLength << " bits remain. ";
        outVec.push_back(parse_pkt(binIn,binPtr,bitsUsed));
        length-=bitsUsed;
      }

    } else {
      int subPackets = std::stoi(binIn.substr(binPtr,LENGTH_TYPE_1_SIZE),nullptr,2);
      int initPkts = subPackets;
      binPtr+=LENGTH_TYPE_1_SIZE;
      while (subPackets) {
        std:: cout << subPackets << " of " << initPkts << " subpackets remain. ";
        outVec.push_back(parse_pkt(binIn,binPtr,bitsUsed));
        subPackets--;
      }
    }

  return outVec;
}

// returns packet value
uint64_t parse_pkt (const std::string &binIn, int &binPtr, int &pSize)
{
  int bitsIn = binPtr;
  std::vector<std::string> hdr = get_header(binIn,binPtr);
  uint64_t pkt_val = 0;

  int tID = std::stoi(hdr[1],nullptr,2);
  std::vector<uint64_t> outs = {};
  switch (tID) {
    default:
      break;

    case 0: // sum
      std::cout << "add: " ;
      outs = parse_elType (binIn, binPtr, hdr[2]);
      for (auto n:outs) pkt_val+=n;
      std::cout << "sum = " << pkt_val << std::endl;
      break;

    case 1: // product
      std::cout << "multiply: " ;
      pkt_val = 1;
      outs = parse_elType (binIn, binPtr, hdr[2]);
      for (auto n:outs) pkt_val*=n;
      std::cout << "product = " << pkt_val << std::endl;
      break;

    case 2: // minimum
      std::cout << "min: ";
      outs = parse_elType (binIn, binPtr, hdr[2]);
      pkt_val = outs[0];
      for (auto n:outs) pkt_val = pkt_val > n ? n : pkt_val;
      std::cout << "min: " << pkt_val << std::endl;
      break;

    case 3: //maximum
      std::cout << "max: ";
      outs = parse_elType (binIn, binPtr, hdr[2]);
      pkt_val = outs[0];
      for (auto n:outs) pkt_val = pkt_val < n ? n : pkt_val;
      std::cout << "max: " << pkt_val << std::endl;
      break;

    case 4: // literal
      pkt_val = parse_literal(binIn, binPtr);
      std::cout << "# " << pkt_val << std::endl;
      break;

    case 5: // >
      std::cout << "greater: ";
      outs = parse_elType (binIn, binPtr, hdr[2]);
      if (outs[0]>outs[1]) pkt_val = 1;
      std::cout << "greater? " << pkt_val << std::endl;
      break;

    case 6: // <
      std::cout << "less: ";
      outs = parse_elType (binIn, binPtr, hdr[2]);
      if (outs[0]<outs[1]) pkt_val = 1;
      std::cout << "less? " << pkt_val << std::endl;
      break;

    case 7: // ==
      std::cout << "equal: " ;
      outs = parse_elType (binIn, binPtr, hdr[2]);
      if (outs[0]==outs[1]) pkt_val = 1;
      std::cout << "equal? " << pkt_val << std::endl;
      break;


  }

  pSize = binPtr-bitsIn;
  return pkt_val;
}


int main ()
{
  std::ifstream is("day16.txt");
  std::string binIn;
  std::string hexIn;

  while (std::getline(is >> std::ws, hexIn)) for (auto c:hexIn) binIn+=c_hex(c);

  int binPtr = 0;
  int pSize =0;
  int bitsUsed;

  std::cout << binIn << std::endl;

  uint64_t val = parse_pkt (binIn, binPtr, bitsUsed);
  std::cout << val << std::endl;
  return 0;
}
