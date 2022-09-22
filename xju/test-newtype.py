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

from xju.newtype import Str,Int,Float
from xju.assert_ import Assert

from typing import Dict

class FirstNameType:pass
class LastNameType:pass

class FirstName(Str[FirstNameType]):pass
class LastName(Str[LastNameType]):pass

def full_name(first_name:FirstName,last_name:LastName)->str:
    return f'{first_name} {last_name}'

def f(x:FirstName)->FirstName:
    return x

first_name=FirstName('fred')
last_name=LastName('jones')

Assert(full_name(first_name,last_name))=='fred jones'
Assert(first_name.startswith('fr'))==True
Assert(first_name).isInstanceOf(FirstName)
Assert(first_name).isNotInstanceOf(LastName)

another_first_name=FirstName('louise')

Assert(first_name)<another_first_name
z:Dict[FirstName,int]={ first_name: 1, another_first_name:2}
Assert(z[first_name])==1

a=FirstName('robertalertaberta')

b=a.rjust(0)
Assert(b).isInstanceOf(FirstName)
Assert(f(b))==b
Assert(b)==a

Assert(repr(first_name))==repr('fred')
Assert(f'{first_name:6}')=='fred  '
Assert(first_name.splitlines())==[FirstName('fred')]
Assert(first_name.encode('utf-8'))=='fred'.encode('utf-8')
Assert('re').isIn(first_name)
Assert(FirstName('7').zfill(3))==FirstName('007')
Assert(FirstName('{l}').format_map({'l':'fred'}))==FirstName('fred')
Assert(first_name.rjust(6,'_'))==FirstName('__fred')
Assert(FirstName('{l}').format(l='fred'))==FirstName('fred')
Assert(FirstName('J\tQ').expandtabs())==FirstName('J       Q')
Assert(first_name[1:3])=='re'
Assert(first_name.capitalize())==FirstName('Fred')
Assert(FirstName('FreD').lower())==FirstName('fred')
Assert(FirstName('FreD').center(8,fillchar='='))==FirstName('==FreD==')
Assert(FirstName('FreD').swapcase())==FirstName('fREd')
Assert(first_name.title())==FirstName('Fred')
Assert(FirstName('FreD').casefold())==FirstName('FreD'.casefold())
Assert(FirstName('FreD').upper())==FirstName('FRED')
Assert(FirstName('FreD').ljust(6,'9'))==FirstName('FreD'.ljust(6,'9'))
Assert(len(first_name))==4
Assert(first_name.__sizeof__())>=4
Assert(first_name.isalnum())==True
Assert(first_name.isdecimal())==False
Assert(first_name.isidentifier())==True
Assert(first_name.isprintable())==True
Assert(first_name.isascii())==True
Assert(first_name.islower())==True
Assert(first_name.isnumeric())==False
Assert(first_name.isspace())==False
Assert(first_name.isupper())==False
Assert(first_name.isalnum())==True
Assert(first_name.isdigit())==False
Assert(first_name.istitle())==False
Assert(first_name*2)==FirstName('fredfred')
Assert(first_name)==first_name
Assert(first_name)!=another_first_name
Assert(first_name)<another_first_name
Assert(first_name)<=another_first_name
Assert(first_name)<=first_name
Assert(another_first_name)>first_name
Assert(another_first_name)>=first_name
Assert(first_name)>=first_name
Assert(first_name+another_first_name)==FirstName('fredlouise')
Assert(first_name.rfind('re'))==1
Assert(first_name.find('re'))==1
Assert(first_name.rindex('re'))==1
Assert(first_name.index('re'))==1
Assert(a.count('be'))==2
Assert(a.count('ert',4))==2
Assert(a.count('e',4,10))==1
Assert(first_name.translate('abc'))=='fred'.translate('abc')
Assert(a.endswith('rta'))==True
Assert(a.endswith('rta',14))==True
Assert(a.endswith('rta',15))==False
Assert(a.endswith('rta',3,7))==True
Assert(a.endswith('rta',5,7))==False
Assert(a.startswith('ro'))==True
Assert(a.startswith('ro',1))==False
Assert(a.startswith('ob',1,3))==True
Assert(a.startswith('ob',1,4))==True
Assert(FirstName(' fred ').strip())==first_name
Assert(FirstName(' fred ').lstrip())==FirstName('fred ')
Assert(FirstName(' fred ').rstrip())==FirstName(' fred')
Assert(FirstName('freddy').replace('dy',''))==FirstName('fred')
Assert(FirstName('freddy').replace('d','b',count=1))==FirstName('frebdy')
Assert(FirstName('J fred').split())==['J','fred']
Assert(FirstName('J P fred').rsplit(sep=None,max_split=1))==['J P','fred']
Assert(FirstName('J P fred').rsplit(sep=' P ',max_split=1))==['J','fred']
Assert(FirstName('J P fred').partition(sep=' P '))==('J',' P ','fred')
Assert(FirstName('J P fred').rpartition(sep=' P '))==('J',' P ','fred')
Assert(FirstName('J P fred').removeprefix('J '))==FirstName('P fred')
Assert(FirstName('J P fred').removesuffix('ed'))==FirstName('J P fr')



# Int[X]

class HoursTag: pass
class MinutesTag: pass

class Hours(Int[HoursTag]):pass
class Minutes(Int[MinutesTag]):pass

h1=Hours(7)
h2=Hours(8)
Assert(h1)<=h2
Assert(h1)!=h2
Assert(h2)>h1
Assert(h2)>=h1
Assert(h2)>=h2
Assert(h2)<=h2

Assert(str(h1))=='7'
Assert(repr(h1))=='7'
Assert('{:02d}'.format(h1))=='07'
Assert(h1.__float__())==7.0
Assert(abs(Hours(-5)))==Hours(5)
Assert(~h1)==Hours(~h1.value())
Assert(h1.conjugate())==h1.value().conjugate()
Assert(divmod(h1,Hours(2)))==(3,1)
Assert(divmod(h1,2))==(Hours(3),Hours(1))
Assert(divmod(h1,1.5))==(4.0,1.0)
# floordiv
Assert(h1//3)==Hours(2)
Assert(h1//Hours(3))==2
Assert(h1//2.5)==7//2.5
# truediv
Assert(h1/3)==7/3
Assert(h1/Hours(3))==7/3
Assert(h1/2.5)==7/2.5
# mull
Assert(h1*2)==Hours(14)
Assert(h2*2.5)==20.0
# mod
Assert(h1%0.5)==h1.value()%0.5
Assert(h1%h2)==h1.value()%h2.value()
Assert(h1%2)==Hours(h1.value()%2)

Assert(int(h1))==7
Assert(h1.__sizeof__())==h1.value().__sizeof__()
Assert(h1.bit_count())==h1.value().bit_count()
Assert(h1.bit_length())==h1.value().bit_length()
Assert(h1.__index__())==h1.value().__index__()
Assert(h1.__hash__())==h1.value().__hash__()
Assert(h1.__bool__())==h1.value().__bool__()
Assert(h1.__ror__(3))==Hours(h1.value().__ror__(3))
Assert(h1.__rrshift__(3))==Hours(h1.value().__rrshift__(3))
Assert(h1.__lshift__(3))==Hours(h1.value().__lshift__(3))
Assert(h1.__lshift__(3))==Hours(h1.value().__lshift__(3))
Assert(h1.__rlshift__(3))==Hours(h1.value().__rlshift__(3))
Assert(h1.__rshift__(3))==Hours(h1.value().__rshift__(3))
Assert(h1+h2)==Hours(15)
Assert(h1-h2)==Hours(-1)
Assert(h1.__rsub__(h2))==Hours(1)
Assert(h1&h2)==Hours(7&8)
Assert(h1|h2)==Hours(7|8)
Assert(h1.__xor__(h2))==Hours(7^8)
Assert(h1.as_integer_ratio())==h1.value().as_integer_ratio()


class LengthType:pass
class WeightType:pass

Length=Float[LengthType]
Weight=Float[WeightType]


# Float
l1=Length(7.5)
l2=Length(10)
Assert(l1.value())==7.5
Assert(l1)==l1
Assert(l1)!=l2
Assert(l1)<=l2
Assert(l1)<l2
Assert(l2)<=l2
Assert(l2)>l1
Assert(l2)>=l1
Assert(str(l1))==str(7.5)
Assert(repr(l1))==repr(7.5)
Assert(f'{l1:0.2f}')=='7.50'
Assert(int(l1))==7
Assert(float(l1))==7.5
Assert(l1.hex())==float(7.5).hex()
Assert(l1.conjugate())==float(7.5).conjugate()
Assert(divmod(l1,2))==tuple(Length(x) for x in divmod(7.5,2))
Assert(divmod(l1,1.5))==tuple(Length(x) for x in divmod(7.5,1.5))
Assert(divmod(l1,l2))==divmod(7.5,10.0)
#floordiv
Assert(l1//2)==Length(7.5//2)
Assert(l1//2.6)==Length(7.5//2.6)
Assert(l1//l2)==7.5//10.0
#truediv
Assert(l1/2)==Length(7.5/2)
Assert(l1/2.6)==Length(7.5/2.6)
Assert(l1/l2)==7.5/10.0
#mul
Assert(l1*2)==Length(7.5*2)
Assert(l1*2.6)==Length(7.5*2.6)
#mod
Assert(l1%2)==Length(7.5%2)
Assert(l1%2.6)==Length(7.5%2.6)
Assert(l1%l2)==7.5%10.0

Assert(abs(Length(-7.5)))==l1
Assert(-l1)==Length(-7.5)
Assert(+l1)==l1
Assert(l1.__trunc__())==Length(7)
Assert(l1.__round__(0))==Length(8)
Assert(Length(7.235).__round__(2))==Length(7.24)
Assert(l1.__ceil__())==Length(8)
Assert(l1.__floor__())==Length(7)
Assert(l1.__sizeof__())==l1.value().__sizeof__()
Assert(l1.__hash__())==l1.value().__hash__()
Assert(l1.__bool__())==l1.value().__bool__()
Assert(l1.is_integer())==False
Assert(l2.is_integer())==True
Assert(l1+l2)==Length(17.5)
Assert(l1-l2)==Length(-2.5)
