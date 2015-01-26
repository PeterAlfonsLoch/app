#pragma once


namespace simpledb
{

   class CLASS_DECL_AXIS record_row : 
      virtual public ::file::serializable
   {
   public:

      table *     m_ptable;
      stringa     m_straFields;
      var         m_var;

      virtual void write(::file::output_stream & ostream);
      virtual void read(::file::input_stream & ostream);

   };


} // namespace simpledb


