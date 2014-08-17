#include "framework.h"


namespace database
{


   //************* DbErrors implementation ***************


   DbErrors::DbErrors()
   {

      fprintf(stderr, "\nUnknown CDatabase Error\n");
   }


   DbErrors::DbErrors(const char *msg, ...)
   {

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
      return this->get_size() <= 0;
   }

   ::count parameter_list::get_size()
   {
      return m_stra.get_size();
   }

   const char * parameter_list::GetKey(index i)
   {
      return m_stra[i];
   }

   var  & parameter_list::GetFieldValue(index i)
   {
      return m_fieldvaluea[i];
   }

   record::record()
   {
   }

   record::record(const record & record)
   {
      operator = (record);
   }

   record::~record()
   {
   }

   record & record::operator = (const record & record)
   {
      if(this != &record)
      {
         var_array::operator = ((const var_array &) record);
      }
      return *this;
   }


   result_set::result_set()
   {
   }

   result_set::result_set(sp(::base::application) papp) :
   element(papp)
   {
   }

   result_set::result_set(const result_set & set) :
   element(set.get_app())
   {
      operator = (set);
   }

   result_set & result_set::operator = (const result_set & set)
   {

      if(&set != this)
      {
         record_header     = set.record_header;
         records           = set.records;
      }
      return *this;

   }

   void result_set::write(::file::output_stream & ostream)
   {
      record_header.write(ostream);
      records.write(ostream);
   }

   void result_set::read(::file::input_stream & istream)
   {
      record_header.read(istream);
      records.read(istream);
   }

   void field_properties::write(::file::output_stream & ostream)
   {
      ostream << name;
      ostream << display_name;
      ostream << (int32_t) type;
      ostream << field_table; //?
      ostream << read_only;
      ostream << field_len;
      ostream << field_flags;
      ostream << idx;
   }

   void field_properties::read(::file::input_stream & istream)
   {
      istream >> name;
      istream >> display_name;
      istream >> (int32_t &) type;
      istream >> field_table; //?
      istream >> read_only;
      istream >> field_len;
      istream >> field_flags;
      istream >> idx;
   }


} // namespace vmssqlite



