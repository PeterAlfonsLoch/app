#include "framework.h"


namespace simpledb
{


   table::table(base * pdatabase, const char * pszName) :
      element(pdatabase->get_app()),
      m_spfileMeta(pdatabase->get_app()),
      m_spfileFixed(pdatabase->get_app()),
      m_xmldocumentMeta(pdatabase->get_app())
   {


      m_strName = pszName;
      m_pdatabase = pdatabase;

      

      string strMetaPath;

      strMetaPath = System.dir().element("database/" + m_pdatabase->getDatabase() + "/" + m_strName, "meta.xml");

      if(!m_spfileMeta->open(strMetaPath, ::file::type_binary | ::file::binary_buffer::mode_read_write | ::file::binary_buffer::shareExclusive))
         throw 0;

      if(!m_xmldocumentMeta.load(m_spfileMeta))
         throw 0;

      sp(::xml::node) pfields = m_xmldocumentMeta.get_root()->get_child("fields");

      for(int32_t i = 0; i < pfields->get_children_count(); i++)
      {
         sp(::xml::node) pfield = pfields->child_at(i);
         if(pfield->get_name() != "field")
            continue;
         database::field_definition_item item;
         item = *pfield;
         m_fielddefinition.add(item);
      }

      string strFixedPath = m_xmldocumentMeta.get_root()->attr("fixed_path");
      if(strFixedPath.is_empty())
         strFixedPath = strMetaPath = System.dir().element("database/" + m_pdatabase->getDatabase() + "/" + m_strName, "fixed.txt");

      if(!m_spfileFixed->open(strMetaPath, ::file::binary_buffer::mode_create | ::file::binary_buffer::modeNoTruncate | ::file::type_binary | ::file::binary_buffer::mode_read_write | ::file::binary_buffer::shareExclusive |
         ::file::binary_buffer::defer_create_directory))
         throw 0;

   }


} // namespace simpledb


