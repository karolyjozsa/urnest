#ifndef _OMNICXY_PROTO_CXY_P2_HCP_286120_HCP
#define _OMNICXY_PROTO_CXY_P2_HCP_286120_HCP
// generated from p2.idl by omni cxy idl backend specifying 
// cxy::Exception from <cxy/Exception.hh> as base class for all ipc exceptions

#include <cxy/Exception.hh>
#include <string>
#include <stdint.h>

// included idl
#include <omnicxy/proto/cxy/p1.hh>

namespace p2
{
class F 
{
public:
  virtual ~F() throw();

  virtual void f1(
    int16_t const& a,
    int32_t const& b,
    double const& c,
    std::string const& d,
    uint8_t const& e,
    uint64_t const& f,
    bool const& g) throw(
    // ipc failure
    // - note servant may not throw
    cxy::Exception) = 0;
  virtual int16_t f2() throw(
    // ipc failure
    // - note servant may not throw
    cxy::Exception) = 0;
};

}
#endif
