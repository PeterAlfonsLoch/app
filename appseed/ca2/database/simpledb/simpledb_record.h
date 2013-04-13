#pragma once


namespace simpledb
{

   class CLASS_DECL_ca2 record_row : 
      virtual public ::ca::byte_serializable
   {
   public:

      table *     m_ptable;
      stringa     m_straFields;
      var         m_var;

      virtual void write(::ca::byte_output_stream & ostream);
      virtual void read(::ca::byte_input_stream & ostream);

   };


} // namespace simpledb


