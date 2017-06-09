#pragma once


//#include "collection_string_iterable.h"


template < typename STRING >
class string_list :
   public ::list < STRING >
{
public:


   typedef STRING BASE_TYPE;
   typedef const char * BASE_ARG_TYPE;


   string_list();
   virtual ~string_list();

};



template < typename STRING >
string_list < STRING > ::string_list()
{

}


template < typename STRING >
string_list < STRING > ::~string_list()
{
   
   remove_all();
   
   ASSERT(m_nCount == 0);

}


