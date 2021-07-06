#include <gtest/gtest.h>
#include <fstream>
#include "../src/LogDatum.h"

using std::ifstream;

bool operator==(const Msgs& m1, const Msgs& m2)
{
  if(m1.size() != m2.size()) return false;
  for(int i = 0; i < m1.size(); ++i) {
    if(m1[i] != m2[i]) return false;
  }
  return true;
}

TEST(LogDatumTest, TimeOuts1Test)
{
  LogDatum l;
  ifstream ifs("TestCase1");
  ifs >> l;
  Msgs expect = {"Hello", "TimeOuts"};
  EXPECT_EQ(expect, l.timeOuts());
}
