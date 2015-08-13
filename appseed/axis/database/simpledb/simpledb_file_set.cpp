//#include "framework.h"


namespace simpledb
{


   file_set::file_set(::aura::application * papp) :
      ::object(papp),
      ::file::set_sp(allocer())
   {

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


   bool file_set::refresh()
   {

      m_p->clear_search();

      stringa stra;

      bool_array baRecursive;

      if(!data_get(::aura::system::idEmpty, stra))
         return false;

      data_load("recursive", baRecursive);

      // add_search calls Ex2FileSet refresh internally
      m_p->add_search(stra, baRecursive);

      return true;

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


      if(!refresh())
         return false;

      return true;

   }


   bool file_set::clear_search()
   {

      stringa stra;

      if(!data_set(::aura::system::idEmpty, stra))
         return false;

      if(!refresh())
         return false;

      return true;

   }


} // namespace simpledb



