#include "StdAfx.h"

namespace simpledb
{

   file_set::file_set(::ca::application * papp) :
      ca(papp),
      ex2::file_set_sp(papp)
   {
   }

   file_set::~file_set()
   {
   }

   void file_set::data_on_after_change(gen::signal_object * pobj)
   {
      SCAST_PTR(::database::change_event, pchange, pobj);
      if(pchange->m_key.m_idSection == m_dataid
      && pchange->m_key.m_idIndex == (const ::database::id &) ::ca::system::idEmpty
      && pchange->m_key.m_idKey == (const ::database::id &) ::ca::system::idEmpty)
      {
         refresh();
      }
   }

   void file_set::refresh()
   {
      stringa stra;
      bool_array baRecursive;
      data_get(::ca::system::idEmpty, ::ca::system::idEmpty, stra);
      data_get("recursive", ::ca::system::idEmpty, baRecursive);
      m_p->clear_search();
      // add_search calls Ex2FileSet refresh internally
      m_p->add_search(stra, baRecursive);
   }

   bool file_set::add_search(const char * pszSearchDirectory)
   {
      stringa stra;
      data_get(::ca::system::idEmpty, ::ca::system::idEmpty, stra);
      if(stra.add_unique(pszSearchDirectory) < 0)
         return true;
      if(!data_set(::ca::system::idEmpty, ::ca::system::idEmpty, stra))
         return false;
      refresh();
      return true;
   }

} // namespace simpledb