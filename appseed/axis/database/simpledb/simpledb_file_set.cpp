//#include "framework.h"


namespace simpledb
{


   file_set::file_set(::aura::application * papp) :
      ::object(papp),
      ::file::set(papp)
   {

      m_straFile.m_bDir      = false;
      m_straFile.m_bFile     = true;

   }


   file_set::~file_set()
   {

   }


   void file_set::data_on_after_change(signal_details * pobj)
   {

      SCAST_PTR(::database::change_event, pchange, pobj);

      if(pchange->m_key.m_id == m_dataid)
      {

         refresh();

      }

   }


   void file_set::refresh()
   {

      ::file::set::clear_search();

      stringa stra;

      bool_array baRecursive;

      if(!data_get(::aura::system::idEmpty, stra))
         return;

      data_load("recursive", baRecursive);

      // add_search calls Ex2FileSet refresh internally
      ::file::set::add_search(stra, baRecursive);

      ::file::set::refresh();



   }


   bool file_set::add_search(const char * pszSearchDirectory, bool bRecursive)
   {

      stringa stra;

      bool_array baRecursive;

      data_get(::aura::system::idEmpty, stra);

      data_load("recursive",baRecursive);

      index i = -1;

      if((i = stra.find_first_ci(pszSearchDirectory)) < 0)
      {

         stra.add(pszSearchDirectory);

         baRecursive.add(bRecursive);

         if(!data_set(::aura::system::idEmpty,stra))
            return false;

         if(!data_save("recursive",baRecursive))
            return false;

      }
      else
      {

         baRecursive.set_at_grow(i,bRecursive);

         if(!data_save("recursive",baRecursive))
            return false;

      }

      refresh();

      return true;

   }


   void file_set::clear_search()
   {

      ::file::set::clear_search();

      stringa stra;

      data_set(::aura::system::idEmpty, stra);

   }


} // namespace simpledb



