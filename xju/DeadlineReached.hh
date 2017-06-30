#ifndef _XJU_DEADLINEREACHED_HH
#define _XJU_DEADLINEREACHED_HH
// Copyright (c) 2017 Trevor Taylor
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all.
// Trevor Taylor makes no representations about the suitability of this
// software for any purpose.  It is provided "as is" without express or
// implied warranty.
//
#include "xju/Exception.hh"

namespace xju
{
class DeadlineReached : public xju::Exception
{
public:
  explicit DeadlineReached(xju::Exception const& x) throw();

  explicit DeadlineReached(xju::Exception&& x) throw();

  
};

  
}
#endif
