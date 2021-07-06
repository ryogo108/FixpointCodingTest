#ifndef GUARD_LogDatum_h
#define GUARD_LogDatum_h
// LogDatum.h

#include <vector>
#include <string>

using Msgs = std::vector<std::string>;
std::ostream& operator<<(std::ostream&, const Msgs&);

class LogData {
};

class LogDatum {
public:
  friend std::istream& operator>>(std::istream&, LogDatum&);
  Msgs timeOuts();
  Msgs timeOuts(int);
  Msgs overLoads(int, int);
  Msgs timeOutsBySubnets(int);

private:
  std::vector<LogData> val;
};

#endif
