#include <iostream>
#include <algorithm>
#include <set>
#include "LogDatum.h"
#include "split.h"

using std::ostream;
using std::istream;
using std::endl;
using std::vector;
using std::string;
using std::find_if;
using std::set;

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
  l.RespT = strs[2];

  return is;
}

istream& operator>>(istream& is, LogDatum& ls)
{
  if(!is) return is;
  LogData l;
  while(is >> l) ls.push_back(l);
  return is;
}

set<string> LogDatum::addresses() const
{
  set<string> ret;
  for(vector<LogData>::const_iterator it = val.begin();
      it != val.end(); ++it) {
    ret.insert(it -> getA());
  }
  return ret;
}

Msgs LogDatum::timeOuts()
{
  typedef vector<LogData>::const_iterator iter;
  Msgs ret;
  const set<string> as = addresses();
  const vector<LogData>& v = val;
  for(set<string>::const_iterator it = as.begin(); it != as.end(); ++it) {
    string a = (*it);
    iter i = v.begin();
    // IPアドレスがaのLogDataのTimeOutの期間を探す
    while (i != v.end()) {
      // 始めのtimeOutしたLogDataを探す
      i = find_if(i, v.end(), [=](LogData l) {return l.getA() == a &&
                                                     l.getRespT() == "-";});
      // timeOutの終わりを探す
      iter j = find_if(i, v.end(), [=](LogData l) {return l.getA() == a &&
                                                          l.getRespT() != "-";});
      // [i, j)の範囲の文字をコピー
      if (i != v.end()) {
        if(j != v.end())
          ret.push_back(a + ": [" + (i -> getD()) + ", " + (j -> getD()) + ")");
        else
          ret.push_back(a + ": [" + (i -> getD()) + ", )");
      }
      i = j;
    }
  }
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
