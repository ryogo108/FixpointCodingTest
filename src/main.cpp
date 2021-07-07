#include <iostream>
#include "LogDatum.h"

using std::cin;   using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
  int N1 = atoi(argv[1]), m = atoi(argv[2]), t = atoi(argv[3]), N2 = atoi(argv[4]);
  cout << "N1 = " << N1 << endl
       << "m = " << m << endl
       << "t = " << t << endl
       << "N2 = " << N2 << endl;
  LogDatum l;
  cin >> l;
  // Prob1
  cout << "Prob1: " << endl;
  cout << l.timeOuts() << endl;

  // Prob2
  cout << "Prob2: " << endl;
  cout << l.timeOuts(N1) << endl;

  // Prob3
  cout << "Prob3: " << endl;
  cout << l.overLoads(m, t) << endl;

  // Prob4
  cout << "Prob4: " << endl;
  cout << l.timeOutsBySubnets(N2) << endl;

  return 0;
}
