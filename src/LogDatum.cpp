#include <iostream>
#include <algorithm>
#include <map>
#include "LogDatum.h"
#include "split.h"

using std::ostream;
using std::istream;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::find_if;

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

Msgs LogDatum::timeOuts()
{
  return timeOuts(1);
}

bool isTimeOut(LogData l) { return l.getRespT() == "-";}
bool notTimeOut(LogData l) { return l.getRespT() != "-";}

map<string, vector<LogData> > divideByAddress(vector<LogData> ls)
{
  map<string, vector<LogData> > ret;
  for(auto it = ls.begin(); it != ls.end(); ++it) {
    ret[it -> getA()].push_back(*it);
  }
  return ret;
}

Msgs LogDatum::timeOuts(int N)
{
  typedef vector<LogData>::const_iterator iter;
  Msgs ret;
  // IPアドレスが同じLogDataの集まりに分ける
  const map<string, vector<LogData> > logByAddress = divideByAddress(val);
  for(auto it = logByAddress.begin(); it != logByAddress.end(); ++it) {
    vector<LogData> ls = it -> second;
    auto i = ls.begin();
    while(i != ls.end()) {
      // 始めのtimeOutしたLogDataを探す
      i = find_if(i, ls.end(), isTimeOut);
      // timeOutの終わりを探す
      auto j = find_if(i, ls.end(), notTimeOut);
      // [i, j)の範囲でN個以上timeOutがあれば ret に追加
      if (i != ls.end()) {
        int n = count_if(i, j, isTimeOut);
        if(n < N) {
          i = j; continue;
        }
        const string a = it -> first;
        if(j != ls.end())
          ret.push_back(a + ": [" + (i -> getD()) + ", " + (j -> getD()) + ")");
        else
          ret.push_back(a + ": [" + (i -> getD()) + ", )");
      }
      i = j;
    }
  }
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
