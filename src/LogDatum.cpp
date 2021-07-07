#include <iostream>
#include "LogDatum.h"
#include "split.h"

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

istream& operator>>(istream& is, LogData& l)
{
  if(!is) return is;
  string str;
  is >> str;
  vector<string> strs = split(str, ',');
  if(strs.size() != 3) return is;
  l.d = strs[0];
  l.a = strs[1];
  l.RespT = (strs[2] == "-") ? -1 : stoi(strs[2]);

  return is;
}

istream& operator>>(istream& is, LogDatum& ls)
{
  if(!is) return is;
  LogData l;
  while(is >> l) ls.push_back(l);
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

void LogDatum::push_back(LogData l) {
  this->val.push_back(l);
}
