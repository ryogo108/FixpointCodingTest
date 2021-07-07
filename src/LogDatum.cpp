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

const double INF = 1e9;

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

string subnet(string s)
{
  vector<string> ss = split(s, '/');
  int subnetMask = stoi(ss[1]);
  vector<string> IPAddress = split(s, '.');
  string ret;
  for(int i = 0; i < 4; ++i) {
    if(i > 0) ret += ".";
    if(subnetMask - 8 * i >= 8) {
      ret += IPAddress[i];
      continue;
    }
    else if(subnetMask - 8 * i > 0) {
      int b = subnetMask - 8 * i;
      unsigned char a = stoi(IPAddress[i]);
      unsigned char r = 0;
      for(int j = 1; j <= b; ++j) {
        r += (a & 1<<(8 - j));
      }
      ret += std::to_string(r);
      continue;
    }
    ret += "0";
  }
  return ret;
}

map<string, vector<LogData> > divideBySubnets(vector<LogData> ls)
{
  map<string, vector<LogData> > ret;
  for(auto it = ls.begin(); it != ls.end(); ++it) {
    ret[subnet(it -> getA())].push_back(*it);
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

double averageRespTime(vector<LogData> ls)
{
  if(ls.empty()) {
    std::cerr << "ls is empty." << std::endl;
    return 0;
  }
  if(find_if(ls.begin(), ls.end(), isTimeOut) != ls.end()) return INF;
  double ret = 0;
  for(auto it = ls.begin(); it != ls.end(); ++it) {
    ret += double(stoi(it -> getRespT()));
  }
  return ret / double(ls.size());
}

// LogDatum の 中の LogData i が OverLoaded であるとは
// 自身も含め過去の直近m個のLogDataの応答時間の平均がt以上である、
// または timeOutが少なくとも一つあることとする。
Msgs LogDatum::overLoads(int m, int t)
{
  Msgs ret;
  // IPアドレスが同じLogDataの集まりに分ける
  const map<string, vector<LogData> > logByAddress = divideByAddress(val);
  for(auto it = logByAddress.begin(); it != logByAddress.end(); ++it) {
    vector<LogData> ls = it -> second;
    vector<LogData>::const_iterator i = ls.begin() + (m - 1);
    while(i != ls.end()) {
      // 始めのOverLoadedしたLogDataを探す
      for(auto e = i + 1; (e - 1) != ls.end(); ++e) {
        double avg = averageRespTime(vector<LogData>(e - m, e));
        if(avg >= t) {
          i = e - 1;
          break;
        }
        if(e == ls.end()) i = ls.end();
      }
      // OverLoadedの終わりを探す
      vector<LogData>::const_iterator j = ls.end();
      for(auto e = i + 1; (e - 1) != ls.end(); ++e) {
        double avg = averageRespTime(vector<LogData>(e - m, e));
        if(avg < t) {
          j = e - 1;
          break;
        }
      }
      // [i, j)を ret に追加
      if (i != ls.end()) {
        const string a = it -> first;
        if(j != ls.end())
          ret.push_back("OverLoaded: " + a + ": [" + (i -> getD()) + ", " + (j -> getD()) + ")");
        else
          ret.push_back("OverLoaded: " + a + ": [" + (i -> getD()) + ", )");
      }
      i = j;
    }
  }
  return ret;
}

Msgs LogDatum::timeOutsBySubnets(int N)
{
  typedef vector<LogData>::const_iterator iter;
  Msgs ret;
  // サブネットが同じLogDataの集まりに分ける
  const map<string, vector<LogData> > logBySubnets = divideBySubnets(val);
  for(auto it = logBySubnets.begin(); it != logBySubnets.end(); ++it) {
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
        const string sub = it -> first;
        if(j != ls.end())
          ret.push_back("timeOut in the subnet " + sub + ": [" + (i -> getD()) + ", " + (j -> getD()) + ")");
        else
          ret.push_back("timeOut in the subnet " + sub + ": [" + (i -> getD()) + ", )");
      }
      i = j;
    }
  }
  return ret;
}

void LogDatum::push_back(LogData l) {
  this->val.push_back(l);
}
