#include "framework.h"


namespace http
{


   application::application()
   {
   }

   application::~application()
   {
   }

   property_set & application::process_set(property_set & set, const char * pszUrl)
   {

      if(Application.is_serviceable())
         return set;

      if ((bool)set["raw_http"] || (bool)set["disable_ca2_sessid"]
         || ::str::find_ci("/matter.ca2.cc/", pszUrl) >= 0 || ::str::find_ci("-matter.ca2.cc/", pszUrl) >= 0
         || ::str::find_ci("sessid=noauth", pszUrl)
         || ::str::find_ci("/matter/",System.url().get_query(pszUrl)) == 0
         || set["user"].cast < ::fontopus::user >() != NULL)
         return set;
      
      string strWorkUrl;
         
      if (get_thread() != NULL)
      {

         strWorkUrl = get_thread()->m_strWorkUrl;

      }

      keeper < string > keepWorkUrl(get_thread() == NULL ? &strWorkUrl : &get_thread()->m_strWorkUrl, pszUrl, strWorkUrl, true);

      if ((bool)set["optional_ca2_sessid"])
      {
         if (BaseSession.fontopus()->m_puser != NULL)
            set["user"] = &ApplicationUser;
      }
      else
      {
         set["user"] = &ApplicationUser;
      }
      set["app"] = get_app();

      return set;

   }

   ::sockets::http_client_socket * application::get(::sockets::socket_handler & handler,  const char * pszUrl, property_set & set)
   {
      
      return System.http().get(handler, pszUrl, process_set(set, pszUrl));

   }

   void application::get(signal_details * pobj)
   {
      SCAST_PTR(signal, psignal, pobj);

      ::url_domain domain;

      domain.create(System.url().get_server(psignal->m_strUrl));

      if(domain.m_strRadix == "ca2" && ::str::begins(System.url().get_object(psignal->m_strUrl), "/matter/"))
      {

         string strUrl(psignal->m_strUrl);

         property_set set(get_app());

         single_lock sl(&System.http().m_mutexDownload, true);

         if (!(System.http().m_straDownloading.contains(strUrl)) && !exists(psignal->m_strUrl, set))
         {

            sl.unlock();

            psignal->m_estatusRet = status_fail;

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


   bool application::get(const char * pszUrl, primitive::memory_base & memory, property_set & set)
   {

      set["get_memory"] = &memory;

      bool bOk = System.http().get(pszUrl, process_set(set, pszUrl));

      set.remove_by_name("get_memory");

      return bOk;

   }

   bool application::get(const char * pszUrl, string & str, property_set & set)
   {

      set["get_response"].get_value() = &str;

      return System.http().get(pszUrl, process_set(set, pszUrl));

   }


   string application::get(const char * pszUrl, property_set & set)
   {

      set["get_response"] = "";

      if (!System.http().get(pszUrl, process_set(set, pszUrl)))
         return "";

      return set["get_response"].get_string();

   }

   bool application::exists(const char * pszUrl, property_set & set)
   {

      return exists(pszUrl, NULL, set);

   }


   bool application::exists(const char * pszUrl, var * pvarQuery, property_set & set)
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

      if(::str::find_wwci("ca2", System.url().get_server(pszUrl)) >= 0 && System.url().get_object(pszUrl).find_ci("/matter/") >= 0)
      {
         set["raw_http"] = true;
      }

      bool bExists = System.http().exists(strUrl, process_set(set, pszUrl));

      if(bExists)
         strCache = "yes";
      else
         strCache = "no";
      Application.file().put_contents(strFile, strCache);
      return bExists;
   }


   var application::length(const char * pszUrl, property_set & set)
   {

      return length(pszUrl, NULL, set);

   }


   var application::length(const char * pszUrl, var * pvarQuery, property_set & set)
   {

      string strUrl(pszUrl);

      string strFile(strUrl);

      strFile.replace(":", "_");
      strFile.replace("//", "/");
      strFile.replace("?", "%19");
      strFile = System.dir().appdata("cache/" + strFile + ".length_question");

      string strCache = Application.file().as_string(strFile);

      if (strCache.has_char())
      {
         if (strCache == "-1")
         {
            return -1;
         }
         else if (strCache == "no")
         {
            return ::str::to_int64(strCache);
         }
      }

      var len = System.http().length(strUrl, process_set(set, pszUrl));

      if (len.is_empty())
         strCache = "-1";
      else
         strCache = ::str::from(len.int64());

      Application.file().put_contents(strFile, strCache);

      return len;

   }


   bool application::request(const char * pszRequest, const char * pszUrl, property_set & set)
   {
      return System.http().request(pszRequest, pszUrl, process_set(set, pszUrl));
   }


   bool application::download(const char * pszUrl, const char * pszFile, property_set & set)
   {
      return System.http().download(pszUrl, pszFile, process_set(set, pszUrl));
   }

   bool application::put(const char * pszUrl, primitive::memory & memory, property_set & set)
   {

      return System.http().put(pszUrl, memory, process_set(set, pszUrl));
   }

   bool application::put(const char * pszUrl, ::file::buffer_sp  pfile, property_set & set)
   {
      return System.http().put(pszUrl, pfile, process_set(set, pszUrl));
   }



   string application::locale_schema_url(const char * pszUrl, const char * pszLocale, const char * pszSchema)
   {

      string str;

//      int32_t iAttempt = 0;

      string strUrl(pszUrl);

      if (strUrl.find("?") >= 0)
      {

         strUrl += "&";

      }
      else
      {

         strUrl += "?";

      }

      strUrl += "lang=" + string(pszLocale) + "&styl=" + string(pszSchema);

      return strUrl;

   }


   string application::get_locale_schema(const char * pszUrl,const char * pszLocale,const char * pszSchema)
   {

      string strUrl = locale_schema_url(pszUrl, pszLocale, pszSchema);

      string str;

      int iAttempt = 0;

      string strFontopusServer = BaseSession.fontopus()->get_fontopus_server(pszUrl);

      sp(::sockets::http_session) psession = BaseSession.fontopus()->m_mapFontopusSession[strFontopusServer];

      while(true)
      {

         {

            property_set set(get_app());

            set["get_response"] = "";

            psession = System.http().request(psession,strUrl,set);

            if(psession.is_set())
            {

               BaseSession.fontopus()->m_mapFontopusSession.set_at(strFontopusServer,psession);

            }

            str = set["get_response"];

            if(str.has_char())
               return str;

         }

         iAttempt++;

         if(iAttempt > 11)
            return "";

         Sleep(iAttempt * 840);

      }

      return str;

   }


} // namespace http


