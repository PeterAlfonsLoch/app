#pragma once


namespace simpledb
{

   class CLASS_DECL_ca record_row : 
      virtual public ex1::byte_serializable
   {
   public:

      table *     m_ptable;
      stringa     m_straFields;
      var         m_var;

      virtual void write(::ex1::byte_output_stream & ostream);
      virtual void read(::ex1::byte_input_stream & ostream);

   };


} // namespace simpledb


