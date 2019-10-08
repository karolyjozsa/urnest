// Copyright (c) 2019 Trevor Taylor
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all.
// Trevor Taylor makes no representations about the suitability of this
// software for any purpose.  It is provided "as is" without express or
// implied warranty.
//
#include <xju/uri/pctEncode.hh>

#include <iostream>
#include <xju/assert.hh>

namespace xju
{
namespace uri
{

void test1() {

  xju::assert_equal(pctEncode("abcdef",hcp::Chars("a-c")),"abc%64%65%66");
  xju::assert_equal(pctEncode("\tabc",hcp::Chars("a-c")),"%09abc");
}

}
}

using namespace xju::uri;

int main(int argc, char* argv[])
{
  unsigned int n(0);
  test1(), ++n;
  std::cout << "PASS - " << n << " steps" << std::endl;
  return 0;
}

