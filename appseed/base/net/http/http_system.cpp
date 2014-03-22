#include "framework.h"


namespace http
{


   system::system(sp(base_application) papp) :
      element(papp),
      m_mutexPac(papp),
      m_mutexProxy(papp),
      m_mutexDownload(papp)
   {
   }

   system::~system()
   {
   }

   int32_t system::auto_config_proxy_count()
   {
      return 4;
   }

   void system::auto_config_proxy(int32_t i)
   {

      return;
      if(i == 0)
      {
      }
      else if(i == 1)
      {
         // telmico: no proxy
         string str = System.file().as_string(System.dir().appdata("machine/proxy.xml"), &System);
         if(str.has_char() && str.find("<") >= 0 && str.find(">") > 0)
         {
            Application.file().copy(System.dir().appdata("proxy_original.xml"), System.dir().element("proxy.xml"), false);
         }
         if(Application.file().exists(System.dir().appdata("proxy.xml")))
         {
            try
            {
               System.file().del(System.dir().appdata("proxy.xml"));
            }
            catch(...)
            {
            }
         }
      }
      else if(i == 2)
      {
         // telmico: original proxy configuration
         if(Application.file().exists(System.dir().appdata("proxy_original.xml")))
         {
            Application.file().copy(System.dir().appdata("proxy.xml"), System.dir().appdata("proxy_original.xml"), false);
         }
      }
      else
      {
         // telmico: simple default proxy configuration : hostname=>proxy - try etc/hosts port=>80  - assume HTTP proxy
         string str = System.file().as_string(System.dir().appdata("proxy.xml"), &System);
         if(str.has_char() && str.find("<") >= 0 && str.find(">") > 0)
         {
            Application.file().copy(System.dir().appdata("proxy_original.xml"), System.dir().appdata("proxy.xml"), false);
         }
         Application.file().put_contents(System.dir().appdata("proxy.xml"), "proxy");
      }
   }

   void system::defer_auto_initialize_proxy_configuration()
   {
      /*
      if(!strcmp(System.get_module_name(), "netnodeapp")
         || !strcmp(System.get_module_name(), "netnodecfgapp")
         || System.get_license_id() == "simpledbcfg"
         || System.get_license_id() == "app-core/netnodelite"
         || System.command()->m_varTopicQuery["app"] == "simpledbcfg")
      {
         return;
      }
      else if(System.command()->m_varTopicQuery["app"] == "mydns"
         || System.command()->m_varTopicQuery.has_property("install")
         || System.command()->m_varTopicQuery.has_property("uninstall"))
      {
         return;
      }
      else if(!strcmp(System.get_module_name(), "productionapp")
         || !strcmp(System.get_module_name(), "productionbasisapp")
         || !strcmp(System.get_module_name(), "backupapp")
         || System.command()->m_varTopicQuery["app"] == "production"
         || System.get_license_id() == "winservice_filesystemsize")
      {
         return;
      }
      */


      string strHost = Application.file().as_string(System.dir().appdata("database\\text\\last_good_known_fontopus_com.txt"));
      stringa straRequestingServer;
      straRequestingServer.add("account.ca2.cc");
      //straRequestingServer.add("eu-account.ca2.cc");
      //straRequestingServer.add("asia-account.ca2.cc");
      if(!straRequestingServer.contains_ci(strHost))
      {
         strHost = "account.ca2.cc";
      }

      straRequestingServer.remove(strHost);
      straRequestingServer.insert_at(0, strHost);

      bool bOk = false;
      /*for(int32_t i = 0; i < straRequestingServer.get_count() && !bOk; i++)
      {
         string strUrl = "https://" + straRequestingServer[i] + "/hello";
         for(int32_t j = 0; j < auto_config_proxy_count(); j++)
         {
            auto_config_proxy(j);
            string str = get(strUrl);
            if(str == "Hello!!")
            {
               bOk = true;
               break;
            }
         }
      }*/

      if(bOk)
         return;

      auto_config_proxy(0);

   }

   system::pac::pac(sp(base_application) papp) :
      element(papp),
      m_js(papp)
   {
   }

   system::pac * system::get_pac(const char * pszUrl)
   {

      single_lock sl(&m_mutexPac, true);

      string_map < pac * >::pair * ppair = m_mapPac.PLookup(pszUrl);

      if(ppair == NULL || (::get_tick_count() - ppair->m_element2->m_dwLastChecked) > (84 * 1000))
      {
         if(ppair != NULL)
         {
            delete ppair->m_element2;
            m_mapPac.remove_key(pszUrl);
         }

         class pac * ppac = new class pac(get_app());

         ppac->m_dwLastChecked = get_tick_count();

         ppac->m_strUrl = pszUrl;

         var varQuery;

         varQuery["disable_ca2_sessid"] = true;
         varQuery["no_proxy_config"] = true;

         ppac->m_strAutoConfigScript = Application.file().as_string(ppac->m_strUrl, varQuery);


         m_mapPac.set_at(pszUrl, ppac);

         if(ppac->m_strAutoConfigScript.is_empty())
         {
            return NULL;
         }

         registerFunctions(&ppac->m_js);
         registerJavascriptFunctions(&ppac->m_js);
         ppac->m_js.execute(ppac->m_strAutoConfigScript);

         ppair = m_mapPac.PLookup(pszUrl);

         if(ppair == NULL)
            return NULL;
      }

      if(ppair->m_element2->m_strAutoConfigScript.is_empty())
         return NULL;

      return ppair->m_element2;

   }


   system::proxy::proxy(sp(base_application) papp) :
      element(papp)
   {
   }



   ::http::system::proxy * system::get_proxy(const char * pszUrl)
   {

      single_lock sl(&m_mutexProxy, true);

      string_map < ::http::system::proxy * >::pair * ppair = m_mapProxy.PLookup(pszUrl);

      if(ppair == NULL || (::get_tick_count() - ppair->m_element2->m_dwLastChecked) > (84 * 1000))
      {
         if(ppair != NULL)
         {
            delete ppair->m_element2;
            m_mapPac.remove_key(pszUrl);
         }

         class ::http::system::proxy * pproxy = new class ::http::system::proxy(get_app());

         pproxy->m_dwLastChecked = get_tick_count();

         pproxy->m_strUrl = pszUrl;

         config_proxy(pszUrl, pproxy);

         m_mapProxy.set_at(pszUrl, pproxy);

         return pproxy;

      }

      return ppair->m_element2;

   }


   bool system::try_pac_script(const char * pszScriptUrl, const char * pszUrl, proxy * pproxy)
   {

      single_lock sl(&m_mutexPac, true);

      string strProxyServer;

      string strUrl(pszScriptUrl);

      if(::str::begins(pszUrl, strUrl))
      {
         pproxy->m_bDirect = true;
         return true;
      }

      class pac * ppac = get_pac(pszScriptUrl);

      if(ppac == NULL)
         return false;

      string strHost;

      strHost = System.url().get_server(pszUrl);
      int32_t port = System.url().get_port(pszUrl);

/*         ipaddr_t l;
      if (!System.net().u2ip(strHost,l))
      {
         return false;
      }*/
      ::net::address ad(strHost, port);

      strHost = ad.get_display_number();

      string var;
      try
      {
         var = ppac->m_js.evaluate("FindProxyForURL('" + string(pszUrl) + "', '" +strHost +"');");
      }
      catch(...)
      {
         return false;
      }

      if(var.CompareNoCase("DIRECT") == 0)
      {
         pproxy->m_bDirect = true;
      }
      else if(::str::begins_eat_ci(var, "PROXY"))
      {
         var.trim();
         stringa stra;
         stra.explode(":", var);
         pproxy->m_bDirect = false;
         pproxy->m_strProxy = stra[0];
         pproxy->m_iPort = stra.get_size() > 1 ? ::atoi(stra[1]) : 80;
      }
      else
      {
         pproxy->m_bDirect = true;
      }

      return true;

   }

   void system::config_proxy(const char * pszUrl, ::sockets::http_tunnel * psocket)
   {

#ifdef METROWIN

      psocket->m_bDirect = true;

#else

      ::http::system::proxy * pproxy = get_proxy(pszUrl);

      if(pproxy == NULL)
         return;

      if(pproxy->m_bDirect)
      {
         psocket->m_bDirect      = true;
      }
      else
      {
         psocket->m_bDirect      = false;
         psocket->m_strProxy     = pproxy->m_strProxy;
         psocket->m_iProxyPort   = pproxy->m_iPort;
      }

#endif

   }


   void system::config_proxy(const char * pszUrl, ::http::system::proxy * pproxy)
   {

      xml::document doc(get_app());
      string str = System.file().as_string(System.dir().appdata("proxy.xml"), &System);
      if(str.has_char() && str.find("<") < 0 && str.find(">") < 0)
      {
         stringa stra;
         stra.explode(":", str);
         if(stra.get_size() > 0 && stra[0].has_char())
         {
            pproxy->m_bDirect = false;
            pproxy->m_strProxy = stra[0];
            if(stra.get_size() >= 2)
            {
               pproxy->m_iPort = atoi(stra[1]);
            }
            else
            {
               pproxy->m_iPort = 80;
            }
            return;
         }
      }
      bool bOk = false;
      if(!doc.load(str))
      {
         pproxy->m_bDirect = true;
      }
      else
      {
         bOk = true;
         string strHost = System.url().get_server(pszUrl);
         int32_t iHostPort = System.url().get_port(pszUrl);
         ::net::address ipHost(strHost, iHostPort);
         for(int32_t iNode = 0; iNode < doc.get_root()->get_children_count(); iNode++)
         {
            sp(::xml::node) pnode = doc.get_root()->child_at(iNode);
            if(pnode->get_name() == "proxy")
            {
               ::net::address ipAddress(pnode->attr("address").get_string(), 0);
               ::net::address ipMask(pnode->attr("mask").get_string(), 0);
               if(ipHost.is_in_same_net(ipAddress, ipMask))
               {
                  if(pnode->attr("server") == "DIRECT")
                  {
                     pproxy->m_bDirect = true;
                     return;
                  }
                  else
                  {
                     pproxy->m_bDirect = false;
                     pproxy->m_strProxy = pnode->attr("server");
                     pproxy->m_iPort = pnode->attr("port");
                     return;
                  }
               }
            }
         }
         if(doc.attr("server") == "DIRECT")
         {
            pproxy->m_bDirect = true;
            return;
         }
         else
         {
            pproxy->m_bDirect = false;
            pproxy->m_strProxy = doc.get_root()->attr("server");
            pproxy->m_iPort = doc.get_root()->attr("port");
            return;
         }
      }

      if(!bOk)
      {

// xxx         bool bAutoDetect = System.os().connection_settings_get_auto_detect();

         bool bAutoDetect = false;

         if(bAutoDetect)
         {
            if(try_pac_script("http://wpad/wpad.dat", pszUrl, pproxy))
               return;
         }

// xxx         string strUrl = System.os().connection_settings_get_auto_config_url();

         string strUrl;

         if(strUrl.has_char())
         {
            if(try_pac_script(strUrl, pszUrl, pproxy))
               return;
         }

         pproxy->m_bDirect = true;
      }

   }

















   ::sockets::http_session * system::open(
                  ::sockets::socket_handler & handler,
                  const char * pszHost,
                  const char * pszProtocol,
                  property_set & set,
                  ::fontopus::user * puser,
                  const char * pszVersion)
   {

      uint32_t dwTimeProfile1 = get_tick_count();

      UNREFERENCED_PARAMETER(pszVersion);
      string strServer = pszHost;
      string strProtocol = pszProtocol;
      sp(base_application) papp = set["app"].cast < application >();
      int32_t iPort;
      if(strProtocol == "https")
      {
         iPort = 443;
      }
      else
      {
         iPort = 80;
      }

      if(pszVersion == NULL || pszVersion[0] == '\0')
      {
         pszVersion = "HTTP/1.1";
      }

      string strUrl(strProtocol + "://" + strServer);

      // Format of script name example "system://server.com/the rain.mp3" => "system://server.com/the%20rain.mp3"
      {
         string strScript = System.url().url_encode(System.url().url_decode(System.url().get_script(strUrl)));
         strScript.replace("+", "%20");
         strScript.replace("%2F", "/");
         strUrl = System.url().set_script(strUrl, strScript);
      }

      property_set setQuery(get_app());

      setQuery.parse_url_query(System.url().get_query(strUrl));



      string strSessId;
      if(!(bool)set["disable_ca2_sessid"] && !setQuery.has_property("authnone"))
      {
         if((bool)set["optional_ca2_sessid"])
         {


            if(papp != NULL)
            {

               string strFontopusServer = Application.fontopus()->get_server(strUrl, 8);

               url_domain domainFontopus;

               domainFontopus.create(strFontopusServer);

               if(domainFontopus.m_strRadix == "ca2")
               {
                  puser = &AppUser(papp);
                  if(puser != NULL && (strSessId = puser->get_sessid(strUrl, !set["interactive_user"].is_new() && (bool)set["interactive_user"])).has_char() &&
                     if_then(set.has_property("optional_ca2_login"), !(bool)set["optional_ca2_login"]))
                  {
                     System.url().string_set(strUrl, "sessid", strSessId);
                  }
               }

            }

         }
         if(puser != NULL && (strSessId = puser->get_sessid(strUrl, !set["interactive_user"].is_new() && (bool)set["interactive_user"])).has_char() &&
            if_then(set.has_property("optional_ca2_login"), !(bool)set["optional_ca2_login"]))
         {
            System.url().string_set(strUrl, "sessid", strSessId);
         }
         else if(if_then(set.has_property("optional_ca2_login"), (bool)set["optional_ca2_login"]))
         {
         }
         else
         {
            System.url().string_set(strUrl, "authnone", 1);
         }
      }

      ::sockets::http_session * psession;


      psession = new ::sockets::http_session(handler, strProtocol, pszHost);

      if(strProtocol == "https")
      {
#ifndef METROWIN
         ::sockets::ssl_client_context * pcontext = set["ssl_client_context"].cast < ::sockets::ssl_client_context > ();
         if(pcontext != NULL)
         {
            psession->m_spsslclientcontext = pcontext;
         }
         else
         {
            if(strSessId.has_char() && strSessId != "not_auth")
            {
               psession->m_strInitSSLClientContext = System.url().get_server(strUrl) + "?sessid=" + strSessId;
            }
         }
#endif
         psession->EnableSSL();
      }
      uint32_t dw1 = ::get_tick_count();
      bool bConfigProxy = !set.has_property("no_proxy_config") || !(bool)set["no_proxy_config"];
      if(!psession->open(bConfigProxy))
      {
/*            if(pestatus != NULL)
         {
            *pestatus = status_failed;
         }*/
         delete psession;
         uint32_t dwTimeProfile2 = get_tick_count();
         TRACE0("Not Opened/Connected Result Total time ::http::system::get(\"" + strUrl.Left(min(255,strUrl.get_length())) + "\")  " + ::str::from(dwTimeProfile2 - dwTimeProfile1));
         return NULL;
      }
      uint32_t dw2 = ::get_tick_count();
      TRACE("system::get open time %d\n", dw2 - dw1);

      return psession;


   }











































   ::sockets::http_session * system::request(::sockets::socket_handler & handler, ::sockets::http_session * psession, const char * pszRequest, property_set & set)
   {

      uint32_t dw1;
      uint32_t dw2;
      bool bSeemsOk;

      int32_t iTry = 0;

retry:

      iTry++;

      bSeemsOk = true;

      try
      {

         if(psession == NULL || !psession->is_valid())
         {

            bSeemsOk = false;

         }

      }
      catch(...)
      {

         bSeemsOk = false;

      }

      if(!bSeemsOk)
      {
         try
         {
            psession = open(handler, System.url().get_server(pszRequest), System.url().get_protocol(pszRequest), set, set["user"].cast < ::fontopus::user > (), set["http_protocol_version"]);
            if(psession == NULL)
               return NULL;
         }
         catch(...)
         {
            return NULL;
         }
      }


      try
      {

         uint32_t dwTimeProfile1 = get_tick_count();

         sp(base_application) papp = handler.get_app();


         string strRequest = System.url().get_object(pszRequest);





         string strUrl = psession->m_strProtocol + "://" + psession->m_strHost + strRequest;



      // Format of script name example "system://server.com/the rain.mp3" => "system://server.com/the%20rain.mp3"
      {
         string strScript = System.url().url_encode(System.url().url_decode(System.url().get_script(strUrl)));
         strScript.replace("+", "%20");
         strScript.replace("%2F", "/");
         strUrl = System.url().set_script(strUrl, strScript);
      }



      property_set setQuery(get_app());

      setQuery.parse_url_query(System.url().get_query(strUrl));



      string strSessId;
      if(!(bool)set["disable_ca2_sessid"] && !setQuery.has_property("authnone"))
      {
         if((bool)set["optional_ca2_sessid"])
         {


            if(papp != NULL)
            {

               string strFontopusServer = Application.fontopus()->get_server(strUrl, 8);

               url_domain domainFontopus;

               domainFontopus.create(strFontopusServer);

               if(domainFontopus.m_strRadix == "ca2")
               {
                  set["user"] = &AppUser(papp);
                  if (set["user"].cast < ::fontopus::user >() != NULL && (strSessId = set["user"].cast < ::fontopus::user >()->get_sessid(strUrl, !set["interactive_user"].is_new() &&
                     (bool)set["interactive_user"])).has_char() &&
                     if_then(set.has_property("optional_ca2_login"), !(bool)set["optional_ca2_login"]))
                  {
                     System.url().string_set(strUrl, "sessid", strSessId);
                  }
               }

            }

         }
         if (set["user"].cast < ::fontopus::user >() != NULL && 
            (strSessId = set["user"].cast < ::fontopus::user >()->get_sessid(strUrl, !set["interactive_user"].is_new() && (bool)set["interactive_user"])).has_char() &&
            if_then(set.has_property("optional_ca2_login"), !(bool)set["optional_ca2_login"]))
         {
            System.url().string_set(strUrl, "sessid", strSessId);
         }
         else if(if_then(set.has_property("optional_ca2_login"), (bool)set["optional_ca2_login"]))
         {
         }
         else
         {
            System.url().string_set(strUrl, "authnone", 1);
         }
      }

      strRequest = System.url().get_object(strUrl);

         psession->inheaders().clear();
         psession->outheaders().clear();
         psession->inattrs().clear();
         psession->outattrs().clear();
         psession->m_memoryfile.Truncate(0);


         psession->inheaders().add(set["headers"]);
         if(set.has_property("minimal_headers") && (bool)set["minimal_headers"])
         {
            psession->m_request.attrs()["minimal_headers"] = true;
         }
         if(set.has_property("file"))
         {
            psession->m_pfile = set["file"].cast < ::file::binary_buffer >();
         }
         if (set["cookies"].cast < ::http::cookies >() != NULL && set["cookies"].cast < ::http::cookies >()->get_size() > 0)
         {
            psession->request().header(__id(cookie)) = set["cookies"].cast < ::http::cookies >()->get_cookie_header();
         }
         if (set["user"].cast < ::fontopus::user >() != NULL && set["user"].cast < ::fontopus::user >()->m_phttpcookies != NULL && !(bool)set["disable_ca2_user_cookies"])
         {
            psession->request().header(__id(cookie)) = set["user"].cast < ::fontopus::user >()->m_phttpcookies->get_cookie_header();
         }
         if(set.has_property(__id(cookie)) && set[__id(cookie)].get_string().has_char())
         {
            psession->request().header(__id(cookie)) = set[__id(cookie)];
         }

         bool bPost;
         bool bPut;
         if (set["put"].cast < ::file::binary_buffer >() != NULL || set.lookup(__id(http_method)) == "PUT")
         {
            bPost = false;
            bPut = true;
            psession->request("PUT", strRequest);
            dynamic_cast < ::sockets::http_put_socket * > (psession)->m_file = set["put"].cast < ::file::binary_buffer >();
         }
         else if (set["post"].propset().m_propertya.get_count() > 0 || set.lookup(__id(http_method)) == "POST")
         {
            bPost = true;
            bPut = false;
            psession->request("POST", strRequest);
            dynamic_cast < ::sockets::http_post_socket * > (psession)->m_fields = set["post"].propset();
         }
         else
         {
            bPost = false;
            bPut = false;
            psession->request("GET", strRequest);
         }


         handler.add(psession);

         int32_t iIteration = 0;
         ::core::live_signal keeplive;

         if(papp != NULL)
         {
            keeplive.keep(papp);
            keeplive.keep(&Sess(papp));
            keeplive.keep(&Sys(papp));
         }
         oprop("dw").get_value().set_type(var::type_uint32);
         dw1 = oprop("dw");
         dw2 = ::get_tick_count();

         TRACE("intertime system::request time(%d) = %d, %d, %d\n", iIteration, dw1, dw2, dw2 - dw1);

         while(handler.get_count() > 0 && !psession->m_bRequestComplete)
         {
            dw1 = ::get_tick_count();
            handler.select(240, 0);
            keeplive.keep_alive();
            if(psession->m_estatus == ::sockets::socket::status_connection_timed_out)
            {
               break;
            }
            if(set["file_out"].cast < ::file::timeout_buffer >() != NULL)
            {
               if(psession->m_iFinalSize != -1 && set["file_out"].cast < ::file::timeout_buffer >()->m_uiExpectedSize != psession->m_iFinalSize)
               {
                  set["file_out"].cast < ::file::timeout_buffer >()->m_uiExpectedSize = psession->m_iFinalSize;
               }
            }
            dw2 = ::get_tick_count();
            TRACE("system::request time(%d) = %d, %d, %d\n", iIteration, dw1, dw2, dw2 - dw1);
            iIteration++;
         }

         if(set["file_out"].cast < ::file::timeout_buffer >() != NULL)
         {
            if(psession->m_iFinalSize != -1 && set["file_out"].cast < ::file::timeout_buffer >()->m_uiExpectedSize != psession->m_iFinalSize)
            {
               set["file_out"].cast < ::file::timeout_buffer >()->m_uiExpectedSize = psession->m_iFinalSize;
            }
         }

         keeplive.keep_alive();

         oprop("dw") = ::get_tick_count();


         
         set["get_headers"] = psession->outheaders();

//            string strSessId;

#ifdef BSD_STYLE_SOCKETS

         if(psession->IsSSL())
         {
            strSessId = psession->m_response.m_cookies["sessid"];
            if(strSessId.has_char())
            {
               System.sockets().m_clientcontextmap[System.url().get_server(strUrl) + "?sessid=" + strSessId] = psession->m_spsslclientcontext;
            }
         }

#endif

         string strCookie = psession->response().cookies().get_cookie_header();
         set[__id(cookie)] = strCookie;

         int32_t iStatusCode = psession->outattr("http_status_code");

         if(iStatusCode != 200)
         {
            if(iTry < 8)
            {
               goto retry;
            }
         }

         e_status estatus = status_ok;

         if(iStatusCode == 0)
         {
#if defined(BSD_STYLE_SOCKETS)
            if(psession->m_spsslclientcontext.is_set() && psession->m_spsslclientcontext->m_iRetry == 1 && iTry < 8)
            {
               goto retry;
            }
#endif
         }
         if(iStatusCode == 200 || psession->outattr("http_status_code").is_empty())
         {
            estatus = status_ok;
         }
         else if(psession->m_estatus == ::sockets::socket::status_connection_timed_out)
         {
            estatus = status_connection_timed_out;
         }
         else if(iStatusCode >= 300 && iStatusCode <= 399)
         {
            string strCa2Realm = psession->outheader("ca2realm-x");
            if(::str::begins_ci(strCa2Realm, "not licensed: "))
            {
               uint32_t dwTimeProfile2 = get_tick_count();
               TRACE0("Not Licensed Result Total time ::http::system::get(\"" + strUrl.Left(min(255,strUrl.get_length())) + "\") " + ::str::from(dwTimeProfile2 - dwTimeProfile1));
               string strLocation = psession->outheader("Location");
               delete psession;
               throw not_licensed(get_app(), strCa2Realm, strLocation);
               return NULL;
            }
         }
         else
         {
            estatus = status_fail;
         }

         set["get_status"] = (int64_t)estatus;

         uint32_t dwTimeProfile2 = get_tick_count();
         TRACE0("Total time ::http::system::get(\"" + strUrl.Left(min(255,strUrl.get_length())) + "\") " + ::str::from(dwTimeProfile2 - dwTimeProfile1));

      }
      catch(...)
      {
         if(iTry > 8)
            return NULL;
         goto retry;
      }

      if (set.has_property("get_response"))
      {

         set["get_response"] = string((const char *)psession->GetDataPtr(), psession->GetContentLength());

      }

      if (set.has_property("get_memory"))
      {

         ::primitive::memory_base * pbase = set.cast < ::primitive::memory_base >("get_memory");

         if (pbase != NULL)
         {

            pbase->assign(::primitive::memory(psession->GetDataPtr(), psession->GetContentLength()));

         }
         else
         {
          
            set["get_memory"] = canew(::primitive::memory(psession->GetDataPtr(), psession->GetContentLength()));

         }

      }


      return psession;

   }













































































































   ::sockets::http_client_socket * system::get(::sockets::socket_handler & handler, const char * pszUrl, property_set & set)
   {
#ifdef BSD_STYLE_SOCKETS
retry:
#endif

      uint32_t dwTimeProfile1 = get_tick_count();

      string strServer = System.url().get_root(pszUrl);
      string strProtocol = System.url().get_protocol(pszUrl);
      string strObject = System.url().get_object(pszUrl);
      sp(base_application) papp = set["app"].cast < application >();
      int32_t iPort;
      if(strProtocol == "https")
      {
         iPort = 443;
      }
      else
      {
         iPort = 80;
      }


      string strVersion = set["http_protocol_version"];
      if (strVersion.is_empty())
      {
         strVersion = "HTTP/1.1";
      }

      string strUrl(pszUrl);

      // Format of script name example "system://server.com/the rain.mp3" => "system://server.com/the%20rain.mp3"
      {
         string strScript = System.url().url_encode(System.url().url_decode(System.url().get_script(strUrl)));
         strScript.replace("+", "%20");
         strScript.replace("%2F", "/");
         strUrl = System.url().set_script(strUrl, strScript);
      }

      property_set setQuery(get_app());

      setQuery.parse_url_query(System.url().get_query(strUrl));



      string strSessId;
      if ((bool)set["raw_http"])
      {
      }
      else
      {

         if (!(bool)set["disable_ca2_sessid"] && !setQuery.has_property("authnone"))
         {
            if ((bool)set["optional_ca2_sessid"])
            {


               if (papp != NULL)
               {

                  string strFontopusServer = Application.fontopus()->get_server(strUrl, 8);

                  url_domain domainFontopus;

                  domainFontopus.create(strFontopusServer);

                  if (domainFontopus.m_strRadix == "ca2")
                  {
                     set["user"] = &AppUser(papp);
                     if (set["user"].cast < ::fontopus::user >() != NULL && (strSessId = set["user"].cast < ::fontopus::user >()->get_sessid(strUrl, !set["interactive_user"].is_new()
                        && (bool)set["interactive_user"])).has_char() &&
                        if_then(set.has_property("optional_ca2_login"), !(bool)set["optional_ca2_login"]))
                     {
                        System.url().string_set(strUrl, "sessid", strSessId);
                     }
                  }

               }

            }
            else if (set["user"].cast < ::fontopus::user >() != NULL &&
               (strSessId = set["user"].cast < ::fontopus::user >()->get_sessid(strUrl, !set["interactive_user"].is_new() && (bool)set["interactive_user"])).has_char() &&
               if_then(set.has_property("optional_ca2_login"), !(bool)set["optional_ca2_login"]))
            {
               System.url().string_set(strUrl, "sessid", strSessId);
               if (strUrl.find_ci("://api.ca2.cc/") > 0)
               {
                  string strApi(Application.fontopus()->get_server(strUrl, 8));
                  strApi.replace("account", "api");
                  strUrl.replace("://api.ca2.cc/", "://" + strApi + "/");
//                  set["user"].cast < ::fontopus::user >()->set_sessid(set["user"].cast < ::fontopus::user >()->get_sessid(strApi), "api.ca2.cc");
               }
            }
            else if (if_then(set.has_property("optional_ca2_login"), (bool)set["optional_ca2_login"]))
            {
            }
            else
            {
               System.url().string_set(strUrl, "authnone", 1);
            }
         }
         else
         {
            System.url().string_set(strUrl, "authnone", 1);
         }
      }


      ::sockets::http_client_socket * psocket;

      bool bPost;
      bool bPut;
      if (set["put"].cast < ::file::stream_buffer >() != NULL || set.lookup(__id(http_method)) == "PUT")
      {
         bPost = false;
         bPut = true;
         psocket = new ::sockets::http_put_socket(handler, strUrl);
         dynamic_cast < ::sockets::http_put_socket * > (psocket)->m_file = set["put"].cast < ::file::stream_buffer >();
         psocket->m_strMethod = "PUT";
      }
      else if (set["post"].propset().m_propertya.get_count() > 0)
      {
         bPost = true;
         bPut = false;
         psocket = new ::sockets::http_post_socket(handler, strUrl);
         dynamic_cast < ::sockets::http_post_socket * > (psocket)->m_fields = set["post"].propset();
         psocket->m_strMethod = "POST";
      }
      else
      {
         bPost = false;
         bPut = false;
         psocket = new ::http::get_socket(handler, strUrl);
         psocket->m_strMethod = set.lookup(__id(http_method), "GET");
      }


      if (set["http_listener"].cast < ::sockets::http_listener >() != NULL)
      {
         psocket->::sockets::http_socket::m_plistener = set["http_listener"].cast < ::sockets::http_listener >();
      }
      psocket->inheaders().add(set["headers"].propset());
      if (set.has_property("progress_listener"))
      {
         psocket->m_progress.m_plistener = set["progress_listener"].cast < progress_listener >();
      }
      if (set.has_property("int_scalar_source_listener"))
      {
         psocket->::int_scalar_source::m_plistener = set["int_scalar_source_listener"].cast < int_scalar_source::listener >();
      }
      if (set.has_property("minimal_headers") && (bool)set["minimal_headers"])
      {
         psocket->m_request.attrs()["minimal_headers"] = true;
      }
      if(set.has_property("only_headers") && (bool)set["only_headers"])
      {
         psocket->m_bOnlyHeaders = true;
      }
      if(set.has_property("noclose") && !(bool)set["noclose"])
      {
         psocket->m_bNoClose = false;
      }
      if(set.has_property("file"))
      {
         psocket->m_pfile = set["file"].cast < ::file::stream_buffer >();
      }
      if (set["cookies"].cast < ::http::cookies >() != NULL && set["cookies"].cast < ::http::cookies >()->get_size() > 0)
      {
         if (set["cookies"].cast < ::http::cookies >()->find_cookie("sessid") >= 0)
         {
            set["cookies"].cast < ::http::cookies >()->set_cookie("sessid", strSessId);
         }
         psocket->request().header(__id(cookie)) = set["cookies"].cast < ::http::cookies >()->get_cookie_header();
      }
      if (set["user"].cast < ::fontopus::user >() != NULL && set["user"].cast < ::fontopus::user >()->m_phttpcookies != NULL && !(bool)set["disable_ca2_user_cookies"])
      {
         if (set["user"].cast < ::fontopus::user >()->m_phttpcookies->find_cookie("sessid") >= 0)
         {
            set["user"].cast < ::fontopus::user >()->m_phttpcookies->set_cookie("sessid", strSessId);
         }
         psocket->request().header(__id(cookie)) = set["user"].cast < ::fontopus::user >()->m_phttpcookies->get_cookie_header();
      }
      if(set.has_property(__id(cookie)) && set[__id(cookie)].get_string().has_char())
      {
         psocket->request().header(__id(cookie)) = set[__id(cookie)];
      }
      if(!psocket->m_bNoClose)
      {
         psocket->SetCloseOnComplete();
      }
      if(strProtocol == "https")
      {
#ifdef BSD_STYLE_SOCKETS
         ::sockets::ssl_client_context * pcontext = set["ssl_client_context"].cast < ::sockets::ssl_client_context > ();
         if(pcontext != NULL)
         {
            psocket->m_spsslclientcontext = pcontext;
         }
         else
         {
            if(strSessId.has_char() && strSessId != "not_auth")
            {
               psocket->m_strInitSSLClientContext = System.url().get_server(strUrl) + "?sessid=" + strSessId;
            }
         }
#endif
         psocket->EnableSSL();
      }
      uint32_t dw1 = ::get_tick_count();
      bool bConfigProxy = !set.has_property("no_proxy_config") || !(bool)set["no_proxy_config"];
      int32_t iTimeout = set["timeout"];
      if(iTimeout == 0)
         iTimeout = 23;
      else if(iTimeout < 1000)
         iTimeout = 1;
      else
         iTimeout = iTimeout / 1000;


      if(!psocket->open(bConfigProxy))
      {
         set["get_status"] = (int64_t) status_failed;
         delete psocket;
         uint32_t dwTimeProfile2 = get_tick_count();
         TRACE0("Not Opened/Connected Result Total time ::http::system::get(\"" + strUrl.Left(min(255,strUrl.get_length())) + "\")  " + ::str::from(dwTimeProfile2 - dwTimeProfile1));
         return NULL;
      }
      uint32_t dw2 = ::get_tick_count();
      TRACE("system::get open time %d\n", dw2 - dw1);
      handler.add(psocket);

      int32_t iIteration = 0;
      ::core::live_signal keeplive;

      if((bool)set["noloop"])
         return psocket;

      if(papp != NULL)
      {
         keeplive.keep(papp);
         keeplive.keep(&Sess(papp));
         keeplive.keep(&Sys(papp));
      }

      psocket->m_bEnablePool = false;

      ::file::timeout_buffer * ptimeoutbuffer = set["file_out"].cast < ::file::timeout_buffer >();

      while(handler.get_count() > 0)
      {
         dw1 = ::get_tick_count();
         handler.select(iTimeout, 0);
         keeplive.keep_alive();
         if(psocket->m_estatus == ::sockets::socket::status_connection_timed_out)
         {
            break;
         }
         if (ptimeoutbuffer != NULL)
         {
            if (psocket->m_iFinalSize != -1 && ptimeoutbuffer->m_uiExpectedSize != psocket->m_iFinalSize)
            {
               ptimeoutbuffer->m_uiExpectedSize = psocket->m_iFinalSize;
            }
         }
         dw2 = ::get_tick_count();
         TRACE("system::get time(%d) = %d, %d, %d\n", iIteration, dw1, dw2, dw2 - dw1);
         iIteration++;
      }
      keeplive.keep_alive();

      set["get_headers"] = psocket->outheaders();

#ifdef BSD_STYLE_SOCKETS
      if(psocket->IsSSL())
      {
         strSessId = psocket->m_response.m_cookies["sessid"];
         if(strSessId.has_char())
         {
            System.sockets().m_clientcontextmap[System.url().get_server(strUrl) + "?sessid=" + strSessId] = psocket->m_spsslclientcontext;
         }
      }
#endif

      string strCookie = psocket->response().cookies().get_cookie_header();
      set[__id(cookie)] = strCookie;

      e_status estatus = status_fail;

      int32_t iStatusCode = psocket->outattr("http_status_code");
#ifdef BSD_STYLE_SOCKETS
      if(iStatusCode == 0)
      {
         if(psocket->m_spsslclientcontext.is_set() && psocket->m_spsslclientcontext->m_iRetry == 1)
         {
            goto retry;
         }
      }
#endif
      if(iStatusCode == 200 || psocket->outattr("http_status_code").is_empty())
      {
         estatus = status_ok;
      }
      else if(psocket->m_estatus == ::sockets::socket::status_connection_timed_out)
      {
         estatus = status_connection_timed_out;
      }
      else if(iStatusCode >= 300 && iStatusCode <= 399)
      {
         string strCa2Realm = psocket->outheader("ca2realm-x");
         if(::str::begins_ci(strCa2Realm, "not licensed: "))
         {
            uint32_t dwTimeProfile2 = get_tick_count();
            TRACE0("Not Licensed Result Total time ::http::system::get(\"" + strUrl.Left(min(255,strUrl.get_length())) + "\") " + ::str::from(dwTimeProfile2 - dwTimeProfile1));
            string strLocation = psocket->outheader("Location");
            delete psocket;
            throw not_licensed(get_app(), strCa2Realm, strLocation);
            return NULL;
         }
      }
      else
      {
         estatus = status_fail;
      }

      set["get_status"] = (int64_t)estatus;

      if (set["http_listener"].cast < ::sockets::http_listener >() != NULL)
      {

         set["http_listener"].cast < ::sockets::http_listener >()->on_http_complete(psocket, estatus);

      }

      if (set.has_property("get_response"))
      {
         
         set["get_response"] = string((const char *) psocket->GetDataPtr(), psocket->GetContentLength());

      }

      if (set.has_property("get_memory"))
      {

         ::primitive::memory_base * pbase = set.cast < ::primitive::memory_base >("get_memory");

         if (pbase != NULL)
         {

            pbase->assign(::primitive::memory(psocket->GetDataPtr(), psocket->GetContentLength()));

         }
         else
         {

            set["get_memory"] = canew(::primitive::memory(psocket->GetDataPtr(), psocket->GetContentLength()));

         }

      }

      uint32_t dwTimeProfile2 = get_tick_count();
      TRACE0("Total time ::http::system::get(\"" + strUrl.Left(min(255,strUrl.get_length())) + "\") " + ::str::from(dwTimeProfile2 - dwTimeProfile1));

      return psocket;

   }





















   void system::get(signal_details * pobj)
   {
      
      SCAST_PTR(signal, psignal, pobj);
      
      if(psignal == NULL)
      {
         return;
      }

      ::sockets::socket_handler handler(get_app());

      property_set set;

      set = psignal->m_set;

      if (psignal->m_setPost.m_propertya.get_count() > 0)
      {

         set["post"] = psignal->m_setPost;

      }

      if (psignal->m_setHeaders.m_propertya.get_count() > 0)
      {

         set["headers"] = psignal->m_setHeaders;

      }

      if (psignal->m_pcookies != NULL && psignal->m_pcookies->get_count() > 0)
      {

         set["cookies"] = psignal->m_pcookies;

      }

      if (psignal->m_puser != NULL)
      {

         set["user"] = psignal->m_puser;

      }

      if (psignal->m_strVersion.has_char())
      {

         set["http_protocol_version"] = psignal->m_strVersion;

      }


      sp(::sockets::http_client_socket) psocket = get(handler, psignal->m_strUrl, set);

      psignal->m_estatusRet = (::http::e_status) set["get_status"].int64();

      if(psocket == NULL)
      {

         psignal->m_bRet = false;

         return;

      }

      if(psocket->GetDataPtr() != NULL && psocket->GetContentLength() > 0)
      {

         psignal->m_memoryRet.set_data((void *) psocket->GetDataPtr(), psocket->GetContentLength());

      }
      else
      {

         psignal->m_memoryRet.allocate(0);

      }

      psignal->m_setHeaders = psocket->outheaders();

      int32_t iStatusCode = psocket->outattr("http_status_code");

      psignal->m_bRet = iStatusCode == 200;

      return;

   }


   bool system::download(const char * pszUrl, const char * pszFile, property_set & set)
   {
      
      ::sockets::socket_handler handler(get_app());

      ::file::buffer_sp spfile = App(set.cast < base_application >("app", get_app())).file().get_file(pszFile,
         ::file::type_binary | ::file::mode_create | ::file::mode_read_write | ::file::defer_create_directory);

      set["file"] = spfile;

      sp(::sockets::http_client_socket) psocket = get(handler, pszUrl, set);

      set["file"] = NULL;

      if(psocket == NULL)
         return false;


/*      if(spfile.is_null())
      {
         return false;
      }

      spfile->write(psocket->GetDataPtr(), psocket->GetContentLength());*/

      return true;

   }


   bool system::exists(const char * pszUrl, ::property_set & set)
   {

      single_lock sl(&m_mutexDownload, true);

      while (m_straExists.contains(pszUrl))
      {
         sl.unlock();
         Sleep(100);
         sl.lock();
      }

      m_straExists.add(pszUrl);

      sl.unlock();

      ::sockets::socket_handler handler(get_app());

      set["only_headers"] = true;

      ::url_domain domain;

      domain.create(System.url().get_server(pszUrl));

      if (::str::begins(System.url().get_object(pszUrl), "/matter/"))
      {

         set["raw_http"] = true;

      }

      sp(::sockets::http_client_socket) psocket = get(handler, pszUrl, set);

      if (psocket == NULL)
      {
         sl.lock();
         m_straExists.remove(pszUrl);
         return false;
      }

      int32_t iStatusCode = psocket->outattr("http_status_code");

      sl.lock();
      m_straExists.remove(pszUrl);

      return iStatusCode == 200;
   }


   var system::length(const char * pszUrl, ::property_set & set)
   {

      ::sockets::socket_handler handler(get_app());

      set["only_headers"] = true;
      set["minimal_headers"] = true;

      ::url_domain domain;

      domain.create(System.url().get_server(pszUrl));

      if (::str::begins(System.url().get_object(pszUrl), "/matter/"))
      {

         set["disable_ca2_sessid"] = true;

      }

      sp(::sockets::http_client_socket) psocket = get(handler, pszUrl, set);

      if (psocket == NULL)
         return false;

      int32_t iStatusCode = psocket->outattr("http_status_code");

      if (iStatusCode == 200)
      {
         
         return psocket->outheader(__id(content_length));

      }
      else
      {

         return var(var::type_null);

      }
      

   }


   string system::gmdate(time_t t)
   {
      if(t == 0)
         t = time(NULL);

      //time_t t = time((time_t *)&iExpire);
      struct tm tp;
   #ifdef _WIN32
      memcpy(&tp, gmtime(&t), sizeof(tp));
   #else
      gmtime_r(&t, &tp);
   #endif
      const char *days[7] = {"Sunday", "Monday",
         "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
      const char *months[12] = {"Jan", "Feb", "Mar", "Apr", "May",
         "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
      char strDateTime[1024];

      sprintf(strDateTime, "%s, %02d-%s-%04d %02d:%02d:%02d GMT",
         days[tp.tm_wday],
         tp.tm_mday,
         months[tp.tm_mon],
         tp.tm_year + 1900,
         tp.tm_hour,
         tp.tm_min,
         tp.tm_sec);

      return strDateTime;
   }

   void system::set_proxy_auth(::fontopus::user * puser, ::sockets::http_client_socket * psocket)
   {
      string strUserName;
      string strPassword;
      string strUserNameFile;
      string strPasswordFile;
      string strSection;
      strSection.Format("proxy_auth\\%s.%s", puser->m_strLogin.c_str(), "proxy_auth");
      strUserNameFile = System.dir().appdata(strSection + "_1");
      strPasswordFile = System.dir().appdata(strSection + "_2");
      bool bOk = true;
      if(!System.crypto().file_get(strUserNameFile, strUserName, NULL, get_app())
      || strUserName.is_empty())
      {
         bOk = false;
      }
      if(!System.crypto().file_get(strPasswordFile, strPassword, NULL, get_app())
      || strPassword.is_empty())
      {
         bOk = false;
      }
      if(bOk)
      {
         psocket->m_strUserNameFile = strUserNameFile;
         psocket->m_strPasswordFile = strPasswordFile;
      }
      else
      {
         //SPECIFY AUTHENTICATION USERNAME
         if(System.get_auth("system\\::fontopus::user\\proxy_authenticate.xhtml", strUserName, strPassword))
         {
            System.crypto().file_set(strUserNameFile, strUserName, NULL, get_app());
            System.crypto().file_set(strPasswordFile, strPassword, NULL, get_app());
            psocket->m_strUserNameFile = strUserNameFile;
            psocket->m_strPasswordFile = strPasswordFile;
         }
      }
   }

   void system::clean_proxy_auth(::fontopus::user * puser)
   {
      string strSection;
      strSection.Format("proxy_auth\\%s.%s", puser->m_strLogin.c_str() , "proxy_auth");
      System.file().del(System.dir().appdata(strSection + "_1"));
      System.file().del(System.dir().appdata(strSection + "_2"));
   }


   bool system::put(const char * pszUrl, primitive::memory_base & memory, property_set & set)
   {
      
      ::file::memory_buffer file(get_app(), &memory);

      return put(pszUrl, &file, set);

   }


   bool system::put(const char * pszUrl, ::file::buffer_sp  pfile, property_set & set)
   {

      set["put"] = pfile;

      set["noclose"] = false;

      return System.http().get(pszUrl, set);

   }

   bool system::get(const char * pszUrl, property_set & set)
   {

      sockets::socket_handler h(set.cast < base_application >("app", get_app()));

      sp(::sockets::http_client_socket) psocket = System.http().get(h, pszUrl, set);

      return status_succeeded(set["get_status"]);

   }

   bool system::request(const char * pszMethod, const char * pszUrl, property_set & set)
   {

      set[__id(http_method)] = pszMethod;

      return System.http().get(pszUrl, set);

   }



} // namespace http

