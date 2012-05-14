#include "framework.h"

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
      && pchange->m_key.m_idIndex == (const ::database::id &) ::radix::system::idEmpty
      && pchange->m_key.m_idKey == (const ::database::id &) ::radix::system::idEmpty)
      {
         refresh();
      }
   }

   void file_set::refresh()
   {
      stringa stra;
      bool_array baRecursive;
      data_get(::radix::system::idEmpty, ::radix::system::idEmpty, stra);
      data_get("recursive", ::radix::system::idEmpty, baRecursive);
      m_p->clear_search();
      // add_search calls Ex2FileSet refresh internally
      m_p->add_search(stra, baRecursive);
   }

   bool file_set::add_search(const char * pszSearchDirectory)
   {
      stringa stra;
      data_get(::radix::system::idEmpty, ::radix::system::idEmpty, stra);
      if(stra.add_unique(pszSearchDirectory) < 0)
         return true;
      if(!data_set(::radix::system::idEmpty, ::radix::system::idEmpty, stra))
         return false;
      refresh();
      return true;
   }

} // namespace simpledb