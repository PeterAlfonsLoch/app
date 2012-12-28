#include "framework.h"


namespace simpledb
{


   table::table(base * pdatabase, const char * pszName) :
      ::ca::ca(pdatabase->get_app()),
      m_spfileMeta(pdatabase->get_app()),
      m_spfileFixed(pdatabase->get_app()),
      m_xmldocumentMeta(pdatabase->get_app())
   {


      m_strName = pszName;
      m_pdatabase = pdatabase;

      

      string strMetaPath;

      strMetaPath = System.dir().ca2("database/" + m_pdatabase->getDatabase() + "/" + m_strName, "meta.xml");

      if(!m_spfileMeta->open(strMetaPath, ::ex1::file::type_binary | ::ex1::file::mode_read_write | ::ex1::file::shareExclusive))
         throw 0;

      if(!m_xmldocumentMeta.load(m_spfileMeta))
         throw 0;

      ::xml::node * pfields = m_xmldocumentMeta.get_root()->get_child("fields");

      for(int32_t i = 0; i < pfields->get_children_count(); i++)
      {
         ::xml::node * pfield = pfields->child_at(i);
         if(pfield->get_name() != "field")
            continue;
         database::field_definition_item item;
         item = *pfield;
         m_fielddefinition.add(item);
      }

      string strFixedPath = m_xmldocumentMeta.get_root()->attr("fixed_path");
      if(strFixedPath.is_empty())
         strFixedPath = strMetaPath = System.dir().ca2("database/" + m_pdatabase->getDatabase() + "/" + m_strName, "fixed.txt");

      if(!m_spfileFixed->open(strMetaPath, ::ex1::file::mode_create | ::ex1::file::modeNoTruncate | ::ex1::file::type_binary | ::ex1::file::mode_read_write | ::ex1::file::shareExclusive |
         ::ex1::file::defer_create_directory))
         throw 0;

   }


} // namespace simpledb


