#include <iostream>
#include "LogDatum.h"

using std::ostream;
using std::istream;
using std::endl;
using std::vector;
using std::string;

ostream& operator<<(ostream& os, const Msgs& msgs)
{
  for(Msgs::const_iterator iter = msgs.begin();
      iter != msgs.end(); ++iter) {
    os << (*iter) << endl;
  }
  return os;
}

istream& operator>>(istream& is, LogDatum& l)
{
  return is;
}

Msgs LogDatum::timeOuts()
{
  Msgs ret = {"Hello", "timeOuts"};
  return ret;
}

Msgs LogDatum::timeOuts(int N = 1)
{
  Msgs ret = {"Hello", "timeOuts"};
  return ret;
}

Msgs LogDatum::overLoads(int m, int t)
{
  Msgs ret = {"Hello", "overLoads"};
  return ret;
}

Msgs LogDatum::timeOutsBySubnets(int N)
{
  Msgs ret = {"Hello", "timeOutsBySubnet"};
  return ret;
}
