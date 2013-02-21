#include "framework.h"


namespace ca4
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
         gen::property_set & post, 
         gen::property_set & headers, 
         gen::property_set & set, 
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

      void application::get(gen::signal_object * pobj)
      {
         SCAST_PTR(signal, psignal, pobj);
         if(psignal->m_strUrl.contains("/matter.ca2.cc/") || psignal->m_strUrl.contains("-matter.ca2.cc/"))
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
         gen::property_set & post, 
         gen::property_set & headers,
         gen::property_set & set, 
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
         return System.http().get(pszUrl, str, post, headers, set, pcookies, puser, pszVersion, pestatus);
      }


      bool application::get(
         const char * pszUrl,
         primitive::memory_base & memory, 
         gen::property_set & post, 
         gen::property_set & headers,
         gen::property_set & set, 
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
         if(puser == NULL && gen::str::find_ci("/matter.ca2.cc/", pszUrl) < 0 && gen::str::find_ci("-matter.ca2.cc/", pszUrl) < 0)
         {
            if(::ca::get_thread() != NULL)
            {
               keeper < string > keepWorkUrl(&::ca::get_thread()->m_strWorkUrl, pszUrl, ::ca::get_thread()->m_strWorkUrl, true);
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
//         e_status estatus;
         string strFile(pszUrl);
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
         && (!get_app()->is_session() || dynamic_cast < ::plane::session * > (get_app())->m_pfontopus->m_puser != NULL) 
         && (pvarQuery == NULL || (!(bool)pvarQuery->operator[]("disable_ca2_sessid") && !(bool)pvarQuery->operator[]("optional_ca2_sessid")))) 
         {
            puser = &ApplicationUser;
         }
  //       set["app"] = get_app();
         bool bExists = System.http().exists(pszUrl, puser);

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
         gen::property_set & post, 
         gen::property_set & headers,
         gen::property_set & set, 
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
         gen::property_set & post, 
         gen::property_set & headers, 
         gen::property_set & set,
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
         gen::property_set & headers,
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

      bool application::put(const char * pszUrl, gen::file * pfile, ::fontopus::user * puser)
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

      bool application::put(string & strResponse, const char * pszUrl, gen::file * pfile, ::fontopus::user * puser)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         return System.http().put(strResponse, pszUrl, pfile, puser);
      }



   } // namespace http


} // namespace ca4

