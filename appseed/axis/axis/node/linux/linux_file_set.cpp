#include "framework.h"
#include "linux.h"


namespace linux
{


   file_set::file_set(sp(::aura::application) papp) :
      ::object(papp)
   {

   }


   file_set::~file_set()
   {

   }


   void file_set::add_search(stringa & stra, bool_array & baRecursive)
   {

      m_straSearch.add(stra);

      m_baRecursive.add(baRecursive);

      refresh();

   }


   void file_set::add_filter(stringa & stra)
   {

      m_straFilter.add(stra);

      refresh();

   }


   ::count file_set::get_file_count()
   {

      return m_straFile.get_size();

   }


   void file_set::file_at(::index i, string & str)
   {

      str = m_straFile[i];

   }


   ::index file_set::find_first_file(const char * lpcsz, ::index iStart)
   {

      return m_straFile.find_first_ci(lpcsz, iStart);

   }


   void file_set::clear_search()
   {

      m_straSearch.remove_all();

   }


   void file_set::clear_filter()
   {

      m_straFilter.remove_all();

   }


   void file_set::clear_file()
   {

      m_straFile.remove_all();

   }


   void file_set::refresh()
   {

      clear_file();

      string strFilter;

      int32_t i, j;

      string strFile;

      string str;

      for(i = 0; i < m_straSearch.get_size(); i++)
      {

         bool bRecursive = true;

         if(i < m_baRecursive.get_size())
         {

            bRecursive = m_baRecursive[i];

         }

         m_straFile.m_pprovider = get_app();

         for(j = 0; j < m_straFilter.get_size(); j++)
         {

            string strFilter = m_straFilter.element_at(j);

            strFilter.trim("\\/");

            if(bRecursive)
            {

               m_straFile.rls_pattern(m_straSearch.element_at(i), strFilter);

            }
            else
            {

               m_straFile.ls_pattern(m_straSearch.element_at(i), strFilter);

            }

         }

      }

   }


} // namespace mac



