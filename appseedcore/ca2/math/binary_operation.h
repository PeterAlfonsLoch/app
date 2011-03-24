#pragma once


namespace math
{

class binary_operation : 
   virtual public value
{
public:
   binary_operation();
   virtual ~binary_operation();

   enum e_type
   {
      type_addition,
      type_subtraction,
      type_multiplication,
      type_division,
   };

   virtual void set_value_string(const char * psz);
   virtual string get_value_string(e_get_value egetvalue);


   value * m_pvalue1;
   value * m_pvalue2;


   e_type m_etype;
};


} // namespace math