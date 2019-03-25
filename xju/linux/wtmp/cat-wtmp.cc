// Copyright (c) 2019 Trevor Taylor
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all.
// Trevor Taylor makes no representations about the suitability of this
// software for any purpose.  It is provided "as is" without express or
// implied warranty.
//
#include <xju/linux/wtmp/LoginLogoutMonitor.hh>
#include <xju/steadyNow.hh>
#include <sstream>
#include <xju/format.hh>


int main(int argc, char* argv[])
{
  if (argc!=1){
    std::cerr << "usage: " << argv[0] << " <wtmp-file-name>\n";
    return 1;
  }
  try{
    auto const fileName{xju::path::split(argv[1])};
    xju::linux::wtmp::LoginLogoutMonitor m{fileName};

    auto const events{m.readEventsUntilDeadline(xju::steadyNow())};
    for (auto e: events){
      //REVISIT
    };
    return 0;
  }
  catch(xju::Exception& e){
    std::ostringstream s;
    s << xju::format::join(argv,argv+argc,std::string(" "));
    e.addContext(s.str(),XJU_TRACED);
    throw;
  }
}