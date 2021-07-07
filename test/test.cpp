#include <gtest/gtest.h>
#include <fstream>
#include "../src/LogDatum.h"

using std::ifstream;
using std::vector;
using std::string;

bool operator==(const Msgs& m1, const Msgs& m2)
{
  if(m1.size() != m2.size()) return false;
  for(int i = 0; i < m1.size(); ++i) {
    if(m1[i] != m2[i]) return false;
  }
  return true;
}

TEST(LogDatumTest, averageRespTimeTest)
{
  vector<LogData> l = vector<LogData>({LogData("a", "d", "10"), LogData("a", "d", "10")});
  vector<LogData> l1 = vector<LogData>({LogData("a", "d", "3"),
                                        LogData("a", "d", "5"),
                                        LogData("a", "d", "10")});
  vector<LogData> l2 = vector<LogData>({LogData("a", "d", "-"),
                                        LogData("a", "d", "5"),
                                        LogData("a", "d", "10")});
  vector<LogData> l3 = vector<LogData>();
  double expect = 10;
  double expect1 = 6.0;
  double expect2 = 1e9;
  double expect3 = 0;
  EXPECT_EQ(expect, averageRespTime(l));
  EXPECT_EQ(expect1, averageRespTime(l1));
  EXPECT_EQ(expect2, averageRespTime(l2));
  EXPECT_EQ(expect3, averageRespTime(l3));
}

TEST(LogDatumTest, subnetTest)
{
  string s1 = "10.20.30.1/16";
  string s2 = "192.168.1.1/24";
  string expect1 = "10.20.0.0";
  string expect2 = "192.168.1.0";
  EXPECT_EQ(expect1, subnet(s1));
  EXPECT_EQ(expect2, subnet(s2));
}

TEST(LogDatumTest, TimeOuts1Test1)
{
  LogDatum l;
  ifstream is("test/TestCase1");
  is >> l;
  Msgs expect = {"timeOut: 10.20.30.1/16: [20201019133125, 20201019133225)"};
  EXPECT_EQ(expect, l.timeOuts());
}

TEST(LogDatumTest, TimeOuts1Test2)
{
  LogDatum l;
  ifstream is("test/TestCase2");
  is >> l;
  Msgs expect = {"timeOut: 10.20.30.1/16: [20201019133124, 20201019133224)",
                 "timeOut: 10.20.30.1/16: [20201019133225, )",
                 "timeOut: 192.168.1.1/24: [20201019133134, 20201019133235)"};
  EXPECT_EQ(expect, l.timeOuts());
}

TEST(LogDatumTest, TimeOuts2Test1)
{
  LogDatum l;
  ifstream is("test/TestCase1");
  is >> l;
  Msgs expect1 = {"timeOut: 10.20.30.1/16: [20201019133125, 20201019133225)"};
  Msgs expect2 = {"timeOut: 10.20.30.1/16: [20201019133125, 20201019133225)"};
  Msgs expect3 = {};
  EXPECT_EQ(expect1, l.timeOuts(1));
  EXPECT_EQ(expect2, l.timeOuts(2));
  EXPECT_EQ(expect3, l.timeOuts(3));
}

TEST(LogDatumTest, TimeOuts2Test2)
{
  LogDatum l;
  ifstream is("test/TestCase2");
  is >> l;
  Msgs expect1 = {"timeOut: 10.20.30.1/16: [20201019133124, 20201019133224)",
                 "timeOut: 10.20.30.1/16: [20201019133225, )",
                 "timeOut: 192.168.1.1/24: [20201019133134, 20201019133235)"};
  Msgs expect2 = {"timeOut: 10.20.30.1/16: [20201019133124, 20201019133224)",
                 "timeOut: 10.20.30.1/16: [20201019133225, )",
                 "timeOut: 192.168.1.1/24: [20201019133134, 20201019133235)"};
  Msgs expect3 = {"timeOut: 10.20.30.1/16: [20201019133225, )",
                  "timeOut: 192.168.1.1/24: [20201019133134, 20201019133235)"};
  Msgs expect4 = {};
  EXPECT_EQ(expect1, l.timeOuts(1));
  EXPECT_EQ(expect2, l.timeOuts(2));
  EXPECT_EQ(expect3, l.timeOuts(3));
  EXPECT_EQ(expect4, l.timeOuts(4));
}

TEST(LogDatumTest, OverLoadsTest1)
{
  LogDatum l;
  ifstream is("test/TestCase1");
  is >> l;
  Msgs expect1 = {"overLoaded: 10.20.30.1/16: [20201019133125, 20201019133225)"};
  Msgs expect2 = {"overLoaded: 10.20.30.1/16: [20201019133125, )"};
  Msgs expect3 = {"overLoaded: 10.20.30.1/16: [20201019133224, )"};
  EXPECT_EQ(expect1, l.overLoads(1, 500));
  EXPECT_EQ(expect2, l.overLoads(2, 500));
  EXPECT_EQ(expect3, l.overLoads(3, 500));
}

TEST(LogDatumTest, OverLoadsTest2)
{
  LogDatum l;
  ifstream is("test/TestCase3");
  is >> l;
  Msgs expect2_500 = {"overLoaded: 10.20.30.1/16: [20201019133125, 20201019133224)"};
  Msgs expect2_400 = {"overLoaded: 10.20.30.1/16: [20201019133125, 20201019133224)",
                      "overLoaded: 192.168.1.1/24: [20201019133135, )"};
  Msgs expect2_300 = {"overLoaded: 10.20.30.1/16: [20201019133125, 20201019133224)",
                      "overLoaded: 10.20.30.1/16: [20201019133325, )",
                      "overLoaded: 192.168.1.1/24: [20201019133135, )"};
  Msgs expect4_500 = {};
  Msgs expect4_400 = {"overLoaded: 192.168.1.1/24: [20201019133235, )"};
  Msgs expect4_300 = {"overLoaded: 192.168.1.1/24: [20201019133235, )"};
  EXPECT_EQ(expect2_500, l.overLoads(2, 500));
  EXPECT_EQ(expect2_400, l.overLoads(2, 400));
  EXPECT_EQ(expect2_300, l.overLoads(2, 300));
  EXPECT_EQ(expect4_500, l.overLoads(4, 500));
  EXPECT_EQ(expect4_400, l.overLoads(4, 400));
  EXPECT_EQ(expect4_300, l.overLoads(4, 300));
}

TEST(LogDatumTest, TimeOutsBySubnetsTest1)
{
  LogDatum l;
  ifstream is("test/TestCase1");
  is >> l;
  Msgs expect1 = {"timeOut in the subnet 10.20.0.0: [20201019133125, 20201019133225)"};
  Msgs expect2 = {"timeOut in the subnet 10.20.0.0: [20201019133125, 20201019133225)"};
  Msgs expect3 = {};
  Msgs expect4 = {};
  EXPECT_EQ(expect1, l.timeOutsBySubnets(1));
  EXPECT_EQ(expect2, l.timeOutsBySubnets(2));
  EXPECT_EQ(expect3, l.timeOutsBySubnets(3));
  EXPECT_EQ(expect4, l.timeOutsBySubnets(4));
}

TEST(LogDatumTest, TimeOutsBySubnetsTest2)
{
  LogDatum l;
  ifstream is("test/TestCase4");
  is >> l;
  Msgs expect1 = {"timeOut in the subnet 10.20.0.0: [20201019133124, 20201019133225)",
                  "timeOut in the subnet 10.20.0.0: [20201019133324, 20201019133325)",
                  "timeOut in the subnet 192.168.1.0: [20201019133134, 20201019133234)",
                  "timeOut in the subnet 192.168.1.0: [20201019133235, )",
                  };
  Msgs expect2 = {"timeOut in the subnet 10.20.0.0: [20201019133124, 20201019133225)",
                  "timeOut in the subnet 192.168.1.0: [20201019133134, 20201019133234)",
                  };
  Msgs expect3 = {"timeOut in the subnet 10.20.0.0: [20201019133124, 20201019133225)",};
  Msgs expect4 = {};
  EXPECT_EQ(expect1, l.timeOutsBySubnets(1));
  EXPECT_EQ(expect2, l.timeOutsBySubnets(2));
  EXPECT_EQ(expect3, l.timeOutsBySubnets(3));
  EXPECT_EQ(expect4, l.timeOutsBySubnets(4));
}
