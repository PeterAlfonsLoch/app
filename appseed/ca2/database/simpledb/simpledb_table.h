
#pragma once

namespace simpledb
{

   class base;

   class CLASS_DECL_ca2 table : 
      virtual public ::ca2::object
   {
   public:
      
      
      base *                        m_pdatabase;
      ::ca2::filesp                 m_spfileMeta;
      ::xml::document               m_xmldocumentMeta;
      ::ca2::filesp                 m_spfileFixed;
      primitive::memory             m_memoryFixed;
      string                        m_strName;
      database::field_definition    m_fielddefinition;


      table(base * pdatabase, const char * pszName);

      base * get_database();

   };


} // namespace simpledb
