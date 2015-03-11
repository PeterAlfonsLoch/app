#pragma once


template < class VALUE, class ARG_VALUE = const VALUE &, class HASH = ::comparison::hash < const string & > , class EQUALS = ::comparison::equals_type_arg_type < string, const string & > >
using string_map =map < string,const string &,VALUE,ARG_VALUE,HASH,EQUALS > ;

using string_to_intptr = string_map < int_ptr,int_ptr > ;

using string_to_int =  string_map < int, int > ;

using string_to_ptr =  string_map < void *,void * > ;


#define strmap(T) string_map < T >


