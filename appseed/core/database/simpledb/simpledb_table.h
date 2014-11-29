
#pragma once

namespace simpledb
{

   class base;

   class CLASS_DECL_CORE table : 
      virtual public ::object
   {
   public:
      
      
      base *                        m_pdatabase;
      ::file::binary_buffer_sp                 m_spfileMeta;
      ::xml::document               m_xmldocumentMeta;
      ::file::binary_buffer_sp                 m_spfileFixed;
      primitive::memory             m_memoryFixed;
      string                        m_strName;
      ::database::field_definition    m_fielddefinition;


      table(base * pdatabase, const char * pszName);

      base * get_database();

   };


} // namespace simpledb
