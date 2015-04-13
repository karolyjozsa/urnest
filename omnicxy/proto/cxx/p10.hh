// This file is generated by omniidl (C++ backend)- omniORB_4_2. Do not edit.
#ifndef __p10_hh__
#define __p10_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_p10
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_p10
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_p10
#endif






#ifdef USE_stub_in_nt_dll
# ifndef USE_core_stub_in_nt_dll
#  define USE_core_stub_in_nt_dll
# endif
# ifndef USE_dyn_stub_in_nt_dll
#  define USE_dyn_stub_in_nt_dll
# endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif



_CORBA_MODULE p10

_CORBA_MODULE_BEG

  enum EN { AA, BB, CC /*, __max_EN=0xffffffff */ };
  typedef EN& EN_out;

#ifndef __p10_mF__
#define __p10_mF__
  class F;
  class _objref_F;
  class _impl_F;
  
  typedef _objref_F* F_ptr;
  typedef F_ptr FRef;

  class F_Helper {
  public:
    typedef F_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_F, F_Helper> F_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_F,F_Helper > F_out;

#endif

  // interface F
  class F {
  public:
    // Declarations for this interface type.
    typedef F_ptr _ptr_type;
    typedef F_var _var_type;

    static _ptr_type _duplicate(_ptr_type);
    static _ptr_type _narrow(::CORBA::Object_ptr);
    static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
    
    static _ptr_type _nil();

    static inline void _marshalObjRef(_ptr_type, cdrStream&);

    static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
      omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static inline _ptr_type _fromObjRef(omniObjRef* o) {
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static _core_attr const char* _PD_repoId;

    // Other IDL defined within this scope.
    
  };

  class _objref_F :
    public virtual ::CORBA::Object,
    public virtual omniObjRef
  {
  public:
    // IDL operations
    void f1(::p10::EN a);

    // Constructors
    inline _objref_F()  { _PR_setobj(0); }  // nil
    _objref_F(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_F();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_F(const _objref_F&);
    _objref_F& operator = (const _objref_F&);
    // not implemented

    friend class F;
  };

  class _pof_F : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_F() : _OMNI_NS(proxyObjectFactory)(F::_PD_repoId) {}
    virtual ~_pof_F();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_F :
    public virtual omniServant
  {
  public:
    virtual ~_impl_F();

    virtual void f1(::p10::EN a) = 0;
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
    
  };


_CORBA_MODULE_END



_CORBA_MODULE POA_p10
_CORBA_MODULE_BEG

  class F :
    public virtual p10::_impl_F,
    public virtual ::PortableServer::ServantBase
  {
  public:
    virtual ~F();

    inline ::p10::F_ptr _this() {
      return (::p10::F_ptr) _do_this(::p10::F::_PD_repoId);
    }
  };

_CORBA_MODULE_END



_CORBA_MODULE OBV_p10
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr

inline void operator >>=(p10::EN _e, cdrStream& s) {
  ::operator>>=((::CORBA::ULong)_e, s);
}

inline void operator <<= (p10::EN& _e, cdrStream& s) {
  ::CORBA::ULong _0RL_e;
  ::operator<<=(_0RL_e,s);
  if (_0RL_e <= p10::CC) {
    _e = (p10::EN) _0RL_e;
  }
  else {
    OMNIORB_THROW(MARSHAL,_OMNI_NS(MARSHAL_InvalidEnumValue),
                  (::CORBA::CompletionStatus)s.completion());
  }
}



inline void
p10::F::_marshalObjRef(::p10::F_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}



#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_p10
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_p10
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_p10
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_p10
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_p10
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_p10
#endif

#endif  // __p10_hh__
