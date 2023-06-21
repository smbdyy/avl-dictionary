#include "IOFormatGuard.h"

IOFormatGuard::IOFormatGuard(std::basic_ios<char>& stream) :
    stream_(stream),
    fill_(stream.fill()),
    flags_(stream.flags())
{}

IOFormatGuard::~IOFormatGuard()
{
    stream_.fill(fill_);
    stream_.flags(flags_);
}