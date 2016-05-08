#pragma once


template < class VALUE, class ARG_VALUE = const VALUE & >
using int_map = map < int32_t,int32_t, VALUE, ARG_VALUE >;

template < class VALUE,class ARG_VALUE = const VALUE & >
using int_ptr_map = map < int_ptr,int_ptr, VALUE, ARG_VALUE >;

using int_to_int= int_map < int,int >;

using int_to_string =  int_map < string, const string & > ;

using int_ptr_to_int_ptr= int_ptr_map < int_ptr,int_ptr >;

using int_ptr_to_string =  int_ptr_map < string, const string & > ;

