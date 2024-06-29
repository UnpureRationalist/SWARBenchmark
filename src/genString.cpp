#include "genString.h"

std::string generateRandomString(int n) {
  std::string randomString(n, 0);

  std::mt19937 generator(static_cast<unsigned long>(std::time(0)));
  std::uniform_int_distribution<int> distribution(0, 255);

  for (int i = 0; i < n; ++i) {
    char randomChar = static_cast<char>(distribution(generator));
    randomString[i] = randomChar;
  }

  return randomString;
}
