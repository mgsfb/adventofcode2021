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

int main ()
{


  std::ifstream is("day5.txt");
  std::string n;
  std::vector<std::string> raw;

  std::vector<std::vector<int>> horz;
  std::vector<std::vector<int>> vert;
  std::vector<std::vector<int>> diag;

  while (std::getline(is >> std::ws, n)) {
    std::vector<std::string> line(4);
    std::vector<int> vals;
    int dex=0, delim = 0;
    for (auto c:n)
    {
      if (std::isdigit(c)) {
        dex+=delim;
        delim=0;
        line[dex]+=c;
      } else {
        delim = 1;
      }
    }

    for (auto i=0;i!=line.size();i++) {
      vals.push_back(stoi(line[i]));
    }

    if (vals[0] > vals[2] || vals[1] > vals[3]) {
      std::swap(vals[0],vals[2]);
      std::swap(vals[1],vals[3]);
    }

    if (vals[0] == vals[2]) horz.push_back(vals);
    else if (vals[1] == vals[3]) vert.push_back(vals);
    else diag.push_back(vals);
  }

  std::sort(horz.begin(),horz.end());

  std::vector<std::vector<int>> board (1000, std::vector<int> (1000,0));
  int accum =0;

  for (auto i=0;i!=vert.size();i++) {
    for (auto j=vert[i][0];j<=vert[i][2];j++) {
      if (++board[j][vert[i][1]] == 2) {
        accum++;
      }
    }
  }

  for (auto i=0;i!=horz.size();i++) {
    for (auto j=horz[i][1];j<=horz[i][3];j++) {
      if (++board[horz[i][0]][j] == 2) {
        accum++;
      }
    }
  }

  for (auto i=0;i!=diag.size();i++) {
    int deltax = diag[i][2]-diag[i][0];
    deltax /= std::abs(deltax);
    int deltay = diag[i][3]-diag[i][1];
    deltay /= std::abs(deltay);

    int x = diag[i][0];
    int y = diag[i][1];

    while (x!=(deltax+diag[i][2]) && y!=(deltay+diag[i][3])) {
      if (++board[x][y] == 2) accum++;
      x+=deltax;
      y+=deltay;
    }
  }

  std::cout << "yes:" << accum << std::endl;
  return 0;
}
