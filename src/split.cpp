#include <vector>
#include <string>
#include "split.h"

using std::vector;  using std::string;

vector<string> split(const string& str, char c)
{
  typedef string::const_iterator iter;
  vector<string> ret;
  iter i = str.begin();
  while (i != str.end()) {
    // 始めにcがあればそれらは無視する
    i = find_if(i, str.end(), [=](char _c) {return _c != c;});
    // 次の単語の終わりを探す
    iter j = find(i, str.end(), c);
    // [i, j)の範囲の文字をコピー
    if (i != str.end())
      ret.push_back(string(i, j));
    i = j;
  }
  return ret;
}
