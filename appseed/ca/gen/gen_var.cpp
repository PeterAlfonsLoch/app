#include "StdAfx.h"

namespace gen
{

   CLASS_DECL_ca new_const g_newconst;
   CLASS_DECL_ca null_const g_nullconst;
   CLASS_DECL_ca empty_const g_emptyconst;
   CLASS_DECL_ca empty_argument_const g_emptyargumentconst;

   bool ok(para_return eret)
   {
      return ((int)eret) >= 0;
   }

   var::e_type new_const::get_type() const
   {
      return type_new;
   }

   bool new_const::is_true() const
   {
      return false;
   }

   bool new_const::is_new() const
   {
      return true;
   }


   bool new_const::is_empty() const
   {
      return true;
   }
      
   bool new_const::is_null() const
   {
      return false;
   }



   var::e_type null_const::get_type() const
   {
      return type_null;
   }

   bool null_const::is_true() const
   {
      return false;
   }

   bool null_const::is_new() const
   {
      return false;
   }


   bool null_const::is_empty() const
   {
      return true;
   }
      
   bool null_const::is_null() const
   {
      return true;
   }

   var::e_type empty_const::get_type() const
   {
      return type_empty;
   }

   bool empty_const::is_true() const
   {
      return false;
   }

   bool empty_const::is_new() const
   {
      return false;
   }

   bool empty_const::is_empty() const
   {
      return true;
   }
      
   bool empty_const::is_null() const
   {
      return false;
   }


   var::e_type empty_argument_const::get_type() const
   {
      return type_empty_argument;
   }

   bool empty_argument_const::is_true() const
   {
      return false;
   }

   bool empty_argument_const::is_new() const
   {
      return false;
   }

   bool empty_argument_const::is_empty() const
   {
      return true;
   }
      
   bool empty_argument_const::is_null() const
   {
      return false;
   }

   var str_ends_get(const char * lpcsz, const char * lpcszSuffix)
   {
      
      string str(lpcsz);

      string strSuffix(lpcszSuffix);

      strsize iLen = strSuffix.get_length();

      if(str.Right(iLen) == lpcszSuffix)
      {

         return str.Left(str.get_length() - iLen);

      }

      return false;

   }

} // namespace gen