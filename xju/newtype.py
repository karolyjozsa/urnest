# Copyright (c) 2022 Trevor Taylor
# coding: utf-8
# 
# Permission to use, copy, modify, and/or distribute this software for
# any purpose with or without fee is hereby granted, provided that all
# copyright notices and this permission notice appear in all copies.
# 
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
# Utilities for creating distinct types mirroring a subset of a basic
# type (str, int, float, bytes).
#
# Unlike typing.NewType:
#   - works with isinstance (at runtime)
#   - many methods of the basic type are provided directly, e.g. for
#     new int type A, A+A->A

from typing import Iterable,Sized,Container,Collection,Reversible,Protocol,cast,Type,overload,TypeVar
from typing import Generic,Tuple,Mapping,Optional,List,Literal,Union

Tag=TypeVar('Tag',covariant=True)

class Int_(Generic[Tag]):
    __value:int

    def __init__(self, value:int):
        self.__value=value
        pass

    def value(self)->int:
        return self.__value

    pass

class Int(Generic[Tag],Int_[Tag]):
    def __eq__(self,other)->bool:
        '''equality test ignores possible subclass relationships, i.e. only valid
           for two object of exactly the same class; except that python insists
           supporting __eq__ for objects of any type, so this functions supports
           comparing any Int[X] with any non-Int but if you want to use Int[X] in
           a multi-level class hierarchy you'll need write your own __eq__ to suit
           your specific circumstances'''
        '''i.e. recommend stick to using Int[X] like:
              class Hours(Int[HoursTag]):pass
           ... and not inherit from Hours.
           If you choose to inherit from Hours, make sure you write your own __eq__'''
        assert (other.__class__ is self.__class__) or not isinstance(other,Int)  # see above
        if other.__class__ is self.__class__:
            return self.value().__eq__(other.value())
        return False
    def __ne__(self,other)->bool:
        assert (other.__class__ is self.__class__) or not isinstance(other,Int)  # see __eq__ above
        if other.__class__==self.__class__:
            return self.value()!=other.value()
        return True
    def __str__(self)->str:
        return str(self.value())

    def __repr__(self)->str:
        return repr(self.value())

    def __reduce__(self)->Tuple:
        return (self.__class__, (self.value(),))

    def __format__(self, format_spec:str)->str:
        return self.value().__format__(format_spec)

    def __float__(self)->float:
        return self.value().__float__()
    
    def conjugate(self):
        return self.value().conjugate()

    @overload
    def __divmod__(self, x:int) -> Tuple:  # Tuple[Self,Self]
        ...
    @overload
    def __divmod__(self, x:float) -> Tuple[float,float]:
        ...
    @overload
    def __divmod__(self, x:Int_[Tag]) -> Tuple:  # Tuple[int,int]
        ...
    def __divmod__(self, x):
        if isinstance(x,int):
            q,r=self.value().__divmod__(x)
            return self.__class__(q),self.__class__(r)
        if isinstance(x,float):
            return divmod(self.value(),x)
        else:
            return divmod(self.value(),x.value())
        pass

    @overload
    def __floordiv__(self, x:int):  # -> Int[Tag]
        ...
    @overload
    def __floordiv__(self, x:float) -> float:
        ...
    @overload
    def __floordiv__(self, x:Int_[Tag]) -> int:
        ...
    def __floordiv__(self, x):
        if isinstance(x,int):
            return self.__class__(self.value()//x)
        elif isinstance(x,float):
            return self.value()//x
        else:
            return self.value()//x.value()
        pass

    def __truediv__(self, x:Union[float,int,Int_[Tag]]) -> float:
        if isinstance(x,float) or isinstance(x,int):
            return self.value()/x
        else:
            return self.value()/x.value()
        pass
    
    @overload
    def __mul__(self, x:int):  # -> Int[Tag]
        ...
    @overload
    def __mul__(self, x:float) -> float:
        ...
    def __mul__(self, x):
        if isinstance(x,int):
            return self.__class__(self.value()*x)
        else:
            return self.value()*x
        pass

    @overload
    def __rmul__(self, x:int):  # -> Int[Tag]
        ...
    @overload
    def __rmul__(self, x:float) -> float:
        ...
    def __rmul__(self, x):
        if isinstance(x,int):
            return self.__class__(x*self.value())
        else:
            return x*self.value()
        pass

    @overload
    def __mod__(self, other:int):  #->Int[Tag]
        ...
    @overload
    def __mod__(self, other:float)->float:
        ...
    @overload
    def __mod__(self, other:Int_[Tag])->int:
        ...
    def __mod__(self, other):
        if type(other) is int:
            return self.__class__(self.value()%other)
        if type(other) is float:
            return self.value()%other
        else:
            return self.value()%other.value()

    
    def __abs__(self):
        return self.__class__(self.value().__abs__())
    def __invert__(self):
        return self.__class__(self.value().__invert__())
    def __neg__(self):
        return self.__class__(self.value().__neg__())
    def __pos__(self):
        return self.__class__(self.value().__pos__())
    def __trunc__(self):
        return self.__class__(self.value().__trunc__())
    def __round__(self):
        return self.__class__(self.value().__round__())
    def __ceil__(self):
        return self.__class__(self.value().__ceil__())
    def __floor__(self):
        return self.__class__(self.value().__floor__())
    def __int__(self)->int:
        return self.value().__int__()
    def __sizeof__(self)->int:
        return self.value().__sizeof__()
    def bit_count(self)->int:
        return self.value().bit_count()
    def bit_length(self)->int:
        return self.value().bit_length()
    def __index__(self)->int:
        return self.value().__index__()
    def __hash__(self)->int:
        return self.value().__hash__()
    def __bool__(self)->bool:
        return self.value().__bool__()
    def __ror__(self,n:int):
        return self.__class__(self.value().__ror__(n))
    def __rrshift__(self,n:int):
        return self.__class__(self.value().__rrshift__(n))
    def __lshift__(self,n:int):
        return self.__class__(self.value().__lshift__(n))
    def __rlshift__(self,n:int):
        return self.__class__(self.value().__rlshift__(n))
    def __rshift__(self,n:int):
        return self.__class__(self.value().__rshift__(n))
    def __gt__(self,other:Int_[Tag])->bool:
        return self.value().__gt__(other.value())
    def __lt__(self,other:Int_[Tag])->bool:
        return self.value().__lt__(other.value())
    def __le__(self,other:Int_[Tag])->bool:
        return self.value().__le__(other.value())
    def __ge__(self,other:Int_[Tag])->bool:
        return self.value().__ge__(other.value())
    def __add__(self,other:Int_[Tag]):
        return self.__class__(self.value().__add__(other.value()))
    def __sub__(self,other:Int_[Tag]):
        return self.__class__(self.value().__sub__(other.value()))
    def __rsub__(self,other:Int_[Tag]):
        return self.__class__(self.value().__rsub__(other.value()))
    def __radd__(self,other:Int_[Tag]):
        return self.__class__(self.value().__radd__(other.value()))
    def __and__(self,other:Int_[Tag]):
        return self.__class__(self.value().__and__(other.value()))
    def __or__(self,other:Int_[Tag]):
        return self.__class__(self.value().__or__(other.value()))
    def __xor__(self,other:Int_[Tag]):
        return self.__class__(self.value().__xor__(other.value()))
    def as_integer_ratio(self)->Tuple[int,int]:
        return self.value().as_integer_ratio()

    pass


class Float_(Generic[Tag]):
    __value:float

    def __init__(self, value:float):
        self.__value=value
        pass

    def value(self)->float:
        return self.__value

    pass

class Float(Generic[Tag],Float_[Tag]):
    def __eq__(self,other)->bool:
        '''equality test ignores possible subclass relationships, i.e. only valid
           for two object of exactly the same class; except that python insists
           supporting __eq__ for objects of any type, so this functions supports
           comparing any Float[X] with any non-Float but if you want to use Float[X] in
           a multi-level class hierarchy you'll need write your own __eq__ to suit
           your specific circumstances'''
        '''i.e. recommend stick to using Float[X] like:
              class Timestamp(Float[TimestampTag]):pass
           ... and not inherit from Timestamp.
           If you choose to inherit from Timestamp, make sure you write your own __eq__'''
        assert (other.__class__ is self.__class__) or not isinstance(other,Float)  # see above
        if other.__class__ is self.__class__:
            return self.value().__eq__(other.value())
        return False
    def __ne__(self,other)->bool:
        assert (other.__class__ is self.__class__) or not isinstance(other,Float)  # see __eq__ above
        if other.__class__==self.__class__:
            return self.value()!=other.value()
        return True

    def __str__(self)->str:
        return str(self.value())

    def __repr__(self)->str:
        return repr(self.value())

    def __reduce__(self)->Tuple:
        return (self.__class__, (self.value(),))

    def __format__(self, format_spec:str)->str:
        return self.value().__format__(format_spec)

    def __int__(self)->int:
        return self.value().__int__()
    
    def __float__(self)->float:
        return self.value().__float__()
    
    def hex(self)->str:
        return self.value().hex()
    
    def conjugate(self):
        return self.value().conjugate()

    @overload
    def __divmod__(self, x:int) -> Tuple:  # Tuple[Self,Self]
        ...
    @overload
    def __divmod__(self, x:float) -> Tuple:  # Tuple[Self,Self]
        ...
    @overload
    def __divmod__(self, x:Float_[Tag]) -> Tuple:  # Tuple[float,float]
        ...
    def __divmod__(self, x):
        if isinstance(x,int) or isinstance(x,float):
            q,r=self.value().__divmod__(x)
            return Float[Tag](q),Float[Tag](r)
        else:
            return divmod(self.value(),x.value())
        pass

    @overload
    def __floordiv__(self, x:int):  # -> Float[Tag]
        ...
    @overload
    def __floordiv__(self, x:float):  # -> Float[Tag]
        ...
    @overload
    def __floordiv__(self, x:Float_[Tag]) -> float:
        ...
    def __floordiv__(self, x):
        if isinstance(x,int) or isinstance(x,float):
            return Float[Tag](self.value()//x)
        else:
            return self.value()//x.value()
        pass

    @overload
    def __truediv__(self, x:Union[float,int]): # -> Float[Tag]
        ...
    @overload
    def __truediv__(self, x:Float_[Tag]) -> float:
        ...
    def __truediv__(self, x):
        if isinstance(x,int) or isinstance(x,float):
            return Float[Tag](self.value()/x)
        else:
            return self.value()/x.value()
        pass
    
    @overload
    def __mul__(self, x:int):  # -> Float[Tag]
        ...
    @overload
    def __mul__(self, x:float):  # -> Float[Tag]
        ...
    def __mul__(self, x):
        return Float[Tag](self.value()*x)

    @overload
    def __rmul__(self, x:int):  # -> Float[Tag]
        ...
    @overload
    def __rmul__(self, x:float):  # -> Float[Tag]
        ...
    def __rmul__(self, x):
        return Float[Tag](x*self.value())

    @overload
    def __mod__(self, other:int):  #->Float[Tag]
        ...
    @overload
    def __mod__(self, other:float):  #->Float[Tag]
        ...
    @overload
    def __mod__(self, other:Float_[Tag])->float:
        ...
    def __mod__(self, other):
        if isinstance(other,int) or isinstance(other,float):
            return Float[Tag](self.value()%other)
        else:
            return self.value()%other.value()

    def __round__(self, ndigits:int):  #->Float[Tag]
        return Float[Tag](self.value().__round__(ndigits))

    
    def __abs__(self):
        return Float[Tag](self.value().__abs__())
    def __neg__(self):
        return Float[Tag](self.value().__neg__())
    def __pos__(self):
        return Float[Tag](self.value().__pos__())
    def __trunc__(self):
        return Float[Tag](self.value().__trunc__())
    def __ceil__(self):
        return Float[Tag](self.value().__ceil__())
    def __floor__(self):
        return Float[Tag](self.value().__floor__())
    def __sizeof__(self)->int:
        return self.value().__sizeof__()
    def __hash__(self)->int:
        return self.value().__hash__()
    def __bool__(self)->bool:
        return float(self.value()).__bool__()
    def is_integer(self)->bool:
        return float(self.value()).is_integer()
    def __gt__(self,other:Float_[Tag])->bool:
        return self.value().__gt__(other.value())
    def __lt__(self,other:Float_[Tag])->bool:
        return self.value().__lt__(other.value())
    def __le__(self,other:Float_[Tag])->bool:
        return self.value().__le__(other.value())
    def __ge__(self,other:Float_[Tag])->bool:
        return self.value().__ge__(other.value())
    def __add__(self,other:Float_[Tag]):
        return Float[Tag](self.value().__add__(other.value()))
    def __sub__(self,other:Float_[Tag]):
        return Float[Tag](self.value().__sub__(other.value()))
    def as_integer_ratio(self)->Tuple[float,float]:
        return self.value().as_integer_ratio()

    pass


class Str_(Generic[Tag]):
    __value:str
    def __init__(self, value:str):
        self.__value=value
        pass

    def value(self)->str:
        return self.__value
    pass

class Str(Generic[Tag],Str_[Tag]):
    def __eq__(self,other)->bool:
        '''equality test ignores possible subclass relationships, i.e. only valid
           for two object of exactly the same class; except that python insists
           supporting __eq__ for objects of any type, so this functions supports
           comparing any Str[X] with any non-Str but if you want to use Str[X] in
           a multi-level class hierarchy you'll need write your own __eq__ to suit
           your specific circumstances'''
        '''i.e. recommend stick to using Str[X] like:
              class FirstName(Str[FirstNameTag]):pass
           ... and not inherit from FirstName.
           If you choose to inherit from Timestamp, make sure you write your own __eq__'''
        assert (other.__class__ is self.__class__) or not isinstance(other,Str)  # see above
        if other.__class__ is self.__class__:
            return self.value().__eq__(other.value())
        return False
    def __ne__(self,other)->bool:
        assert (other.__class__ is self.__class__) or not isinstance(other,Str)  # see __eq__ above
        if other.__class__==self.__class__:
            return self.value()!=other.value()
        return True

    def __str__(self)->str:
        return str(self.value())

    def __repr__(self)->str:
        return repr(self.value())

    def __reduce__(self)->Tuple:
        return (self.__class__, (self.value(),))

    def __format__(self, format_spec:str)->str:
        return self.value().__format__(format_spec)

    def splitlines(self,keepends=False)->List:
        return [self.__class__(_) for _ in self.value().splitlines()]

    def encode(self,encoding:str='utf-8', errors:str='strict')->bytes:
        return self.value().encode()

    def __contains__(self,other:str)->bool:
        return self.value().__contains__(other)

    def zfill(self,width:int):
        return self.__class__(self.value().zfill(width))

    def format_map(self,mapping:Mapping):
        return self.__class__(self.value().format_map(mapping))

    def format(self,*args,**kwargs):
        return self.__class__(self.value().format(*args,**kwargs))
    
    def expandtabs(self,tabsize=8):
        return self.__class__(self.value().expandtabs(tabsize))

    def __getitem__(self,key):
        return self.value().__getitem__(key)

    
    def capitalize(self):
        return self.__class__(self.value().capitalize())
    def lower(self):
        return self.__class__(self.value().lower())
    def swapcase(self):
        return self.__class__(self.value().swapcase())
    def title(self):
        return self.__class__(self.value().title())
    def casefold(self):
        return self.__class__(self.value().casefold())
    def upper(self):
        return self.__class__(self.value().upper())
    def __len__(self)->int:
        return self.value().__len__()
    def __sizeof__(self)->int:
        return self.value().__sizeof__()
    def __hash__(self)->int:
        return self.value().__hash__()
    def isalnum(self)->bool:
        return self.value().isalnum()
    def isdecimal(self)->bool:
        return self.value().isdecimal()
    def isidentifier(self)->bool:
        return self.value().isidentifier()
    def isprintable(self)->bool:
        return self.value().isprintable()
    def isascii(self)->bool:
        return self.value().isascii()
    def islower(self)->bool:
        return self.value().islower()
    def isnumeric(self)->bool:
        return self.value().isnumeric()
    def isspace(self)->bool:
        return self.value().isspace()
    def isupper(self)->bool:
        return self.value().isupper()
    def isalpha(self)->bool:
        return self.value().isalpha()
    def isdigit(self)->bool:
        return self.value().isdigit()
    def istitle(self)->bool:
        return self.value().istitle()
    def __mul__(self,n:int):
        return self.__class__(self.value().__mul__(n))
    def __gt__(self,other:Str_[Tag])->bool:
        return self.value().__gt__(other.value())
    def __lt__(self,other:Str_[Tag])->bool:
        return self.value().__lt__(other.value())
    def __le__(self,other:Str_[Tag])->bool:
        return self.value().__le__(other.value())
    def __ge__(self,other:Str_[Tag])->bool:
        return self.value().__ge__(other.value())
    def __add__(self,other:Str_[Tag]):
        return self.__class__(self.value().__add__(other.value()))
    @overload
    def rfind(self, sub:str) -> int:
        ...
    @overload
    def rfind(self, sub:str, start:int)->int:
        ...
    @overload
    def rfind(self, sub:str, start:int, end:int)->int:
        ...
    def rfind(self, sub, *args):
        return self.value().rfind(sub,*args)
    @overload
    def find(self, sub:str) -> int:
        ...
    @overload
    def find(self, sub:str, start:int)->int:
        ...
    @overload
    def find(self, sub:str, start:int, end:int)->int:
        ...
    def find(self, sub, *args):
        return self.value().find(sub,*args)
    @overload
    def rindex(self, sub:str) -> int:
        ...
    @overload
    def rindex(self, sub:str, start:int)->int:
        ...
    @overload
    def rindex(self, sub:str, start:int, end:int)->int:
        ...
    def rindex(self, sub, *args):
        return self.value().rindex(sub,*args)
    @overload
    def index(self, sub:str) -> int:
        ...
    @overload
    def index(self, sub:str, start:int)->int:
        ...
    @overload
    def index(self, sub:str, start:int, end:int)->int:
        ...
    def index(self, sub, *args):
        return self.value().index(sub,*args)
    @overload
    def count(self, sub:str) -> int:
        ...
    @overload
    def count(self, sub:str, start:int)->int:
        ...
    @overload
    def count(self, sub:str, start:int, end:int)->int:
        ...
    def count(self, sub, *args):
        return self.value().count(sub,*args)
    @overload
    def translate(self, sub:str) -> int:
        ...
    @overload
    def translate(self, sub:str, start:int)->int:
        ...
    @overload
    def translate(self, sub:str, start:int, end:int)->int:
        ...
    def translate(self, sub, *args):
        return self.value().translate(sub,*args)
    @overload
    def endswith(self, s:str) -> bool:
        ...
    @overload
    def endswith(self, s:str, start:int)->bool:
        ...
    @overload
    def endswith(self, s:str, start:int, end:int)->bool:
        ...
    def endswith(self, s, *args):
        return self.value().endswith(s,*args)
    @overload
    def startswith(self, s:str) -> bool:
        ...
    @overload
    def startswith(self, s:str, start:int)->bool:
        ...
    @overload
    def startswith(self, s:str, start:int, end:int)->bool:
        ...
    def startswith(self, s, *args):
        return self.value().startswith(s,*args)
    def strip(self, chars:Optional[str]=None):
        return self.__class__(self.value().strip(chars))
    def lstrip(self, chars:Optional[str]=None):
        return self.__class__(self.value().lstrip(chars))
    def rstrip(self, chars:Optional[str]=None):
        return self.__class__(self.value().rstrip(chars))
    def replace(self, old:str, new:str, count=-1):
        return self.__class__(self.value().replace(old,new,count))
    def split(self, sep:Optional[str]=None, max_split=-1)->List[str]:
        return self.value().split(sep,max_split)
    def rsplit(self, sep:Optional[str]=None, max_split=-1)->List[str]:
        return self.value().rsplit(sep,max_split)
    def partition(self,sep:str) -> Tuple[str,str,str]:
        return self.value().partition(sep)
    def rpartition(self,sep:str) -> Tuple[str,str,str]:
        return self.value().rpartition(sep)
    def removeprefix(self,sub:str):
        return self.__class__(self.value().removeprefix(sub))
    def removesuffix(self,sub:str):
        return self.__class__(self.value().removesuffix(sub))
    def center(self,width:int,fillchar:str=' '):
        return self.__class__(self.value().center(width,fillchar))
    def ljust(self,width:int,fillchar:str=' '):
        return self.__class__(self.value().ljust(width,fillchar))
    def rjust(self,width:int,fillchar:str=' '):
        return self.__class__(self.value().rjust(width,fillchar))

    pass
