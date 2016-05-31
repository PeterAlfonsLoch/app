//#include "framework.h"


namespace file
{




   set::set(::ace::application * papp) :
      ::object(papp)
   {

   }


   set::~set()
   {

   }


   void set::add_search(stringa & stra, bool_array & baRecursive)
   {

      m_straSearch.add(stra);

      m_baRecursive.add(baRecursive);

      //refresh();

   }

   void set::add_filter(stringa & stra)
   {

      m_straFilter.add(stra);

   }



   ::count set::get_file_count()
   {

      return m_straFile.get_size();

   }


   void set::file_at(::index i, string & str)
   {

      str = m_straFile[i];

   }


   ::index set::find_first_file(const char * lpcsz, ::index iStart)
   {

      return m_straFile.find_first_ci(lpcsz, iStart);

   }




   void set::refresh()
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

      m_straFile.add(m_straFileAddUp);

   }


   void set::clear_file()
   {

      m_straFile.clear();

   }


   void set::clear_search()
   {

      m_straSearch.remove_all();

      m_baRecursive.remove_all();

   }


   void set::clear_filter()
   {

      m_straFilter.remove_all();

   }


   bool set::get_next_file(const char * pszFile, string & strNext)
   {

      index iFind = find_first_file(pszFile);

      if(iFind < 0)
      {

         iFind = -1;

      }

      index iNext = iFind + 1;

      if(iNext >= m_straFile.get_count())
      {

         iNext = 0;

      }

      if(iNext >= m_straFile.get_count())
      {

         return false;

      }

      strNext =  m_straFile[iNext];

      return true;

   }


   string set::get_next_file(const char * pszFile)
   {

      string strNext;

      if(!get_next_file(pszFile, strNext))
      {

         return "";

      }

      return strNext;

   }


} // namespace file





