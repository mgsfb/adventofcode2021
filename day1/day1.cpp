// day 1, advent of code
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

int main ()
{
  std::ifstream is("day1.txt");
  std::istream_iterator<int> start(is), end;
  std::vector<int> numbers(start, end);

  int old = numbers[0]+numbers[1]+numbers[2];
  int total =0;

  for (auto n=3;n<numbers.size();n++) {
    int curr = old - numbers[n-3] + numbers[n];
    if (curr>old) total++;
    old=curr;
  }

  std::cout << total << std::endl;

  return 0;
}
