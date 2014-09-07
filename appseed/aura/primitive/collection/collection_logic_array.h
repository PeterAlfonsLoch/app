#pragma once


class CLASS_DECL_AURA bool_array :
   virtual public ::file::serializable_array < raw_array < bool, bool > >
{
public:


   bool_array()
   {
   }


   bool_array(const bool_array & a)
   {
      operator = (a);
   }

   bool_array(bool_array && a)
   {
      operator = (a);
   }

   virtual ~bool_array()
   {
   }

   bool_array & operator = (const bool_array & a)
   {
      ::file::serializable_array < raw_array < bool, bool > >::operator = (a);
      return *this;
   }

   bool_array & operator = (bool_array && a)
   {
      ::file::serializable_array < raw_array < bool, bool > >::operator = (a);
      return *this;
   }

};
