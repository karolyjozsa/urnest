// This file is generated by omniidl (C++ backend)- omniORB_4_2. Do not edit.

#include "p11.hh"
#include <omniORB4/IOP_S.h>
#include <omniORB4/IOP_C.h>
#include <omniORB4/callDescriptor.h>
#include <omniORB4/callHandle.h>
#include <omniORB4/objTracker.h>


OMNI_USING_NAMESPACE(omni)

static const char* _0RL_library_version = omniORB_4_2;



const char * p11_Z = "z";

_init_in_def_( const ::CORBA::Short p11_Q = 10; )

void
U1::operator>>= (cdrStream& _n) const
{
  _pd__d >>= _n;


  switch(_pd__d) {
    case A:
      _pd_a_ >>= _n;
      break;
    case C:
      _pd_c_ >>= _n;
      break;

  }
}

void
U1::operator<<= (cdrStream& _n)
{
  _release_member();
  
  (X&)_pd__d <<= _n;

  switch(_pd__d) {
    case A:
      _pd__default = 0;
      (::CORBA::Long&)_pd_a_ <<= _n;
      break;
    case C:
      _pd__default = 0;
      (::CORBA::Float&)_pd_c_ <<= _n;
      break;
    default:
      _pd__default = 1;
      break;

  }
  _pd__initialised = 1;
}

p11::F_ptr p11::F_Helper::_nil() {
  return ::p11::F::_nil();
}

::CORBA::Boolean p11::F_Helper::is_nil(::p11::F_ptr p) {
  return ::CORBA::is_nil(p);

}

void p11::F_Helper::release(::p11::F_ptr p) {
  ::CORBA::release(p);
}

void p11::F_Helper::marshalObjRef(::p11::F_ptr obj, cdrStream& s) {
  ::p11::F::_marshalObjRef(obj, s);
}

p11::F_ptr p11::F_Helper::unmarshalObjRef(cdrStream& s) {
  return ::p11::F::_unmarshalObjRef(s);
}

void p11::F_Helper::duplicate(::p11::F_ptr obj) {
  if (obj && !obj->_NP_is_nil())  omni::duplicateObjRef(obj);
}

p11::F_ptr
p11::F::_duplicate(::p11::F_ptr obj)
{
  if (obj && !obj->_NP_is_nil())  omni::duplicateObjRef(obj);
  return obj;
}

p11::F_ptr
p11::F::_narrow(::CORBA::Object_ptr obj)
{
  if (!obj || obj->_NP_is_nil() || obj->_NP_is_pseudo()) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_realNarrow(_PD_repoId);
  return e ? e : _nil();
}


p11::F_ptr
p11::F::_unchecked_narrow(::CORBA::Object_ptr obj)
{
  if (!obj || obj->_NP_is_nil() || obj->_NP_is_pseudo()) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_uncheckedNarrow(_PD_repoId);
  return e ? e : _nil();
}

p11::F_ptr
p11::F::_nil()
{
#ifdef OMNI_UNLOADABLE_STUBS
  static _objref_F _the_nil_obj;
  return &_the_nil_obj;
#else
  static _objref_F* _the_nil_ptr = 0;
  if (!_the_nil_ptr) {
    omni::nilRefLock().lock();
    if (!_the_nil_ptr) {
      _the_nil_ptr = new _objref_F;
      registerNilCorbaObject(_the_nil_ptr);
    }
    omni::nilRefLock().unlock();
  }
  return _the_nil_ptr;
#endif
}

const char* p11::F::_PD_repoId = "IDL:p11/F:1.0";


p11::_objref_F::~_objref_F() {
  
}


p11::_objref_F::_objref_F(omniIOR* ior, omniIdentity* id) :
   omniObjRef(::p11::F::_PD_repoId, ior, id, 1)
   
   
{
  _PR_setobj(this);
}

void*
p11::_objref_F::_ptrToObjRef(const char* id)
{
  if (id == ::p11::F::_PD_repoId)
    return (::p11::F_ptr) this;
  
  if (id == ::CORBA::Object::_PD_repoId)
    return (::CORBA::Object_ptr) this;

  if (omni::strMatch(id, ::p11::F::_PD_repoId))
    return (::p11::F_ptr) this;
  
  if (omni::strMatch(id, ::CORBA::Object::_PD_repoId))
    return (::CORBA::Object_ptr) this;

  return 0;
}


//
// Code for p11::F::f1

// Proxy call descriptor class. Mangled signature:
//  void_i_cU1
class _0RL_cd_c6f736139037bfb6_00000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_c6f736139037bfb6_00000000(LocalCallFn lcfn, const char* op_, size_t oplen, _CORBA_Boolean upcall=0)
    : omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

    
  
  static const char* const _user_exns[];

  U1 arg_0_;
  const U1* arg_0;
};

void _0RL_cd_c6f736139037bfb6_00000000::marshalArguments(cdrStream& _n)
{
  (const U1&) *arg_0 >>= _n;

}

void _0RL_cd_c6f736139037bfb6_00000000::unmarshalArguments(cdrStream& _n)
{
  (U1&)arg_0_ <<= _n;
  arg_0 = &arg_0_;

}

const char* const _0RL_cd_c6f736139037bfb6_00000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_c6f736139037bfb6_10000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_c6f736139037bfb6_00000000* tcd = (_0RL_cd_c6f736139037bfb6_00000000*)cd;
  p11::_impl_F* impl = (p11::_impl_F*) svnt->_ptrToInterface(p11::F::_PD_repoId);
  impl->f1(*tcd->arg_0);


}

void p11::_objref_F::f1(const ::U1& a)
{
  _0RL_cd_c6f736139037bfb6_00000000 _call_desc(_0RL_lcfn_c6f736139037bfb6_10000000, "f1", 3);
  _call_desc.arg_0 = &(::U1&) a;

  _invoke(_call_desc);



}

p11::_pof_F::~_pof_F() {}


omniObjRef*
p11::_pof_F::newObjRef(omniIOR* ior, omniIdentity* id)
{
  return new ::p11::_objref_F(ior, id);
}


::CORBA::Boolean
p11::_pof_F::is_a(const char* id) const
{
  if (omni::ptrStrMatch(id, ::p11::F::_PD_repoId))
    return 1;
  
  return 0;
}

const p11::_pof_F _the_pof_p11_mF;

p11::_impl_F::~_impl_F() {}


::CORBA::Boolean
p11::_impl_F::_dispatch(omniCallHandle& _handle)
{
  const char* op = _handle.operation_name();

  if (omni::strMatch(op, "f1")) {

    _0RL_cd_c6f736139037bfb6_00000000 _call_desc(_0RL_lcfn_c6f736139037bfb6_10000000, "f1", 3, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }


  return 0;
}

void*
p11::_impl_F::_ptrToInterface(const char* id)
{
  if (id == ::p11::F::_PD_repoId)
    return (::p11::_impl_F*) this;
  
  if (id == ::CORBA::Object::_PD_repoId)
    return (void*) 1;

  if (omni::strMatch(id, ::p11::F::_PD_repoId))
    return (::p11::_impl_F*) this;
  
  if (omni::strMatch(id, ::CORBA::Object::_PD_repoId))
    return (void*) 1;
  return 0;
}

const char*
p11::_impl_F::_mostDerivedRepoId()
{
  return ::p11::F::_PD_repoId;
}

POA_p11::F::~F() {}

