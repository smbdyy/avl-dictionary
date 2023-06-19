#ifndef IOFMT_GUARD_H
#define IOFMT_GUARD_H

#include <iomanip>

class iofmtguard {
public:
  explicit iofmtguard(std::basic_ios< char >& s);
  ~iofmtguard();
private:
  std::basic_ios< char >& s_;
  char fill_;
  std::basic_ios< char >::fmtflags fmt_;
};
#endif