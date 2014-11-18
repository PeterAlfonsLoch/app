#pragma once


template < class VALUE, class ARG_VALUE = const VALUE &, class HASH = ::comparison::hash < int32_t > , class EQUALS = ::comparison::equals_type_arg_type < int32_t, int32_t > >
using int_map = map < int32_t,int32_t,VALUE,ARG_VALUE,HASH,EQUALS >  ;

using int_to_int= int_map < int,int >;

using int_to_string =  int_map < string, const string & > ;


