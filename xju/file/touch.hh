#ifndef _XJU_FILE_TOUCH_HCP
#define _XJU_FILE_TOUCH_HCP
// Copyright (c) 2017 Trevor Taylor
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all.
// Trevor Taylor makes no representations about the suitability of this
// software for any purpose.  It is provided "as is" without express or
// implied warranty.
//
#include <sys/types.h>
#include <xju/path.hh>

namespace xju
{
namespace file
{
void touch(std::pair<xju::path::AbsolutePath,xju::path::FileName> const& f,
           mode_t mode)
  throw(xju::Exception);


}
}
#endif
