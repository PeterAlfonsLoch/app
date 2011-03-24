#pragma once

namespace database
{

   class CLASS_DECL_ca field_definition_item : 
      virtual public ::radix::object
   {
   public:


      string m_strName;

      
      field_definition_item();
      field_definition_item(const field_definition_item & item);

      field_definition_item & operator = (const field_definition_item & item);

   };


   class CLASS_DECL_ca field_definition : 
      virtual public base_array < field_definition_item >
   {
   public:
      
   };



} // namespace simpledb
