#include "StdAfx.h"

namespace devedge
{

   folder::folder(::ca::application * papp) :
      ca(papp),
      array_app_alloc < file, file & > (papp)
   {
   }

   void folder::load(project * pproject, const char * pszFilter)
   {
      m_pproject = pproject;
      m_strFilter = pszFilter;
      stringa straPath;
      System.dir().ls_pattern(pproject->m_strProjectDir, m_strFilter, &straPath);
      for(index i = 0; i < straPath.get_count(); i++)
      {
         file * pfile = add_new();
         pfile->initialize(this, straPath[i]);
      }
   }

   index folder::find(const char * pszName)
   {
      for(index i = 0; i < get_count(); i++)
      {
         file & file = element_at(i);
         if(file.m_strName.CompareNoCase(pszName) == 0)
            return i;
      }
      return -1;
   }

   bool folder::has(const char * pszName)
   {
      return find(pszName) >= 0;
   }

} // namespace devedge