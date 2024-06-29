#include "genString.h"
#include "gtest/gtest.h"
#include "swar.h"

#include <ctime>
#include <random>
#include <string>

class CountOnesTest : public testing::Test {
 protected:
  CountOnesTest() = default;

  ~CountOnesTest() override = default;
};

void doCountOnesTest(int n) {
  std::string str = generateRandomString(n);
  long long redisLen = redisPopcount((void *)str.c_str(), n);
  long long basicLen = basicPopcount((const unsigned char *)str.c_str(), n);
  long long bitAndLen = bitAndPopcount((const unsigned char *)str.c_str(), n);
  long long gccAndLen = gccBuildinPopCount((const unsigned char *)str.c_str(), n);
  long long openmpBasicLen = openmpBasicPopCount((const unsigned char *)str.c_str(), n);
  EXPECT_EQ(redisLen, basicLen);
  EXPECT_EQ(redisLen, bitAndLen);
  EXPECT_EQ(redisLen, gccAndLen);
  EXPECT_EQ(redisLen, openmpBasicLen);
}

TEST_F(CountOnesTest, BasicTest) {
  int n = 1000000;
  doCountOnesTest(n);
}

TEST_F(CountOnesTest, StrongTest) {
  int times = 1000;
  for (int i = 0; i < times; ++i) {
    int n = (i + 1) * (i + 1);
    doCountOnesTest(n);
  }
}
