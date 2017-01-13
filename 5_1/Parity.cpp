#include <iostream>
#include <sstream>
#include <map>
using namespace std;

std::map<unsigned int, short> parityCache;

short Parity(unsigned long x){
  short result = 0;
  while(x){
    result ^= (x & 1);
    x >>= 1;
  }
  return result;
}

short parityUsingParityCache(unsigned long x) {
  short result = 0;
  const int kWordSize = 16;
  const int kBitmask = 0xFFFF;
  result = parityCache[x >> (3 * kWordSize)];
  result ^= parityCache[x >> (2 * kWordSize) & kBitmask];
  result ^= parityCache[(x >> kWordSize) & kBitmask];
  result ^= parityCache[x & kBitmask];
  return result;
}

void buildParityCache() {
  std::map<unsigned int, short> cache;
  short number = std::numeric_limits<short>::max();
  short result = 0;
  while(number) {
    result = Parity(number);
    cache[number] = result;
    number--;
  }
  cout << "Size of parity cache " << cache.size() << endl;
  parityCache = cache;
}

int main(int argc, char *argv[]) {
  buildParityCache();
  unsigned long number = 50;
  while(number) {
    short result = parityUsingParityCache(number);
    cout << "Parity of " << number << " is " << result  << endl;
    number--;
  }
  return 0;
}
