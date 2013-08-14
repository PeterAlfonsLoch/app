#include "framework.h"


namespace ca2
{


   file_application::file_application()
   {
   }

   void file_application::copy(const char * pszNew, const char * pszOld, bool bFailIfExists, e_extract eextract)
   {
      return m_papp->m_psystem->m_spfile->copy(pszNew, pszOld, bFailIfExists, eextract, m_papp);
   }

   void file_application::trash_that_is_not_trash(const char * psz)
   {
      return m_papp->m_psystem->m_spfile->trash_that_is_not_trash(psz, m_papp);
   }

   void file_application::trash_that_is_not_trash(stringa & stra)
   {
      return m_papp->m_psystem->m_spfile->trash_that_is_not_trash(stra, m_papp);
   }

   void file_application::replace(const char * pszContext, const char * pszFind, const char * pszReplace)
   {
      return m_papp->m_psystem->m_spfile->replace(pszContext, pszFind, pszReplace, m_papp);
   }

   bool file_application::exists(const char * pszPath)
   {

      if(::ca2::str::begins_ci(pszPath, "uifs://"))
      {
         return AppUser(m_papp).m_pifs->file_exists(pszPath);
      }

      return m_papp->m_psystem->m_spfile->exists(pszPath, m_papp);

   }


   bool file_application::exists(const string & strPath)
   {

      if(::ca2::str::begins_ci_iws(strPath, "uifs://"))
      {
         ::fontopus::user & user = AppUser(m_papp);
         return user.m_pifs->file_exists(strPath);
      }

      return m_papp->m_psystem->m_spfile->exists(strPath, m_papp);

   }

   bool file_application::exists(const var & var)
   {

      const string & strPath = var.get_string();

      if(::ca2::str::begins_ci_iws(strPath, "uifs://"))
      {
         return AppUser(m_papp).m_pifs->file_exists(strPath);
      }

      return m_papp->m_psystem->m_spfile->exists(strPath, m_papp);

   }

   string file_application::time(const char * pszBasePath, int32_t iDepth, const char * pszPrefix, const char * pszSuffix)
   {
      return m_papp->m_psystem->m_spfile->time(m_papp, pszBasePath, iDepth, pszPrefix, pszSuffix);
   }

   string file_application::time_square(const char * pszPrefix, const char * pszSuffix)
   {
      return m_papp->m_psystem->m_spfile->time_square(m_papp, pszPrefix, pszSuffix);
   }

   string file_application::time_log(const char * pszId)
   {
      return m_papp->m_psystem->m_spfile->time_log(m_papp, pszId);
   }

   ::ca2::filesp file_application::time_square_file(const char * pszPrefix, const char * pszSuffix)
   {
      return m_papp->m_psystem->m_spfile->time_square_file(m_papp, pszPrefix, pszSuffix);
   }

   ::ca2::filesp file_application::get(const char * name)
   {
      return m_papp->m_psystem->m_spfile->get(name, m_papp);
   }

   string file_application::as_string(var varFile)
   {
      return m_papp->m_psystem->m_spfile->as_string(varFile, m_papp);
   }

   string file_application::as_string(var varFile, var & varQuery)
   {
      return m_papp->m_psystem->m_spfile->as_string(varFile, varQuery, m_papp);
   }

   void file_application::as_memory(var varFile, primitive::memory & mem)
   {
      return m_papp->m_psystem->m_spfile->as_memory(varFile, mem, m_papp);
   }

   void file_application::lines(stringa & stra, var varFile)
   {
      return m_papp->m_psystem->m_spfile->lines(stra, varFile, m_papp);
   }

   bool file_application::put_contents(var varFile, const void * pvoidContents, ::count count)
   {
      return m_papp->m_psystem->m_spfile->put_contents(varFile, pvoidContents, count, m_papp);
   }

   bool file_application::put_contents(var varFile, const char * lpcszContents)
   {
      return m_papp->m_psystem->m_spfile->put_contents(varFile, lpcszContents, m_papp);
   }

   bool file_application::put_contents(var varFile, ::ca2::file & file)
   {
      return m_papp->m_psystem->m_spfile->put_contents(varFile, file, m_papp);
   }

   bool file_application::put_contents(var varFile, primitive::memory & mem)
   {
      return m_papp->m_psystem->m_spfile->put_contents(varFile, mem, m_papp);
   }

   bool file_application::put_contents_utf8(var varFile, const char * lpcszContents)
   {
      return m_papp->m_psystem->m_spfile->put_contents_utf8(varFile, lpcszContents, m_papp);
   }

   string file_application::sys_temp(const char * pszName, const char * pszExtension)
   {
      return m_papp->m_psystem->m_spfile->sys_temp(pszName, pszExtension, m_papp);
   }


   ::ca2::filesp file_application::friendly_get_file(var varFile, UINT nOpenFlags)
   {
      try
      {
         return get_file(varFile, nOpenFlags);
      }
      catch(...)
      {
         return NULL;
      }
   }

   ::ca2::filesp file_application::get_file(var varFile, UINT nOpenFlags)
   {

      ::ca2::filesp spfile;

      string strPath;

      if(varFile.get_type() == var::type_string)
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

      if(varFile.get_type() == var::type_propset && varFile.propset()["file"].ca2 < ::ca2::file >() != NULL)
      {

         spfile = varFile.propset()["file"].ca2 < ::ca2::file >();

      }
      else if(::ca2::str::find_ci(".zip:", strPath) >= 0)
      {

         zip::InFile * pinfile = new zip::InFile(get_app());

         if(pinfile != NULL)
         {

            if(!pinfile->unzip_open(strPath, 0))
            {

               delete pinfile;

               pinfile = NULL;

            }

         }

         spfile = pinfile;

      }
      else if(::ca2::str::begins(strPath, "http://") || ::ca2::str::begins(strPath, "https://"))
      {

         ::url_domain domain;

         domain.create(System.url().get_server(strPath));

         if(domain.m_strRadix == "ca2" && ::ca2::str::begins(System.url().get_object(strPath), "/matter/"))
         {

            string strFile(strPath);

            string strFileDownloading(strPath);
            
            if(::ca2::str::ends(strPath, "en_us_international.xml"))
            {
               TRACE("Debug Here");
            }

            if(::ca2::str::ends(strPath, "text_select.xml"))
            {
               TRACE("Debug Here");
            }

            if(::ca2::str::ends(strPath, "arialuni.ttf"))
            {
               TRACE("Debug Here : arialuni.ttf");
            }

#ifdef WINDOWS
            strFile.replace("://", "_\\");
#else
             strFile.replace("://", "_/");
#endif
            strFile = System.dir().appdata("cache/" + strFile);
            
            strFile = strFile + ".local_copy";

            strFileDownloading = strFile + ".downloading";

            if(m_papp->m_pappThis->m_file.exists(strFile) && !m_papp->m_pappThis->m_file.exists(strFileDownloading))
            {

               spfile.create(allocer());

               try
               {

                  if(spfile->open(strFile, nOpenFlags))
                  {
                     TRACE("from_exist_cache:\"" + strPath + "\"");
                     return spfile;

                  }
               }
               catch(...)
               {

               }

               try
               {

                  spfile.release();

               }
               catch(...)
               {
               }

            }


            var varQuery;

            varQuery["disable_ca2_sessid"] = true;

            if(m_papp->m_pappThis->m_file.exists(strFileDownloading) || m_papp->m_pappThis->m_http.exists(strPath, &varQuery))
            {

               spfile = new sockets::http::file(get_app());

               if(!spfile->open(strPath, nOpenFlags))
               {

                  spfile.release();

               }
               else if(!m_papp->m_pappThis->m_file.exists(strFileDownloading))
               {
                  
                  try
                  {

                     System.file().output(m_papp, strFile, &System.compress(), &::ca2::compress::null, *spfile.m_p);

                  }
                  catch(...)
                  {
                  }


                  spfile->seek_to_begin();

               }

            }


         }
         else
         {

            spfile = new sockets::http::file(get_app());

            if(!spfile->open(strPath, nOpenFlags))
            {

               spfile.release();

            }

         }

      }
      else if(::ca2::str::begins(strPath, "ifs://") || ::ca2::str::begins(strPath, "uifs://"))
      {

         if(&AppUser(m_papp) == NULL)
         {

            spfile = NULL;

         }
         else
         {

            spfile = AppUser(m_papp).m_pifs->get_file(varFile, nOpenFlags);

         }

      }
      else if(::ca2::str::begins(strPath, "fs://"))
      {

         if(&Session == NULL)
         {

            spfile = NULL;

         }
         else
         {

            spfile = Session.m_prfs->get_file(varFile, nOpenFlags);

         }

      }
      else if(::ca2::str::begins_eat_ci(strPath, "matter://"))
      {

         sp(::ca2::application) papp = NULL;

         if(System.url().get_server("matter://" + strPath) == m_papp->m_pappThis->m_strAppName)
         {

            strPath = System.url().get_object("matter://" + strPath).Mid(1);

            spfile.create(m_papp);

            if(!spfile->open(App(m_papp).dir().matter(strPath), nOpenFlags))
            {

               spfile.release();

            }

         }
         else if(&Session != NULL && Session.m_mapApplication.Lookup(System.url().get_server("matter://" + strPath), papp) && App(m_papp).m_strAppName.has_char())
         {

            spfile = App(papp).file().get_file("matter://" + strPath, nOpenFlags);

         }
         else
         {

            spfile = get_file(App(m_papp).dir().matter(strPath), nOpenFlags);

         }

      }
      else
      {

         if(strPath.is_empty())
         {
            TRACE("plane::file_application::get_file file with empty name!!");
            return spfile;
         }

         if((nOpenFlags & ::ca2::file::mode_create) == 0 && !exists(strPath))
         {
            TRACE("plane::file_application::file does not exist!!");
            return spfile;
         }

         spfile.create(allocer());

         if(!spfile->open(strPath, nOpenFlags))
         {

            spfile.release();

         }

      }

      if(spfile.is_null())
      {

         throw ::ca2::file_exception(m_papp, ::ca2::file_exception::none, -1, strPath);

      }

      return spfile;

   }

   ::ca2::byte_stream file_application::get_byte_stream(var varFile, UINT nOpenFlags)
   {

      return ::ca2::byte_stream(get_file(varFile, nOpenFlags));

   }




} // namespace ca2









