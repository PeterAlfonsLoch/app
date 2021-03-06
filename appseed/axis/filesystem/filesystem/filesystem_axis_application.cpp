#include "framework.h"
//#include "axis/net/net_sockets.h"



namespace file
{


   namespace axis
   {


      application::application(::aura::application * papp) :
         ::object(papp),
         ::file::application(papp)
      {

      }


      application::~application()
      {

      }


      cres application::copy(const ::file::path & pszNew, const ::file::path & pszOld, bool bFailIfExists, e_extract eextract)
      {

         return m_pauraapp->m_paurasystem->m_spfile->copy(pszNew, pszOld, bFailIfExists, eextract, m_pauraapp);

      }


      cres application::move(const ::file::path & pszNew, const ::file::path & pszOld)
      {

         return m_pauraapp->m_paurasystem->m_spfile->move(pszNew, pszOld, m_pauraapp);

      }


      cres application::del(const ::file::path & psz)
      {

         return m_pauraapp->m_paurasystem->m_spfile->del(psz, m_pauraapp);

      }


      cres application::rename(const ::file::path & pszNew, const ::file::path & pszOld)
      {

         return m_pauraapp->m_paurasystem->m_spfile->rename(pszNew, pszOld, m_pauraapp);

      }


      void application::trash_that_is_not_trash(const ::file::path & psz)
      {

         return m_pauraapp->m_paurasystem->m_spfile->trash_that_is_not_trash(psz, m_pauraapp);

      }


      void application::trash_that_is_not_trash(::file::patha & stra)
      {

         return m_pauraapp->m_paurasystem->m_spfile->trash_that_is_not_trash(stra, m_pauraapp);

      }


      cres application::replace(const ::file::path & pszContext, const string & pszFind, const string & pszReplace)
      {

         return m_pauraapp->m_paurasystem->m_spfile->replace(pszContext, pszFind, pszReplace, m_pauraapp);

      }


      bool application::exists(const ::file::path & pszPath)
      {

         if (::str::begins_ci(pszPath, "uifs://"))
         {

            return AppUser(m_pauraapp).m_pifs->file_exists(pszPath);

         }

         return m_pauraapp->m_paurasystem->m_spfile->exists(pszPath, m_pauraapp);

      }


      var application::length(const ::file::path & pszPath)
      {

         if (::str::begins_ci(pszPath, "uifs://"))
         {

            return AppUser(m_pauraapp).m_pifs->file_length(pszPath);

         }

         return m_pauraapp->m_paurasystem->m_spfile->length(pszPath, m_pauraapp);

      }




      ::file::path application::time(const ::file::path & pszBasePath, int32_t iDepth, const string & pszPrefix, const string & pszSuffix)
      {

         return m_pauraapp->m_paurasystem->m_spfile->time(m_pauraapp, pszBasePath, iDepth, pszPrefix, pszSuffix);

      }


      ::file::path application::time_square(const string & pszPrefix, const string & pszSuffix)
      {

         return m_pauraapp->m_paurasystem->m_spfile->time_square(m_pauraapp);

      }


      ::file::path application::time_log(const string & pszId)
      {
         return m_pauraapp->m_paurasystem->m_spfile->time_log(m_pauraapp, pszId);
      }

      ::file::file_sp application::time_square_file(const string & pszPrefix, const string & pszSuffix)
      {
         return m_pauraapp->m_paurasystem->m_spfile->time_square_file(m_pauraapp, pszPrefix, pszSuffix);
      }

      ::file::file_sp application::get(const ::file::path & name)
      {
         return m_pauraapp->m_paurasystem->m_spfile->get(name, m_pauraapp);
      }

      string application::as_string(var varFile)
      {
         return m_pauraapp->m_paurasystem->m_spfile->as_string(varFile, m_pauraapp);
      }

      string application::as_string(var varFile, var & varQuery)
      {
         return m_pauraapp->m_paurasystem->m_spfile->as_string(varFile, varQuery, m_pauraapp);
      }

      void application::as_memory(var varFile, memory & mem)
      {
         return m_pauraapp->m_paurasystem->m_spfile->as_memory(varFile, mem, m_pauraapp);
      }

      void application::lines(stringa & stra, var varFile)
      {
         return m_pauraapp->m_paurasystem->m_spfile->lines(stra, varFile, m_pauraapp);
      }

      bool application::put_contents(var varFile, const void * pvoidContents, ::count count)
      {
         return m_pauraapp->m_paurasystem->m_spfile->put_contents(varFile, pvoidContents, count, m_pauraapp);
      }

      bool application::put_contents(var varFile, const char * lpcszContents)
      {
         return m_pauraapp->m_paurasystem->m_spfile->put_contents(varFile, lpcszContents, m_pauraapp);
      }

      bool application::put_contents(var varFile, ::file::reader & reader)
      {
         return m_pauraapp->m_paurasystem->m_spfile->put_contents(varFile, reader, m_pauraapp);
      }

      bool application::put_contents(var varFile, memory & mem)
      {
         return m_pauraapp->m_paurasystem->m_spfile->put_contents(varFile, mem, m_pauraapp);
      }

      bool application::put_contents_utf8(var varFile, const char * lpcszContents)
      {
         return m_pauraapp->m_paurasystem->m_spfile->put_contents_utf8(varFile, lpcszContents, m_pauraapp);
      }

      string application::sys_temp(const ::file::path & pszName, const string & pszExtension)
      {
         return m_pauraapp->m_paurasystem->m_spfile->sys_temp(pszName, pszExtension, m_pauraapp);
      }


      void application::dtf(const ::file::path & pszFile, const ::file::path & pszDir)
      {
         return m_pauraapp->m_paurasystem->m_spfile->dtf(pszFile, pszDir, m_pauraapp);
      }

      void application::dtf(const ::file::path & pszFile, ::file::patha & stra)
      {
         return m_pauraapp->m_paurasystem->m_spfile->dtf(pszFile, stra, m_pauraapp);
      }

      void application::ftd(const ::file::path & pszDir, const ::file::path & pszFile)
      {
         return m_pauraapp->m_paurasystem->m_spfile->ftd(pszDir, pszFile, m_pauraapp);
      }


      bool application::crypto_set(var varFile, const char * pszData, const char * pszSalt)
      {
         // attention: operation on System crypto
         return m_pauraapp->m_paxissystem->m_spcrypto->file_set(varFile, pszData, pszSalt, m_pauraapp);
      }

      bool application::crypto_get(var varFile, string & str, const char * pszSalt)
      {
         // attention: operation on System crypto
         return m_pauraapp->m_paxissystem->m_spcrypto->file_get(varFile, str, pszSalt, m_pauraapp);
      }

      ::file::file_sp application::friendly_get_file(var varFile, UINT nOpenFlags, cres * pfesp)
      {
         if (pfesp != NULL)
         {
            ::release(pfesp->m_p);
         }

         try
         {
            return get_file(varFile, nOpenFlags, pfesp);
         }
         catch (...)
         {
            return NULL;
         }
      }

      ::file::file_sp application::get_file(var varFile, UINT nOpenFlags, cres * pfesp)
      {

         ::file::file_sp pfile = m_pauraapp->m_paxissystem->m_spfile->get_file(varFile,nOpenFlags,pfesp,m_pauraapp);

         if (pfile.is_set())
         {

            return pfile;

         }

         if (m_pauraapp->m_paxissession != NULL && Sess(m_pauraapp).m_spfsdata.is_set())
         {

            pfile = Sess(m_pauraapp).m_spfsdata->get_file(varFile, nOpenFlags, pfesp);

         }

         return pfile;

      }

      /*   ::file::byte_stream application::get_byte_stream(var varFile, UINT nOpenFlags)
         {

         return get_file(varFile, nOpenFlags);

         }
         */


   } // namespace axis


} // namespace core



























