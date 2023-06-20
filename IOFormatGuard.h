#ifndef IOFMT_GUARD_H
#define IOFMT_GUARD_H

#include <iomanip>

class IOFormatGuard {
public:
  explicit IOFormatGuard(std::basic_ios< char >& s);
  ~IOFormatGuard();
private:
  std::basic_ios< char >& s_;
  char fill_;
  std::basic_ios< char >::fmtflags fmt_;
};
#endif