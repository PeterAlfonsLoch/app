#include "framework.h"


namespace simpledb
{


   file_set::file_set(sp(::ca2::application) papp) :
      ca2(papp),
      ::ca2::file_set_sp(allocer())
   {

   }


   file_set::~file_set()
   {

   }


   void file_set::data_on_after_change(::ca2::signal_object * pobj)
   {
      
      SCAST_PTR(::database::change_event, pchange, pobj);

      if(pchange->m_key.m_idSection == m_dataid
      && pchange->m_key.m_idIndex == (const ::database::id &) ::ca2::system::idEmpty
      && pchange->m_key.m_idKey == (const ::database::id &) ::ca2::system::idEmpty)
      {

         refresh();

      }

   }


   bool file_set::refresh()
   {
      
      m_p->clear_search();

      stringa stra;

      bool_array baRecursive;
      
      if(!data_get(::ca2::system::idEmpty, ::ca2::system::idEmpty, stra))
         return false;

      data_get("recursive", ::ca2::system::idEmpty, baRecursive);
      
      // add_search calls Ex2FileSet refresh internally
      m_p->add_search(stra, baRecursive);

      return true;

   }


   bool file_set::add_search(const char * pszSearchDirectory)
   {

      stringa stra;

      data_get(::ca2::system::idEmpty, ::ca2::system::idEmpty, stra);

      if(stra.add_unique(pszSearchDirectory) < 0)
         return true;

      if(!data_set(::ca2::system::idEmpty, ::ca2::system::idEmpty, stra))
         return false;

      if(!refresh())
         return false;

      return true;

   }


   bool file_set::clear_search()
   {

      stringa stra;

      if(!data_set(::ca2::system::idEmpty, ::ca2::system::idEmpty, stra))
         return false;

      if(!refresh())
         return false;

      return true;

   }


} // namespace simpledb



