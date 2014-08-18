#pragma once


template < class VALUE, class ARG_VALUE = const VALUE &, class HASH = ::comparison::hash < int32_t > , class EQUALS = ::comparison::equals_type_arg_type < int32_t, int32_t > >
class int_map :
   virtual public attrib_map < map < int32_t, int32_t, VALUE, ARG_VALUE, HASH, EQUALS > >
{
public:

   int_map(sp(::base::application) papp = NULL, ::count nBlockSize = 10);
   int_map(const int_map & map);


   int_map & operator = (const int_map & map);

};

template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
int_map < VALUE, ARG_VALUE, HASH, EQUALS >::int_map(sp(::base::application) papp, ::count nBlockSize) :
   element(papp),
   map < int32_t, int32_t, VALUE, ARG_VALUE, HASH, EQUALS > (papp, nBlockSize)
{
}

template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
int_map < VALUE, ARG_VALUE, HASH, EQUALS >::int_map(const int_map & intmap) :
   element(intmap.get_app()),
   attrib_map < map < int32_t, int32_t, VALUE, ARG_VALUE, HASH, EQUALS > >(intmap)
{
}

template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
int_map < VALUE, ARG_VALUE, HASH, EQUALS > & int_map < VALUE, ARG_VALUE, HASH, EQUALS >::operator = (const int_map & intmap)
{

   if(this != &intmap)
   {
      this->attrib_map < ::map < int32_t, int32_t, VALUE, ARG_VALUE, HASH, EQUALS > >::operator = (intmap);
   }

   return *this;

}



typedef CLASS_DECL_AXIS int_map < int, int > int_to_int;

typedef CLASS_DECL_AXIS int_map < string, const string & > int_to_string;


