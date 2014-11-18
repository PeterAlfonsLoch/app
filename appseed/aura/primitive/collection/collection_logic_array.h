#pragma once

using bool_array_base = raw_array < bool,bool  > ;

class CLASS_DECL_AURA bool_array :
   virtual public bool_array_base
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
      bool_array_base::operator = (a);
      return *this;
   }

   bool_array & operator = (bool_array && a)
   {
      bool_array_base::operator = (a);
      return *this;
   }

};
