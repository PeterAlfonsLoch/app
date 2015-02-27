//#include "framework.h"


namespace simpledb
{


   table::table(base * pdatabase, const char * pszName) :
      object(pdatabase->get_app()),
      m_spfileMeta(pdatabase->get_app()),
      m_spfileFixed(pdatabase->get_app())
   {


      m_strName = pszName;
      m_pdatabase = pdatabase;

      

      string strMetaPath;

      strMetaPath = System.dir().element("database/" + m_pdatabase->getDatabase() + "/" + m_strName, "meta.xml");

      if(!m_spfileMeta->open(strMetaPath, ::file::type_binary | ::file::mode_read_write | ::file::share_exclusive))
         throw 0;

      ::file::input_stream is(m_spfileMeta);

      if(!m_xmldocumentMeta.load(is))
         throw 0;

      ::xml::node  pfields = m_xmldocumentMeta.root().get_child("fields");

      for(int32_t i = 0; i < pfields->get_children_count(); i++)
      {
         ::xml::node  pfield = pfields->child_at(i);
         if(pfield->get_name() != "field")
            continue;
         ::database::field_definition_item item;
         item = *pfield;
         m_fielddefinition.add(item);
      }

      string strFixedPath = m_xmldocumentMeta.root().attr("fixed_path");
      if(strFixedPath.is_empty())
         strFixedPath = strMetaPath = System.dir().element("database/" + m_pdatabase->getDatabase() + "/" + m_strName, "fixed.txt");

      if(!m_spfileFixed->open(strMetaPath, ::file::mode_create | ::file::mode_no_truncate | ::file::type_binary | ::file::mode_read_write | ::file::share_exclusive |
         ::file::defer_create_directory))
         throw 0;

   }


} // namespace simpledb


