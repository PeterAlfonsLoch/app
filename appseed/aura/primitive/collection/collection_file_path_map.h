#pragma once


template < class VALUE,class ARG_VALUE = const VALUE &,class HASH = ::comparison::hash < const string & >,class EQUALS = ::comparison::equals_type_arg_type < string,const string & > >
using file_path_map =map < ::file::path,const ::file::path &,VALUE,ARG_VALUE,HASH,EQUALS > ;

using file_path_to_intptr = string_map < int_ptr,int_ptr > ;

using file_path_to_int =  string_map < int,int > ;

using file_path_to_ptr =  string_map < void *,void * > ;

#define filepathmap(T) string_map < T >


