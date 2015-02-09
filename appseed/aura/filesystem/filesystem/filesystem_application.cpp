#include "framework.h"
//#include "axis/net/net_sockets.h"


namespace file
{


   application::application(::aura::application * papp) :
      element(papp)
   {

   }


   application::~application()
   {

   }

   void application::copy(const char * pszNew, const char * pszOld, bool bFailIfExists, e_extract eextract)
   {
      return m_pauraapp->m_paurasystem->m_spfile->copy(pszNew, pszOld, bFailIfExists, eextract, m_pauraapp);
   }

   void application::trash_that_is_not_trash(const char * psz)
   {
      return m_pauraapp->m_paurasystem->m_spfile->trash_that_is_not_trash(psz, m_pauraapp);
   }

   void application::trash_that_is_not_trash(stringa & stra)
   {
      return m_pauraapp->m_paurasystem->m_spfile->trash_that_is_not_trash(stra, m_pauraapp);
   }

   void application::replace(const char * pszContext, const char * pszFind, const char * pszReplace)
   {
      return m_pauraapp->m_paurasystem->m_spfile->replace(pszContext, pszFind, pszReplace, m_pauraapp);
   }

   bool application::exists(const char * pszPath)
   {

      return m_pauraapp->m_paurasystem->m_spfile->exists(pszPath, m_pauraapp);

   }


   bool application::exists(const string & strPath)
   {

      return m_pauraapp->m_paurasystem->m_spfile->exists(strPath, m_pauraapp);

   }

   bool application::exists(const var & var)
   {

      const string & strPath = var.get_string();


      return m_pauraapp->m_paurasystem->m_spfile->exists(strPath, m_pauraapp);

   }


   var application::length(const char * pszPath)
   {

      return m_pauraapp->m_paurasystem->m_spfile->length(pszPath, m_pauraapp);

   }


   var application::length(const string & strPath)
   {


      return m_pauraapp->m_paurasystem->m_spfile->length(strPath, m_pauraapp);

   }


   var application::length(const var & var)
   {

      return m_pauraapp->m_paurasystem->m_spfile->length(var.get_string(), m_pauraapp);

   }


   string application::time(const char * pszBasePath, int32_t iDepth, const char * pszPrefix, const char * pszSuffix)
   {

      return m_pauraapp->m_paurasystem->m_spfile->time(m_pauraapp, pszBasePath, iDepth, pszPrefix, pszSuffix);

   }


   string application::time_square(const char * pszPrefix, const char * pszSuffix)
   {

      return m_pauraapp->m_paurasystem->m_spfile->time_square(m_pauraapp, pszPrefix, pszSuffix);

   }


   string application::time_log(const char * pszId)
   {
      return m_pauraapp->m_paurasystem->m_spfile->time_log(m_pauraapp, pszId);
   }

   ::file::buffer_sp application::time_square_file(const char * pszPrefix, const char * pszSuffix)
   {
      return m_pauraapp->m_paurasystem->m_spfile->time_square_file(m_pauraapp, pszPrefix, pszSuffix);
   }

   ::file::buffer_sp application::get(const char * name)
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

   void application::as_memory(var varFile, primitive::memory & mem)
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

   bool application::put_contents(var varFile, primitive::memory & mem)
   {
      return m_pauraapp->m_paurasystem->m_spfile->put_contents(varFile, mem, m_pauraapp);
   }

   bool application::put_contents_utf8(var varFile, const char * lpcszContents)
   {
      return m_pauraapp->m_paurasystem->m_spfile->put_contents_utf8(varFile, lpcszContents, m_pauraapp);
   }

   string application::sys_temp(const char * pszName, const char * pszExtension)
   {
      return m_pauraapp->m_paurasystem->m_spfile->sys_temp(pszName, pszExtension, m_pauraapp);
   }



   ::file::buffer_sp application::friendly_get_file(var varFile, UINT nOpenFlags, fesp * pfesp)
   {
      if(pfesp != NULL)
      {
         ::release(pfesp->m_p);
      }

      try
      {
         return get_file(varFile, nOpenFlags, pfesp);
      }
      catch(...)
      {
         return NULL;
      }
   }

   ::file::buffer_sp application::get_file(var varFile, UINT nOpenFlags, fesp * pfesp)
   {

      if(pfesp != NULL)
      {
         ::release(pfesp->m_p);
      }

      ::fesp fesp;

      ::file::buffer_sp spfile;

      string strPath;

      if (varFile.get_type() == var::type_element)
      {
         
         spfile = varFile.cast < ::file::stream_buffer >();

         if (spfile.is_set())
            return spfile;

      }
      else if(varFile.get_type() == var::type_string)
      {

         strPath = varFile;

         strPath.trim("\"'");

      }
      else if(varFile.get_type() == var::type_stra)
      {

         if(varFile.stra().get_count() > 0)
         {

            strPath = varFile.stra()[0];

         }

         strPath.trim("\"'");

      }
      else if(varFile.get_type() == var::type_propset)
      {

         if(varFile.has_property("url"))
         {

            strPath = varFile["url"];

            strPath.trim("\"'");

         }

      }

      if(varFile.get_type() == var::type_propset && varFile.propset()["file"].cast < ::file::binary_buffer >() != NULL)
      {

         spfile = varFile.propset()["file"].cast < ::file::binary_buffer >();

      }
      //else if(::str::find_file_extension("zip:", strPath) >= 0)
      //{

      //   /* xxx
      //   zip::InFile * pinfile = new zip::InFile(get_app());

      //   if(pinfile != NULL)
      //   {

      //      if(!pinfile->unzip_open(strPath, 0))
      //      {

      //         delete pinfile;

      //         pinfile = NULL;

      //      }

      //   }

      //   spfile = pinfile;

      //   */

      //}
      else if(::str::begins_eat_ci(strPath, "matter://"))
      {

          spfile = get_file(App(m_pauraapp).dir().matter(strPath), nOpenFlags);

      }
      else
      {

         if(strPath.is_empty())
         {
            TRACE("::application::get_file file with empty name!!");
            return spfile;
         }

         if((nOpenFlags & ::file::mode_create) == 0 && !exists(strPath))
         {
            TRACE("::application::file does not exist!! : \"%s\"", strPath);
            return spfile;
         }

         spfile = Application.alloc(System.type_info < ::file::binary_buffer > ());

         fesp = spfile->open(strPath,nOpenFlags);

      }

      if(!fesp)
      {

         spfile.release();

         if(pfesp != NULL)
         {

            *pfesp = fesp;

         }

      }

      return spfile;

   }

/*   ::file::byte_stream application::get_byte_stream(var varFile, UINT nOpenFlags)
   {

      return get_file(varFile, nOpenFlags);

   }
   */

   void application::dtf(const char * pszFile,const char * pszDir)
   {

      return m_pauraapp->m_paurasystem->m_spfile->dtf(pszFile,pszDir,m_pauraapp);

   }


   void application::dtf(const char * pszFile,stringa & stra,stringa & straRelative)
   {

      return m_pauraapp->m_paurasystem->m_spfile->dtf(pszFile,stra,straRelative,m_pauraapp);

   }


   void application::ftd(const char * pszDir,const char * pszFile)
   {

      return m_pauraapp->m_paurasystem->m_spfile->ftd(pszDir,pszFile,m_pauraapp);

   }


   bool application::crypto_set(var varFile,const char * pszData,const char * pszSalt)
   {

      throw interface_only_exception(get_app());

      return false;

   }
   
   
   bool application::crypto_get(var varFile,string & str,const char * pszSalt)
   {

      throw interface_only_exception(get_app());

      return false;

   }



} // namespace file










































