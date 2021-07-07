#ifndef GUARD_LogDatum_h
#define GUARD_LogDatum_h
// LogDatum.h

#include <vector>
#include <string>

using Msgs = std::vector<std::string>;
std::ostream& operator<<(std::ostream&, const Msgs&);

class LogData {
public:
  friend std::istream& operator>>(std::istream&, LogData&);
private:
  std::string d;
  std::string a;
  int RespT;
};

class LogDatum {
public:
  friend std::istream& operator>>(std::istream&, LogDatum&);
  Msgs timeOuts();
  Msgs timeOuts(int);
  Msgs overLoads(int, int);
  Msgs timeOutsBySubnets(int);

  void push_back(LogData);

private:
  std::vector<LogData> val;
};

#endif
