#include "framework.h"
//#include "axis/net/net_sockets.h"


namespace file
{


   application::application(::aura::application * papp) :
      object(papp)
   {

   }


   application::~application()
   {

   }

   ::cres application::copy(const ::file::path & pszNew,const ::file::path & pszOld,bool bFailIfExists,e_extract eextract)
   {
      return m_pauraapp->m_paurasystem->m_spfile->copy(pszNew, pszOld, bFailIfExists, eextract, m_pauraapp);
   }

   ::cres application::move(const ::file::path & pszNew,const ::file::path & pszOld)
   {
      return m_pauraapp->m_paurasystem->m_spfile->move(pszNew,pszOld,m_pauraapp);
   }

   ::cres application::del(const ::file::path & psz)
   {
      return m_pauraapp->m_paurasystem->m_spfile->del(psz,m_pauraapp);
   }

   ::cres application::rename(const ::file::path & pszNew,const ::file::path & pszOld)
   {
      return m_pauraapp->m_paurasystem->m_spfile->rename(pszNew,pszOld,m_pauraapp);
   }

   void application::trash_that_is_not_trash(const ::file::path & psz)
   {
      return m_pauraapp->m_paurasystem->m_spfile->trash_that_is_not_trash(psz, m_pauraapp);
   }

   void application::trash_that_is_not_trash(::file::patha & stra)
   {
      return m_pauraapp->m_paurasystem->m_spfile->trash_that_is_not_trash(stra, m_pauraapp);
   }

   ::cres application::replace(const ::file::path & pszContext,const string & pszFind,const string & pszReplace)
   {
      return m_pauraapp->m_paurasystem->m_spfile->replace(pszContext, pszFind, pszReplace, m_pauraapp);
   }

   bool application::exists(const ::file::path & pszPath)
   {

      return m_pauraapp->m_paurasystem->m_spfile->exists(pszPath, m_pauraapp);

   }


 /*  bool application::exists(const string & strPath)
   {

      return m_pauraapp->m_paurasystem->m_spfile->exists(strPath, m_pauraapp);

   }

   bool application::exists(const var & var)
   {

      const string & strPath = var.get_string();


      return m_pauraapp->m_paurasystem->m_spfile->exists(strPath, m_pauraapp);

   }*/


   var application::length(const ::file::path & pszPath)
   {

      return m_pauraapp->m_paurasystem->m_spfile->length(pszPath, m_pauraapp);

   }


   //var application::length(const string & strPath)
   //{


   //   return m_pauraapp->m_paurasystem->m_spfile->length(strPath, m_pauraapp);

   //}


   //var application::length(const var & var)
   //{

   //   return m_pauraapp->m_paurasystem->m_spfile->length(var.get_string(), m_pauraapp);

   //}


   ::file::path application::time(const ::file::path & pszBasePath,int32_t iDepth,const string & pszPrefix,const string & pszSuffix)
   {

      return m_pauraapp->m_paurasystem->m_spfile->time(m_pauraapp, pszBasePath, iDepth, pszPrefix, pszSuffix);

   }


   ::file::path application::time_square(const string & pszPrefix,const string & pszSuffix)
   {

      return m_pauraapp->m_paurasystem->m_spfile->time_square(m_pauraapp, pszPrefix, pszSuffix);

   }


   ::file::path application::time_log(const string & pszId)
   {
      return m_pauraapp->m_paurasystem->m_spfile->time_log(m_pauraapp, pszId);
   }

   ::file::buffer_sp application::time_square_file(const char * pszPrefix, const char * pszSuffix)
   {
      return m_pauraapp->m_paurasystem->m_spfile->time_square_file(m_pauraapp, pszPrefix, pszSuffix);
   }

   ::file::buffer_sp application::get(const ::file::path & name)
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

   bool application::add_contents(var varFile,const char * lpcszContents)
   {
      return m_pauraapp->m_paurasystem->m_spfile->add_contents(varFile,lpcszContents,m_pauraapp);
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



   ::file::buffer_sp application::friendly_get_file(var varFile, UINT nOpenFlags, cres * pfesp)
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

   ::file::buffer_sp application::get_file(var varFile, UINT nOpenFlags, cres * pfesp)
   {

      if(pfesp != NULL)
      {
         ::release(pfesp->m_p);
      }

      ::cres cres;

      ::file::buffer_sp spfile;

      ::file::path strPath;

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

         cres = spfile->open(strPath,nOpenFlags);

      }

      if(cres.failed())
      {

         spfile.release();

         if(pfesp != NULL)
         {

            *pfesp = cres;

         }

      }

      return spfile;

   }

/*   ::file::byte_stream application::get_byte_stream(var varFile, UINT nOpenFlags)
   {

      return get_file(varFile, nOpenFlags);

   }
   */

   void application::dtf(const ::file::path & pszFile,const ::file::path & pszDir)
   {

      return m_pauraapp->m_paurasystem->m_spfile->dtf(pszFile,pszDir,m_pauraapp);

   }


   void application::dtf(const ::file::path & pszFile,::file::patha & stra,::file::patha & straRelative)
   {

      return m_pauraapp->m_paurasystem->m_spfile->dtf(pszFile,stra,m_pauraapp);

   }


   void application::ftd(const ::file::path & pszDir,const ::file::path & pszFile)
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










































