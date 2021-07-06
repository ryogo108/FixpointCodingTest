#include <iostream>
#include "LogDatum.h"

using std::cin;   using std::cout;
using std::endl;

int main()
{
  int N, m, t;
  LogDatum l;
  cin >> l;
  // Prob1
  cout << "Prob1: " << endl;
  cout << l.timeOuts();

  // Prob2
  cout << "Prob2: " << endl;
  cout << l.timeOuts(N);

  // Prob3
  cout << "Prob3: " << endl;
  cout << l.overLoads(m, t);

  // Prob4
  cout << "Prob4: " << endl;
  cout << l.timeOutsBySubnets(N);

  return 0;
}
