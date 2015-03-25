// Copyright (c) 2014 Trevor Taylor
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all.
// Trevor Taylor makes no representations about the suitability of this
// software for any purpose.  It is provided "as is" without express or
// implied warranty.
//


#include "p4.hh"
#include "p4.cref.hh"
#include "p4.sref.hh"

#include <xju/Exception.hh>
#include <iostream>
#include <string>
#include <xju/format.hh>
#include <xju/stringToInt.hh>
#include <stdlib.h>
#include <xju/mt.hh>
#include <xju/Time.hh>
#include <cxy/ORB.hh>
#include "xju/Shared.hh"
#include <unistd.h>

std::string makeURI(int port, std::string const& objectName) throw()
{
  std::ostringstream s;
  s << "corbaloc:iiop:localhost:"<< port << "/" << objectName;
  return s.str();
}

class F_impl : public p4::F
{
public:
  ~F_impl() throw()
  {
  }
  
  // p4::F::
  virtual ::p4::XS1 f1(
    ::p4::XS1 const& y) throw(cxy::Exception)
  {
    std::cout << "::p4::f1(XS1(" 
              << y.a_ << ", "
              << y.b_ << ")) -> ::p4::f1(XS1(" 
              << ::p3::MyInt(62) << ", "
              << std::string("jock") << "))" << std::endl;
    calls_.push_back(xju::Shared<Call>(
                       new Call::f1(y)));
    return ::p4::XS1(::p3::MyInt(62), std::string("jock"));
  }

  // p4::F::
  virtual ::p4::F::XxPair f2(
    ::p4::F::XxPair const& z) throw()
  {
    std::cout << "::p4::f2(XxPair("
              << z.first << ", "
              << z.second << ") -> XxPair(-3, \"f2\")" << std::endl;
    calls_.push_back(xju::Shared<Call>(
                       new Call::f2(z)));
    return XxPair(-3, "f2");
  }

  struct Call
  {
    virtual ~Call() throw()
    {
    }
    struct f1;
    struct f2;
  };
  struct Call::f1 : Call
  {
    ~f1() throw()
    {
    }
    f1(::p4::XS1 const& a) throw():
        a_(a) {
    }
    ::p4::XS1 a_;
    
    friend bool operator==(f1 const& x, f1 const& y) throw()
    {
      return x.a_ == y.a_;
    }
  };
  struct Call::f2 : Call
  {
    ~f2() throw()
    {
    }
    f2(::p4::F::XxPair const& a) throw():
        a_(a) {
    }
    ::p4::F::XxPair a_;
    
    friend bool operator==(f2 const& x, f2 const& y) throw()
    {
      return x.a_ == y.a_;
    }
  };
  std::vector<xju::Shared<Call> > calls_;
};

int main(int argc, char* argv[])
{
  try {
    if (argc != 3 || !(std::string("client")==argv[2]||
                       std::string("loop-client")==argv[2]||
                       std::string("server")==argv[2]||
                       std::string("both")==argv[2])) {
      std::cerr << "usage:  " 
                << argv[0] << " <ip-port> [client|server|both]" << std::endl;
      return 1;
    }
    
    std::string const OBJECT_NAME("p4");
    
    int const port(xju::stringToInt(argv[1]));
    
    if (argv[2]==std::string("client")) {
      cxy::ORB<cxy::Exception> orb("giop:tcp::");
      cxy::cref<p4::F> ref(orb, makeURI(port, OBJECT_NAME));
      ::p4::XS1 const r(
        ref->f1(::p4::XS1(::p3::MyInt(77),std::string("argy"))));
      std::cout << "::p4::XS1(::p3::MyInt("<<r.a_<<"), "<<r.b_<<")"
                << std::endl;
      {
        ::p4::F::XxPair const r(
          ref->f2(::p4::F::XxPair(18,std::string("argz"))));
        std::cout << "::p4::F::XxPair("<<r.first<<"), "<<r.second<<")"
                  << std::endl;
      }
    }
    else if (argv[2]==std::string("loop-client")) {
      cxy::ORB<cxy::Exception> orb("giop:tcp::");
      cxy::cref<p4::F> ref(orb, makeURI(port, OBJECT_NAME));
      ::p4::XS1 const r(
        ref->f1(::p4::XS1(::p3::MyInt(77),std::string("argy"))));
      std::cout << "::p4::XS1(::p3::MyInt("<<r.a_<<"), "<<r.b_<<")"
                << std::endl;
      while(true)
      {
        ::p4::F::XxPair const r(
          ref->f2(::p4::F::XxPair(18,std::string("argz"))));
        std::cout << "::p4::F::XxPair("<<r.first<<"), "<<r.second<<")"
                  << std::endl;
        ::sleep(1);
      }
    }
    else if (argv[2]==std::string("server")) {
      std::string const orbEndPoint="giop:tcp::"+xju::format::str(port);
      cxy::ORB<cxy::Exception> orb(orbEndPoint);

      F_impl x;
      
      cxy::sref<p4::F> const xa(orb, OBJECT_NAME, x);
      
      orb.monitorUntil(xju::Time::now()+xju::MicroSeconds(30*1000000));
    }
    else
    {
      std::string const orbEndPoint="giop:tcp::"+xju::format::str(port);
      cxy::ORB<cxy::Exception> orb(orbEndPoint);
      F_impl x;
      
      cxy::sref<p4::F> const xa(orb, OBJECT_NAME, x);
      
      cxy::cref<p4::F> ref(orb, makeURI(port, OBJECT_NAME));
      xju::assert_equal(ref->f1(::p4::XS1(::p3::MyInt(19),std::string("al"))),
                        ::p4::XS1(::p3::MyInt(62),std::string("jock")));
      xju::assert_equal(x.calls_.size(),1U);
      {
        F_impl::Call::f1 const& c(
          dynamic_cast<F_impl::Call::f1 const&>(*x.calls_[0]));
        xju::assert_equal(c,
                          F_impl::Call::f1(
                            ::p4::XS1(::p3::MyInt(19),std::string("al"))));
      }
      xju::assert_equal(ref->f2(::p4::F::XxPair(18,std::string("argz"))),
                        ::p4::F::XxPair(-3,std::string("f2")));
      xju::assert_equal(x.calls_.size(),2U);
      {
        F_impl::Call::f2 const& c(
          dynamic_cast<F_impl::Call::f2 const&>(*x.calls_[1]));
        xju::assert_equal(c,
                          F_impl::Call::f2(
                            ::p4::F::XxPair(18,std::string("argz"))));
      }
    }
    return 0;
  }
  catch(xju::Exception& e) {
    e.addContext(xju::format::join(argv, argv+argc, " "), XJU_TRACED);
    std::cerr << readableRepr(e) << std::endl;
    return 1;
  }
  catch(cxy::Exception& e) {
    e.addContext(xju::format::join(argv, argv+argc, " "), 
                 std::make_pair(__FILE__, __LINE__));
    std::cerr << readableRepr(e, true, false) << std::endl;
    return 1;
  }
}
