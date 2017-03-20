#ifndef _XJU_HOLDER_HCP
#define _XJU_HOLDER_HCP
// Copyright (c) 2015 Trevor Taylor
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all.
// Trevor Taylor makes no representations about the suitability of this
// software for any purpose.  It is provided "as is" without express or
// implied warranty.
//

#include <cinttypes>
#include <cstddef>


namespace xju
{

//
// object holder for use with placement new, eg:
//   Holder<X> h;
//     :
//   X* x=new(h) X(3);
//   x->~X();
//
template<class T>
class Holder
{
public:
  union H // for correct alignment
  {
    short a_;
    int b_;
    long c_;
    long long d_;
    void* e_;
    uint8_t f_[sizeof(T)];
  };
  H x_;
};

}

template<class T>
void* operator new(std::size_t, xju::Holder<T>& holder) throw()
{
  return &holder.x_;
}
#endif