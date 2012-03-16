#pragma once

#include "primitive/var.h"



class var_array;

namespace gen
{
   class property;
   class property;
   class property_set;
   class pair_set_interface;
   class str_str_interface;

   class CLASS_DECL_ca new_const :
      virtual public var
   {
   public:
      virtual e_type get_type() const;
      virtual bool is_true() const;

      virtual bool is_new() const;
      virtual bool is_null() const;
      virtual bool is_empty() const;
   };


   class CLASS_DECL_ca null_const :
      virtual public var
   {
   public:
      virtual e_type get_type() const;
      virtual bool is_true() const;

      virtual bool is_new() const;
      virtual bool is_null() const;
      virtual bool is_empty() const;
   };

   class CLASS_DECL_ca empty_const :
      virtual public var
   {
   public:
      virtual e_type get_type() const;
      virtual bool is_true() const;
      
      virtual bool is_new() const;
      virtual bool is_null() const;
      virtual bool is_empty() const;
   };

   class CLASS_DECL_ca empty_argument_const :
      virtual public var
   {
   public:
      virtual e_type get_type() const;
      virtual bool is_true() const;
      
      virtual bool is_new() const;
      virtual bool is_null() const;
      virtual bool is_empty() const;
   };


   extern CLASS_DECL_ca new_const g_newconst;
   extern CLASS_DECL_ca null_const g_nullconst;
   extern CLASS_DECL_ca empty_const g_emptyconst;
   extern CLASS_DECL_ca empty_argument_const g_emptyargumentconst;

   var CLASS_DECL_ca str_ends_get(const char * lpcsz, const char * lpcszSuffix);

   namespace str
   {
      CLASS_DECL_ca var ends_get(const char * pszSuffix, const char * psz);
      CLASS_DECL_ca var ends_get_ci(const char * pszSuffix, const char * psz);
   } // namespace str


} // namespace gen


