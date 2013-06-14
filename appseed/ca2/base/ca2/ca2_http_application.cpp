#include "framework.h"


namespace ca2
{


   namespace http
   {


      application::application()
      {
      }

      application::~application()
      {
      }

      ::sockets::http_client_socket * application::get(
         ::sockets::socket_handler & handler, 
         const char * pszUrl, 
         ::ca2::property_set & post, 
         ::ca2::property_set & headers, 
         ::ca2::property_set & set, 
         ::http::cookies * pcookies, 
         ::fontopus::user * puser, 
         const char * pszVersion, 
         http::e_status * pestatus)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
            set["app"] = get_app();
         }
         return System.http().get(handler, pszUrl, post, headers, set, pcookies, puser, pszVersion, pestatus);
      }

      void application::get(::ca2::signal_object * pobj)
      {
         SCAST_PTR(signal, psignal, pobj);

         ::url_domain domain;

         domain.create(System.url().get_server(psignal->m_strUrl));

         if(domain.m_strRadix == "ca2" && ::ca2::str::begins(System.url().get_object(psignal->m_strUrl), "/matter/"))
         {

            if(!exists(psignal->m_strUrl))
            {

               psignal->m_estatusRet = status_failed;

               psignal->m_bRet = false;

               return;

            }

         }
         else if(psignal->m_puser == NULL)
         {
            psignal->m_puser = &ApplicationUser;
            psignal->m_set["app"] = get_app();
         }
         System.http().get(pobj);
      }


      bool application::get(const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         return System.http().get(pszUrl, memory, puser);         
      }

      bool application::get(
         const char * pszUrl,
         string & str, 
         ::ca2::property_set & post, 
         ::ca2::property_set & headers,
         ::ca2::property_set & set, 
         ::http::cookies * pcookies, 
         ::fontopus::user * puser, 
         const char * pszVersion,
         e_status * pestatus)
      {
         if(puser == NULL && !(bool)set["disable_ca2_sessid"])
         {
            if((bool)set["optional_ca2_sessid"])
            {
               if(Application.fontopus()->m_puser != NULL)
                  puser = &ApplicationUser;
            }
            else
            {
               puser = &ApplicationUser;
            }
            set["app"] = get_app();
         }
         return System.http().get(pszUrl, str, post, headers, set, pcookies, puser, pszVersion, pestatus);
      }


      bool application::get(
         const char * pszUrl,
         primitive::memory_base & memory, 
         ::ca2::property_set & post, 
         ::ca2::property_set & headers,
         ::ca2::property_set & set, 
         ::http::cookies * pcookies, 
         ::fontopus::user * puser, 
         const char * pszVersion,
         e_status * pestatus)
      {
         if(puser == NULL && !(bool)set["disable_ca2_sessid"] && !(bool)set["optional_ca2_sessid"])
         {
            puser = &ApplicationUser;
         }
         set["app"] = get_app();
         return System.http().get(pszUrl, memory, post, headers, set, pcookies, puser, pszVersion, pestatus);
      }

      bool application::get(const char * pszUrl, string & str, ::fontopus::user * puser)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         return System.http().get(pszUrl, str, puser);
      }


      string application::get(const char * pszUrl, ::fontopus::user * puser)
      {
         if(puser == NULL && ::ca2::str::find_ci("/matter.ca2.cc/", pszUrl) < 0 && ::ca2::str::find_ci("-matter.ca2.cc/", pszUrl) < 0)
         {
            if(::ca2::get_thread() != NULL)
            {
               keeper < string > keepWorkUrl(&::ca2::get_thread()->m_strWorkUrl, pszUrl, ::ca2::get_thread()->m_strWorkUrl, true);
               puser = &ApplicationUser;
            }
            else
            {
               puser = &ApplicationUser;
            }
         }
         return System.http().get(pszUrl, puser);
      }

      bool application::exists(const char * pszUrl, ::fontopus::user * puser)
      {

         return exists(pszUrl, NULL, puser);

      }


      bool application::exists(const char * pszUrl, var * pvarQuery, ::fontopus::user * puser)
      {

         string strUrl(pszUrl);

         string strFile(strUrl);

         strFile.replace(":", "_");
         strFile.replace("//", "/");
         strFile.replace("?", "%19");
         strFile = System.dir().appdata("cache/" + strFile + ".exists_question");

         string strCache = Application.file().as_string(strFile);

         if(strCache.has_char())
         {
            if(strCache == "yes")
            {
               return true;
            }
            else if(strCache == "no")
            {
               return false;
            }
         }

         if(puser == NULL && !get_app()->is_system() 
         && (!get_app()->is_session() || get_app()->cast_app < ::plane::session > ().m_pfontopus->m_puser != NULL)
         && (pvarQuery == NULL || (!(bool)pvarQuery->operator[]("disable_ca2_sessid") && !(bool)pvarQuery->operator[]("optional_ca2_sessid")))) 
         {
            puser = &ApplicationUser;
         }
  //       set["app"] = get_app();
         bool bExists = System.http().exists(strUrl, puser);

         if(bExists)
            strCache = "yes";
         else
            strCache = "no";
         Application.file().put_contents(strFile, strCache);
         return bExists;
      }



      bool application::request(
         const char * pszRequest,
         const char * pszUrl,
         string & str, 
         ::ca2::property_set & post, 
         ::ca2::property_set & headers,
         ::ca2::property_set & set, 
         ::http::cookies * pcookies, 
         ::fontopus::user * puser, 
         const char * pszVersion,
         e_status * pestatus)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
            set["app"] = get_app();
         }
         return System.http().request(pszRequest, pszUrl, str, post, headers, set, pcookies, puser, pszVersion, pestatus);
      }


      bool application::request(const char * pszRequest, const char * pszUrl, string & str, ::fontopus::user * puser)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         return System.http().request(pszRequest, pszUrl, str, puser);
      }

      string application::request(const char * pszRequest, const char * pszUrl, ::fontopus::user * puser)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         return System.http().request(pszRequest, pszUrl, puser);
      }

      bool application::request(const char * pszRequest, const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         return System.http().request(pszRequest, pszUrl, memory, puser);         
      }

      bool application::download(
         const char * pszUrl,
         const char * pszFile, 
         ::ca2::property_set & post, 
         ::ca2::property_set & headers, 
         ::ca2::property_set & set,
         ::http::cookies * pcookies, 
         ::fontopus::user * puser, 
         const char * pszVersion)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         return System.http().download(pszUrl, pszFile, post, headers, set, pcookies, puser, pszVersion);
      }

      bool application::download(
         const char * pszUrl,
         const char * pszFile, 
         const char * pszPost, 
         ::ca2::property_set & headers,
         ::http::cookies * pcookies,
         ::fontopus::user * puser,
         const char * pszVersion)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         return System.http().download(pszUrl, pszFile, pszPost, headers, pcookies, puser, pszVersion);
      }


      bool application::download(const char * pszUrl, const char * pszFile, ::fontopus::user * puser)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         return System.http().download(pszUrl, pszFile, puser);
      }

      bool application::put(const char * pszUrl, primitive::memory & memory, ::fontopus::user * puser)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         return System.http().put(pszUrl, memory, puser);
      }

      bool application::put(const char * pszUrl, sp(::ca2::file) pfile, ::fontopus::user * puser)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         return System.http().put(pszUrl, pfile, puser);
      }


      bool application::put(string & strResponse, const char * pszUrl, primitive::memory & memory, ::fontopus::user * puser)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         return System.http().put(strResponse, pszUrl, memory, puser);
      }

      bool application::put(string & strResponse, const char * pszUrl, sp(::ca2::file) pfile, ::fontopus::user * puser)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         return System.http().put(strResponse, pszUrl, pfile, puser);
      }



   } // namespace http


} // namespace ca2

