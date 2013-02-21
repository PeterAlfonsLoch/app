#pragma once

namespace database
{

   class CLASS_DECL_ca field_definition_item : 
      virtual public ::gen::object
   {
   public:

      enum e_type
      {
         type_none,
         type_text,
      };


      string      m_strName;
      int32_t         m_iSize;
      e_type      m_etype;

      
      field_definition_item();
      field_definition_item(const field_definition_item & item);

      field_definition_item & operator = (const field_definition_item & item);
      field_definition_item & operator = (const xml::node & node);


      e_type field_str_to_type(const char * pszType);

   };


   class CLASS_DECL_ca field_definition : 
      virtual public base_array < field_definition_item >
   {
   public:
      
   };



} // namespace simpledb
