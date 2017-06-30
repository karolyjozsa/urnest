// Copyright (c) 2015 Trevor Taylor
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all.
// Trevor Taylor makes no representations about the suitability of this
// software for any purpose.  It is provided "as is" without express or
// implied warranty.
//
#include "xju/snmp/encode.hh"

#include <iostream>
#include <xju/assert.hh>
#include "xju/snmp/SnmpV1GetRequest.hh"
#include "xju/snmp/NullValue.hh"
#include "xju/snmp/SnmpV1SetRequest.hh"
#include "xju/snmp/SnmpV1GetNextRequest.hh"
#include "xju/snmp/SnmpV1Trap.hh"
#include "xju/snmp/IntValue.hh"
#include "xju/snmp/StringValue.hh"
#include "xju/snmp/SnmpV2cGetRequest.hh"
#include "xju/snmp/SnmpV2cSetRequest.hh"
#include "xju/snmp/SnmpV2cGetNextRequest.hh"

namespace xju
{
namespace snmp
{

void test1() throw()
{
  // encode(SnmpV1GetRequest)
  SnmpV1GetRequest r(
    Community("private"),
    RequestId(1),
    {Oid(".1.3.6.1.4.1.2680.1.2.7.3.2.0")});
  std::vector<uint8_t> x(encode(r));
  xju::assert_equal(
    x,
    std::vector<uint8_t>({
        0x30,0x2c,0x02,0x01,0x00,0x04,0x07,0x70,0x72,0x69,0x76,0x61,0x74,0x65,0xA0,0x1E,0x02,0x01,0x01,0x02,0x01,0x00,0x02,0x01,0x00,0x30,0x13,0x30,0x11,0x06,0x0D,0x2B,0x06,0x01,0x04,0x01,0x94,0x78,0x01,0x02,0x07,0x03,0x02,0x00,0x05,0x00
          }));
}

void test2() throw()
{
  // encode(SnmpV1SetRequest)
  SnmpV1SetRequest r(
    Community("private"),
    RequestId(1),
    {{Oid(".1.3.6.1.4.1.2680.1.2.7.3.2.0"),
          std::shared_ptr<Value const>(new NullValue)}});
  std::vector<uint8_t> x(encode(r));
  xju::assert_equal(
    x,
    std::vector<uint8_t>({
        0x30,0x2c,0x02,0x01,0x00,0x04,0x07,0x70,0x72,0x69,0x76,0x61,0x74,0x65,0xA3,0x1E,0x02,0x01,0x01,0x02,0x01,0x00,0x02,0x01,0x00,0x30,0x13,0x30,0x11,0x06,0x0D,0x2B,0x06,0x01,0x04,0x01,0x94,0x78,0x01,0x02,0x07,0x03,0x02,0x00,0x05,0x00
          }));
}

void test3() throw()
{
  // encode(SnmpV1GetNexRequest)
  SnmpV1GetNextRequest r(
    Community("private"),
    RequestId(1),
    {Oid(".1.3.6.1.4.1.2680.1.2.7.3.2.0")});
  std::vector<uint8_t> x(encode(r));
  xju::assert_equal(
    x,
    std::vector<uint8_t>({
        0x30,0x2c,0x02,0x01,0x00,0x04,0x07,0x70,0x72,0x69,0x76,0x61,0x74,0x65,0xA1,0x1E,0x02,0x01,0x01,0x02,0x01,0x00,0x02,0x01,0x00,0x30,0x13,0x30,0x11,0x06,0x0D,0x2B,0x06,0x01,0x04,0x01,0x94,0x78,0x01,0x02,0x07,0x03,0x02,0x00,0x05,0x00
          }));
}

void test4() throw()
{
  {
    // encode(SnmpV1Trap)
    SnmpV1Trap t(
      Community("private"),
      Oid(".1.3.6"),
      IPv4Address({192,168,0,3}),
      SnmpV1Trap::GenericType(6),
      SnmpV1Trap::SpecificType(42),
      xju::MicroSeconds(330000),
      {{Oid(".1.3.6.1.4.1.2680.1.2.7.3.2.0"),
            std::shared_ptr<Value const>(new IntValue(2))}});
    std::vector<uint8_t> x(encode(t));
    xju::assert_equal(
      x,
      std::vector<uint8_t>({
          0x30,55,
            0x02,0x01,0x00,//snmp v1
            0x04,0x07,'p','r','i','v','a','t','e',
            0xA4,41,//trap-pdu
            0x06,2,0x2B,6,//oid
            0x40,4,192,168,0,3, //origin
            0x02,1,6, //generic type
            0x02,1,42, //specific type
            0x43,1,33, //timestamp
            0x30,20, // vars:
            0x30,18, // var:
            0x06,0x0D,0x2B,6,1,4,1,0x94,0x78,1,2,7,3,2,0,//oid
            0x02,1,2 //value
            }));
  }
  {
    // encode(SnmpV1Trap)
    SnmpV1Trap t(
      Community("private"),
      Oid(".1.3.6"),
      IPv4Address({192,168,0,3}),
      SnmpV1Trap::GenericType(6),
      SnmpV1Trap::SpecificType(42),
      xju::MicroSeconds(330000),
      {{Oid(".1.3.6.1.4.1.2680.1.2.7.3.2.0"),
            std::shared_ptr<Value const>(new StringValue("Once apon a time there were three little pigs, who each wanted to build a house. The first little pig built a straw house, with straw from the field. The second little pig built a stick house, with sticks from the forest. The third little pig built a brick house, with bricks from the brick works."))}});
    std::vector<uint8_t> x(encode(t));
    xju::assert_equal(
      x,
      std::vector<uint8_t>({
          0x30, 0x82, 0x01, 0x67,
            0x02, 0x01, 0x00, 0x04, 0x07, 0x70, 0x72, 0x69, 0x76, 0x61, 0x74, 0x65, 0xa4, 0x82, 0x01, 0x57,
            0x06, 0x02, 0x2b, 0x06, 0x40, 0x04, 0xc0, 0xa8, 0x00, 0x03, 0x02, 0x01, 0x06, 0x02, 0x01, 0x2a,
            0x43, 0x01, 0x21, 0x30, 0x82, 0x01, 0x40, 0x30, 0x82, 0x01, 0x3c, 0x06, 0x0d, 0x2b, 0x06, 0x01,
            0x04, 0x01, 0x94, 0x78, 0x01, 0x02, 0x07, 0x03, 0x02, 0x00, 0x04, 0x82, 0x01, 0x29, 0x4f, 0x6e,
            0x63, 0x65, 0x20, 0x61, 0x70, 0x6f, 0x6e, 0x20, 0x61, 0x20, 0x74, 0x69, 0x6d, 0x65, 0x20, 0x74,
            0x68, 0x65, 0x72, 0x65, 0x20, 0x77, 0x65, 0x72, 0x65, 0x20, 0x74, 0x68, 0x72, 0x65, 0x65, 0x20,
            0x6c, 0x69, 0x74, 0x74, 0x6c, 0x65, 0x20, 0x70, 0x69, 0x67, 0x73, 0x2c, 0x20, 0x77, 0x68, 0x6f,
            0x20, 0x65, 0x61, 0x63, 0x68, 0x20, 0x77, 0x61, 0x6e, 0x74, 0x65, 0x64, 0x20, 0x74, 0x6f, 0x20,
            0x62, 0x75, 0x69, 0x6c, 0x64, 0x20, 0x61, 0x20, 0x68, 0x6f, 0x75, 0x73, 0x65, 0x2e, 0x20, 0x54,
            0x68, 0x65, 0x20, 0x66, 0x69, 0x72, 0x73, 0x74, 0x20, 0x6c, 0x69, 0x74, 0x74, 0x6c, 0x65, 0x20,
            0x70, 0x69, 0x67, 0x20, 0x62, 0x75, 0x69, 0x6c, 0x74, 0x20, 0x61, 0x20, 0x73, 0x74, 0x72, 0x61,
            0x77, 0x20, 0x68, 0x6f, 0x75, 0x73, 0x65, 0x2c, 0x20, 0x77, 0x69, 0x74, 0x68, 0x20, 0x73, 0x74,
            0x72, 0x61, 0x77, 0x20, 0x66, 0x72, 0x6f, 0x6d, 0x20, 0x74, 0x68, 0x65, 0x20, 0x66, 0x69, 0x65,
            0x6c, 0x64, 0x2e, 0x20, 0x54, 0x68, 0x65, 0x20, 0x73, 0x65, 0x63, 0x6f, 0x6e, 0x64, 0x20, 0x6c,
            0x69, 0x74, 0x74, 0x6c, 0x65, 0x20, 0x70, 0x69, 0x67, 0x20, 0x62, 0x75, 0x69, 0x6c, 0x74, 0x20,
            0x61, 0x20, 0x73, 0x74, 0x69, 0x63, 0x6b, 0x20, 0x68, 0x6f, 0x75, 0x73, 0x65, 0x2c, 0x20, 0x77,
            0x69, 0x74, 0x68, 0x20, 0x73, 0x74, 0x69, 0x63, 0x6b, 0x73, 0x20, 0x66, 0x72, 0x6f, 0x6d, 0x20,
            0x74, 0x68, 0x65, 0x20, 0x66, 0x6f, 0x72, 0x65, 0x73, 0x74, 0x2e, 0x20, 0x54, 0x68, 0x65, 0x20,
            0x74, 0x68, 0x69, 0x72, 0x64, 0x20, 0x6c, 0x69, 0x74, 0x74, 0x6c, 0x65, 0x20, 0x70, 0x69, 0x67,
            0x20, 0x62, 0x75, 0x69, 0x6c, 0x74, 0x20, 0x61, 0x20, 0x62, 0x72, 0x69, 0x63, 0x6b, 0x20, 0x68,
            0x6f, 0x75, 0x73, 0x65, 0x2c, 0x20, 0x77, 0x69, 0x74, 0x68, 0x20, 0x62, 0x72, 0x69, 0x63, 0x6b,
            0x73, 0x20, 0x66, 0x72, 0x6f, 0x6d, 0x20, 0x74, 0x68, 0x65, 0x20, 0x62, 0x72, 0x69, 0x63, 0x6b,
            0x20, 0x77, 0x6f, 0x72, 0x6b, 0x73, 0x2e
            }));
  }
  
}

  
void test5() throw()
{
  // encode(SnmpV2cGetRequest)
  SnmpV2cGetRequest r(
    Community("private"),
    RequestId(1),
    {Oid(".1.3.6.1.4.1.2680.1.2.7.3.2.0")});
  std::vector<uint8_t> x(encode(r));
  xju::assert_equal(
    x,
    std::vector<uint8_t>({
        0x30,0x2c,0x02,0x01,0x01,0x04,0x07,0x70,0x72,0x69,0x76,0x61,0x74,0x65,0xA0,0x1E,0x02,0x01,0x01,0x02,0x01,0x00,0x02,0x01,0x00,0x30,0x13,0x30,0x11,0x06,0x0D,0x2B,0x06,0x01,0x04,0x01,0x94,0x78,0x01,0x02,0x07,0x03,0x02,0x00,0x05,0x00
          }));
}

void test6() throw()
{
  // encode(SnmpV2cSetRequest)
  SnmpV2cSetRequest r(
    Community("private"),
    RequestId(1),
    {{Oid(".1.3.6.1.4.1.2680.1.2.7.3.2.0"),
          std::shared_ptr<Value const>(new NullValue)}});
  std::vector<uint8_t> x(encode(r));
  xju::assert_equal(
    x,
    std::vector<uint8_t>({
        0x30,0x2c,0x02,0x01,0x01,0x04,0x07,0x70,0x72,0x69,0x76,0x61,0x74,0x65,0xA3,0x1E,0x02,0x01,0x01,0x02,0x01,0x00,0x02,0x01,0x00,0x30,0x13,0x30,0x11,0x06,0x0D,0x2B,0x06,0x01,0x04,0x01,0x94,0x78,0x01,0x02,0x07,0x03,0x02,0x00,0x05,0x00
          }));
}

void test7() throw()
{
  // encode(SnmpV2cGetNexRequest)
  SnmpV2cGetNextRequest r(
    Community("private"),
    RequestId(1),
    {Oid(".1.3.6.1.4.1.2680.1.2.7.3.2.0")});
  std::vector<uint8_t> x(encode(r));
  xju::assert_equal(
    x,
    std::vector<uint8_t>({
        0x30,0x2c,0x02,0x01,0x01,0x04,0x07,0x70,0x72,0x69,0x76,0x61,0x74,0x65,0xA1,0x1E,0x02,0x01,0x01,0x02,0x01,0x00,0x02,0x01,0x00,0x30,0x13,0x30,0x11,0x06,0x0D,0x2B,0x06,0x01,0x04,0x01,0x94,0x78,0x01,0x02,0x07,0x03,0x02,0x00,0x05,0x00
          }));
}

}
}

using namespace xju::snmp;

int main(int argc, char* argv[])
{
  unsigned int n(0);
  test1(), ++n;
  test2(), ++n;
  test3(), ++n;
  test4(), ++n;
  test5(), ++n;
  test6(), ++n;
  test7(), ++n;
  std::cout << "PASS - " << n << " steps" << std::endl;
  return 0;
}

