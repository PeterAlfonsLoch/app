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
         return m_psystem->m_file.copy(pszNew, pszOld, bFailIfExists, m_papp);
      }

      void application::trash_that_is_not_trash(const char * psz)
      {
         return m_psystem->m_file.trash_that_is_not_trash(psz, m_papp);
      }

      void application::trash_that_is_not_trash(stringa & stra)
      {
         return m_psystem->m_file.trash_that_is_not_trash(stra, m_papp);
      }

      void application::replace(const char * pszContext, const char * pszFind, const char * pszReplace)
      {
         return m_psystem->m_file.replace(pszContext, pszFind, pszReplace, m_papp);
      }

      bool application::exists(const char * pszPath)
      {

         if(gen::str::begins_ci(pszPath, "uifs://"))
         {
            return ifs(m_papp, "").file_exists(pszPath);
         }

         return m_psystem->m_file.exists(pszPath, m_papp);

      }


      bool application::exists(const string & strPath)
      {

         if(gen::str::begins_ci_iws(strPath, "uifs://"))
         {
            return ifs(m_papp, "").file_exists(strPath);
         }

         return m_psystem->m_file.exists(strPath, m_papp);

      }

      bool application::exists(const var & var)
      {

         const string & strPath = var.get_string();

         if(gen::str::begins_ci_iws(strPath, "uifs://"))
         {
            return ifs(m_papp, "").file_exists(strPath);
         }

         return m_psystem->m_file.exists(strPath, m_papp);

      }

      string application::time(const char * pszBasePath, int iDepth, const char * pszPrefix, const char * pszSuffix)
      {
         return m_psystem->m_file.time(m_papp, pszBasePath, iDepth, pszPrefix, pszSuffix);
      }

      string application::time_square(const char * pszPrefix, const char * pszSuffix)
      {
         return m_psystem->m_file.time_square(m_papp, pszPrefix, pszSuffix);
      }

      string application::time_log(const char * pszId)
      {
         return m_psystem->m_file.time_log(m_papp, pszId);
      }

      ex1::filesp application::time_square_file(const char * pszPrefix, const char * pszSuffix)
      {
         return m_psystem->m_file.time_square_file(m_papp, pszPrefix, pszSuffix);
      }

      ::ex1::filesp application::get(const char * name)
      {
         return m_psystem->m_file.get(name, m_papp);
      }

      string application::as_string(var varFile)
      {
         return m_psystem->m_file.as_string(varFile, m_papp);
      }

      string application::as_string(var varFile, var varQuery)
      {
         return m_psystem->m_file.as_string(varFile, varQuery, m_papp);
      }

      void application::as_memory(var varFile, primitive::memory & mem)
      {
         return m_psystem->m_file.as_memory(varFile, mem, m_papp);
      }

      void application::lines(stringa & stra, var varFile)
      {
         return m_psystem->m_file.lines(stra, varFile, m_papp);
      }

      bool application::put_contents(var varFile, const void * pvoidContents, count count)
      {
         return m_psystem->m_file.put_contents(varFile, pvoidContents, count, m_papp);
      }

      bool application::put_contents(var varFile, const char * lpcszContents)
      {
         return m_psystem->m_file.put_contents(varFile, lpcszContents, m_papp);
      }

      bool application::put_contents(var varFile, ex1::file & file)
      {
         return m_psystem->m_file.put_contents(varFile, file, m_papp);
      }

      bool application::put_contents(var varFile, primitive::memory & mem)
      {
         return m_psystem->m_file.put_contents(varFile, mem, m_papp);
      }

      bool application::put_contents_utf8(var varFile, const char * lpcszContents)
      {
         return m_psystem->m_file.put_contents_utf8(varFile, lpcszContents, m_papp);
      }

      string application::sys_temp(const char * pszName, const char * pszExtension)
      {
         return m_psystem->m_file.sys_temp(pszName, pszExtension, m_papp);
      }


   } // namespace file


} // namespace ca2



