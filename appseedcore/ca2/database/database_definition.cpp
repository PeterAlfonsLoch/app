#include "StdAfx.h"

namespace database
{

   //************* DbErrors implementation ***************

   DbErrors::DbErrors() {

     fprintf(stderr, "\nUnknown CDatabase Error\n");
   }


   DbErrors::DbErrors(const char *msg, ...) {
     va_list vl;
     va_start(vl, msg);
     //cout << "In db\n\n";
     char buf[DB_BUFF_MAX]="";
   //  vsnprintf(buf, DB_BUFF_MAX-1, msg, vl);
     va_end(vl);

     fprintf(stderr, "\nDatabase Error: %s\n", buf);
   }

   parameter_list & parameter_list::operator = (const parameter_list & paramlist)
   {
      m_stra = paramlist.m_stra;
      m_fieldvaluea = paramlist.m_fieldvaluea;
      return *this;
   }

   field_properties::field_properties()
   {
   }

   field_properties::field_properties(const field_properties & field_properties)
   {
      operator = (field_properties);
   }

   field_properties & field_properties::operator = (const field_properties & field_properties)
   {
      if(this != &field_properties)
      {
         name           = field_properties.name;
         display_name   = field_properties.display_name;
         type           = field_properties.type;
         field_table    = field_properties.field_table;
         read_only      = field_properties.read_only;
         field_len      = field_properties.field_len;
         field_flags    = field_properties.field_flags;
         idx;
      }
      return *this;
   }

   field::field()
   {
   }

   field::field(const field & field)
   {
      operator = (field);
   }

   field & field::operator = (const field & field)
   {
      if(this != &field)
      {
         m_properties   = field.m_properties;
         m_value        = field.m_value;
      }
      return *this;
   }

   bool parameter_list::is_empty()
   {
      return get_size() <= 0;
   }

   int parameter_list::get_size()
   {
      return m_stra.get_size();
   }

   const char * parameter_list::GetKey(int i)
   {
      return m_stra[i];
   }

   var  & parameter_list::GetFieldValue(int i)
   {
      return m_fieldvaluea[i];
   }

} // namespace vmssqlite

