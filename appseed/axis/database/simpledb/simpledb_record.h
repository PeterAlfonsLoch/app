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

      virtual void write(::file::ostream & ostream) const;
      virtual void read(::file::istream & ostream);

   };


} // namespace simpledb


