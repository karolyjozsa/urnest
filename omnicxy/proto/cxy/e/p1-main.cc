// Copyright (c) 2014 Trevor Taylor
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all.
// Trevor Taylor makes no representations about the suitability of this
// software for any purpose.  It is provided "as is" without express or
// implied warranty.
//


#include <omnicxy/proto/p1.hh>
#include <omnicxy/proto/p1.cref.hh>
#include <omnicxy/proto/p1.sref.hh>

#include <omnicxy/proto/cxy/e/E.hh>
#include <iostream>
#include <string>
#include<xju/format.hh>
#include<xju/stringToInt.hh>
#include <stdlib.h>
#include<xju/mt.hh>
#include <cxy/ORB.hh>

std::string makeURI(int port, std::string const& objectName) throw()
{
  std::ostringstream s;
  s << "corbaloc:iiop:localhost:"<< port << "/" << objectName;
  return s.str();
}

class F_impl : public p1::F
{
public:
  ~F_impl() throw()
  {
  }
  
  virtual void f1() throw(E)
  {
    std::cout << "F::f1()" << std::endl;
  }
};

  
int main(int argc, char* argv[])
{
  try {
    if (argc != 3 || !(std::string("client")==argv[2]||
                       std::string("server")==argv[2]||
                       std::string("both")==argv[2])) {
      std::cerr << "usage:  " 
                << argv[0] << " <ip-port> [client|server|both]" << std::endl;
      return 1;
    }
    
    std::string const OBJECT_NAME("p1");
    
    int const port(xju::stringToInt(argv[1]));
    
    if (argv[2]==std::string("client")) {
      cxy::ORB<E> orb("giop:tcp::");
      cxy::cref<p1::F> ref(orb, makeURI(port, OBJECT_NAME));
      ref->f1();
    }
    else if (argv[2]==std::string("server")) {
      std::string const orbEndPoint="giop:tcp::"+xju::format::str(port);
      cxy::ORB<E> orb(orbEndPoint);

      F_impl x;
      
      cxy::sref<p1::F> const xa(orb, OBJECT_NAME, x);
      
      orb.monitorUntil(xju::Time::now()+xju::MicroSeconds(30*1000000));
    }
    else
    {
      std::string const orbEndPoint="giop:tcp::"+xju::format::str(port);
      cxy::ORB<E> orb(orbEndPoint);

      F_impl x;
      
      cxy::sref<p1::F> const xa(orb, OBJECT_NAME, x);
      
      cxy::cref<p1::F> ref(orb, makeURI(port, OBJECT_NAME));
      ref->f1();
    }
    
    return 0;
  }
  catch(xju::Exception& e) {
    e.addContext(xju::format::join(argv, argv+argc, " "), XJU_TRACED);
    std::cerr << readableRepr(e) << std::endl;
    return 1;
  }
}
