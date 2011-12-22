#include "StdAfx.h"


namespace ca
{


   namespace file
   {


      application::application()
      {
      }

      void application::copy(const char * pszNew, const char * pszOld, bool bFailIfExists)
      {
         return System.file().copy(pszNew, pszOld, bFailIfExists, m_papp);
      }

      void application::replace(const char * pszContext, const char * pszFind, const char * pszReplace)
      {
         return System.file().replace(pszContext, pszFind, pszReplace, m_papp);
      }

      bool application::exists(const char * pszPath)
      {
         string strPath(pszPath);
         strPath.trim();
         if(gen::str::begins_ci(strPath, "uifs://"))
         {
            return ifs(m_papp, "").file_exists(strPath);
         }
         return System.file().exists(pszPath, m_papp);
      }


      string application::as_string(var varFile)
      {
         return System.file().as_string(varFile, m_papp);
      }

      string application::as_string(var varFile, var varQuery)
      {
         return System.file().as_string(varFile, varQuery, m_papp);
      }

      void application::as_memory(var varFile, primitive::memory & mem)
      {
         return System.file().as_memory(varFile, mem, m_papp);
      }
   
      void application::lines(stringa & stra, var varFile)
      {
         return System.file().lines(stra, varFile, m_papp);
      }

      bool application::put_contents(var varFile, const void * pvoidContents, count count)
      {
         return System.file().put_contents(varFile, pvoidContents, count, m_papp);
      }

      bool application::put_contents(var varFile, const char * lpcszContents)
      {
         return System.file().put_contents(varFile, lpcszContents, m_papp);
      }

      bool application::put_contents(var varFile, ex1::file & file)
      {
         return System.file().put_contents(varFile, file, m_papp);
      }

      bool application::put_contents(var varFile, primitive::memory & mem)
      {
         return System.file().put_contents(varFile, mem, m_papp);
      }

      bool application::put_contents_utf8(var varFile, const char * lpcszContents)
      {
         return System.file().put_contents_utf8(varFile, lpcszContents, m_papp);
      }

      string application::sys_temp(const char * pszName, const char * pszExtension)
      {
         return System.file().sys_temp(pszName, pszExtension, m_papp);
      }


   } // namespace file


} // namespace ca2



