#pragma once


template < class VALUE, class ARG_VALUE = const VALUE &, class HASH = ::ca2::hash < const string & > , class EQUALS = ::ca2::equals_type_arg_type < string, const string & > >
class string_map :
   virtual public attrib_map < map < string, const string &, VALUE, ARG_VALUE, HASH, EQUALS > >
{
public:


   string_map(::ca2::application * papp = NULL, ::count nBlockSize = 10);
   string_map(const string_map & map);


   string_map & operator = (const string_map & map);


};

template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
string_map < VALUE, ARG_VALUE, HASH, EQUALS >::string_map(::ca2::application * papp, ::count nBlockSize) :
   ::ca2::ca2(papp),
   map < string, const string &, VALUE, ARG_VALUE, HASH, EQUALS > (papp, nBlockSize)
{
}

template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
string_map < VALUE, ARG_VALUE, HASH, EQUALS >::string_map(const string_map & map) :
   ::ca2::ca2(map.get_app()),
   attrib_map < ::map < string, const string &, VALUE, ARG_VALUE, HASH, EQUALS > > (map)
{
}

template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
string_map < VALUE, ARG_VALUE, HASH, EQUALS > & string_map < VALUE, ARG_VALUE, HASH, EQUALS >::operator = (const string_map & map)
{

   if(this != &map)
   {
      attrib_map < ::map < string, const string &, VALUE, ARG_VALUE, HASH, EQUALS > >::operator = (map);
   }

   return *this;

}


typedef CLASS_DECL_ca2 string_map < int_ptr, int_ptr > string_to_intptr;

typedef CLASS_DECL_ca2 string_map < void *, void * > string_to_ptr;


#define strmap(T) string_map < T >







