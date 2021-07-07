#ifndef GUARD_LogDatum_h
#define GUARD_LogDatum_h
// LogDatum.h

#include <vector>
#include <string>
#include <set>

using Msgs = std::vector<std::string>;
std::ostream& operator<<(std::ostream&, const Msgs&);

class LogData {
public:
  friend std::istream& operator>>(std::istream&, LogData&);

  LogData() {}
  LogData(std::string _d, std::string _a, std::string _t) : d(_d), a(_a), RespT(_t) {}

  std::string getD() const { return d; };
  std::string getA() const { return a; };
  std::string getRespT() const { return RespT; };
private:
  std::string d;
  std::string a;
  std::string RespT;
};

double averageRespTime(std::vector<LogData> ls);

class LogDatum {
public:
  friend std::istream& operator>>(std::istream&, LogDatum&);

  LogDatum() {}
  LogDatum(const std::vector<LogData>& v) : val(v) {}
  Msgs timeOuts();
  Msgs timeOuts(int);
  Msgs overLoads(int, int);
  Msgs timeOutsBySubnets(int);

  void push_back(LogData);

private:
  std::vector<LogData> val;
  std::set<std::string> addresses() const;
};

#endif
