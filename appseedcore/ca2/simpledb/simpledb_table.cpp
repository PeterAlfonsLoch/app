#include "StdAfx.h"

namespace simpledb
{

   table::table(base * pdatabase, const char * pszName) :
      ::ca::ca(pdatabase->get_app()),
      m_spfileMeta(pdatabase->get_app()),
      m_spfileFixed(pdatabase->get_app()),
      m_nodeMeta(pdatabase->get_app())
   {
      m_strName = pszName;
      m_pdatabase = pdatabase;

      

      string strMetaPath;

      strMetaPath = System.dir().ca2("database/" + m_pdatabase->getDatabase() + "/" + m_strName, "meta.xml");

      if(!m_spfileMeta->open(strMetaPath, ::ex1::file::type_binary | ::ex1::file::mode_read_write | ::ex1::file::shareExclusive))
         throw 0;

      if(!m_nodeMeta.load(m_spfileMeta))
         throw 0;

      ::xml::node * pfields = m_nodeMeta.get_child("fields");

      for(int i = 0; i < pfields->get_children_count(); i++)
      {
         ::xml::node * pfield = m_nodeMeta.child_at(i);
         if(pfield->m_strName != "field")
            continue;
         database::field_definition_item item;
         item.m_strName = pfield->attr("name");
         m_fielddefinition.add(item);
      }

      string strFixedPath = m_nodeMeta.attr("fixed_path");

      if(!m_spfileFixed->open(strMetaPath, ::ex1::file::type_binary | ::ex1::file::mode_read_write | ::ex1::file::shareExclusive))
         throw 0;

   }

} // namespace simpledb