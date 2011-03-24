#include "StdAfx.h"


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
         }
         return System.http().get(handler, pszUrl, post, headers, set, pcookies, puser, pszVersion, pestatus);
      }

      void application::get(gen::signal_object * pobj)
      {
         SCAST_PTR(signal, psignal, pobj);
         if(psignal->m_puser == NULL)
         {
            psignal->m_puser = &ApplicationUser;
         }
         System.http().get(pobj);
      }


      bool application::get(const char * pszUrl, primitive::memory & memory, ::fontopus::user * puser)
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
         }
         return System.http().get(pszUrl, str, post, headers, set, pcookies, puser, pszVersion, pestatus);
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
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         return System.http().get(pszUrl, puser);
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


   } // namespace http


} // namespace ca4

