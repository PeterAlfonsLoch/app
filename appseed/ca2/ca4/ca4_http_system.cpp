#include "StdAfx.h"


namespace ca4
{


   namespace http
   {


      system::system()
      {
      }

      system::~system()
      {
      }

      int system::auto_config_proxy_count()
      {
         return 4;
      }

      void system::auto_config_proxy(int i)
      {

         return;
         if(i == 0)
         {
         }
         else if(i == 1)
         {
            // telmico: no proxy
            string str = System.file_as_string(&System, System.dir().appdata("machine/proxy.xml"));
            if(str.has_char() && str.find("<") >= 0 && str.find(">") > 0)
            {
               Application.file().copy(System.dir().appdata("proxy_original.xml"), System.dir().ca2("proxy.xml"), false);
            }
            if(System.file().exists(System.dir().appdata("proxy.xml")))
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
            if(System.file().exists(System.dir().appdata("proxy_original.xml")))
            {
               Application.file().copy(System.dir().appdata("proxy.xml"), System.dir().appdata("proxy_original.xml"), false);
            }
         }
         else
         {
            // telmico: simple default proxy configuration : hostname=>proxy - try etc/hosts port=>80  - assume HTTP proxy
            string str = System.file_as_string(&System, System.dir().appdata("proxy.xml"));
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
            || System.get_license_id() == "netnode"
            || System.command().m_varTopicQuery["app"] == "simpledbcfg")
         {
            return;
         }
         else if(System.command().m_varTopicQuery["app"] == "mydns"
            || System.command().m_varTopicQuery.has_property("install")
            || System.command().m_varTopicQuery.has_property("uninstall"))
         {
            return;
         }
         else if(!strcmp(System.get_module_name(), "productionapp")
            || !strcmp(System.get_module_name(), "productionbasisapp")
            || !strcmp(System.get_module_name(), "backupapp")
            || System.command().m_varTopicQuery["app"] == "production"
            || System.get_license_id() == "winservice_filesystemsize")
         {
            return;
         }
         */


         string strHost = Application.file().as_string(System.dir().appdata("database\\text\\last_good_known_fontopus_com.txt"));
         stringa straRequestingServer;
         straRequestingServer.add("fontopus.com");
         straRequestingServer.add("fontopus.eu");
         straRequestingServer.add("fontopus.asia");
         if(!straRequestingServer.contains_ci(strHost))
         {
            strHost = "fontopus.com";
         }

         straRequestingServer.remove(strHost);
         straRequestingServer.insert_at(0, strHost);

         bool bOk = false;
         /*for(int i = 0; i < straRequestingServer.get_count() && !bOk; i++)
         {
            string strUrl = "https://" + straRequestingServer[i] + "/hello";
            for(int j = 0; j < auto_config_proxy_count(); j++)
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

      bool system::try_pac_script(const char * pszScriptUrl, const char * pszUrl, ::sockets::http_tunnel * psocket)
      {

         string strProxyServer;

         string strUrl(pszScriptUrl);


         if(gen::str::begins(pszUrl, strUrl))
         {
            psocket->m_bDirect = true;
            return true;
         }

         var varQuery;

         varQuery["disable_ca2_sessid"] = true;

         string strAutoConfigScript = Application.file().as_string(strUrl, varQuery);

         string strHost;

         strHost = System.url().get_server(pszUrl);
         int port = System.url().get_port(pszUrl);

         ipaddr_t l;
         if (!System.net().u2ip(strHost,l))
         {
            return false;
         }
         sockets::ipv4_address ad(get_app(), l, (port_t) port);
         strHost = ad.Convert(true);

         tinyjs js(get_app());


         string var;
         try
         {
            registerFunctions(&js);
            js.execute(strAutoConfigScript);
            var = js.evaluate("FindProxyForURL('" + string(pszUrl) + "', '" +strHost +"');");
         }
         catch(...)
         {
            return false;
         }

         if(var.CompareNoCase("DIRECT") == 0)
         {
            psocket->m_bDirect = true;
         }
         else if(gen::str::begins_eat_ci(var, "PROXY"))
         {
            var.trim();
            stringa stra;
            stra.explode(":", var);
            psocket->m_bDirect = false;
            psocket->m_strProxy = stra[0];
            psocket->m_iProxyPort = stra.get_size() > 1 ? ::atoi(stra[1]) : 80;
         }
         else
         {
            psocket->m_bDirect = true;
         }

         return true;

      }

      void system::config_proxy(const char * pszUrl, ::sockets::http_tunnel * psocket)
      {

         xml::node node(get_app());
         string str = System.file_as_string(&System, System.dir().appdata("proxy.xml"));
         if(str.has_char() && str.find("<") < 0 && str.find(">") < 0)
         {
            stringa stra;
            stra.explode(":", str);
            if(stra.get_size() > 0 && stra[0].has_char())
            {
               psocket->m_bDirect = false;
               psocket->m_strProxy = stra[0];
               if(stra.get_size() >= 2)
               {
                  psocket->m_iProxyPort = atoi(stra[1]);
               }
               else
               {
                  psocket->m_iProxyPort = 80;
               }
               return;
            }
         }
         bool bOk = false;
         if(!node.load(str))
         {
            psocket->m_bDirect = true;
         }
         else
         {
            bOk = true;
            string strHost = System.url().get_server(pszUrl);
            int iHostPort = System.url().get_port(pszUrl);
               ipaddr_t host;
            if(!System.net().u2ip(strHost,host))
            {
               psocket->m_bDirect = false;
               psocket->m_strProxy = node.attr("server");
               psocket->m_iProxyPort = node.attr("port");
               return;
            }
            ::sockets::ipv4_address ipHost(get_app(), host, (port_t) iHostPort);
            for(int iNode = 0; iNode < node.get_children_count(); iNode++)
            {
               xml::node * pnode = node.child_at(iNode);
               if(pnode->m_strName == "proxy")
               {
                  ipaddr_t addr;
                  if(System.net().u2ip(pnode->attr("address"), addr))
                  {
                     ipaddr_t mask;
                     if(System.net().u2ip(pnode->attr("mask"), mask))
                     {
                        ::sockets::ipv4_address ipAddress(get_app(), addr, 0);
                        ::sockets::ipv4_address ipMask(get_app(), mask, 0);
                        if(ipHost.is_in_net(ipAddress, ipMask))
                        {
                           if(pnode->attr("server") == "DIRECT")
                           {
                              psocket->m_bDirect = true;
                              return;
                           }
                           else
                           {
                              psocket->m_bDirect = false;
                              psocket->m_strProxy = pnode->attr("server");
                              psocket->m_iProxyPort = pnode->attr("port");
                              return;
                           }
                        }
                     }
                  }
               }
            }
            if(node.attr("server") == "DIRECT")
            {
               psocket->m_bDirect = true;
               return;
            }
            else
            {
               psocket->m_bDirect = false;
               psocket->m_strProxy = node.attr("server");
               psocket->m_iProxyPort = node.attr("port");
               return;
            }
         }

         if(!bOk)
         {

            win::registry::Key key1;

            key1.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Connections", false);

            primitive::memory mem;

            key1.QueryValue("DefaultConnectionSettings", mem);

            bool bAutoDetect = (((LPBYTE) mem.get_data())[8] & 0x80) != 0;

            if(bAutoDetect)
            {
               if(try_pac_script("wpad", pszUrl, psocket))
                  return;
            }

            win::registry::Key key;

            key.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", false);

            string strUrl;

            key.QueryValue("AutoConfigURL", strUrl);

            if(strUrl.has_char())
            {
               if(try_pac_script(strUrl, pszUrl, psocket))
                  return;
            }

            psocket->m_bDirect = true;
         }

      }

      ::sockets::http_client_socket * system::get(
                     ::sockets::socket_handler & handler,
                     const char * pszUrl,
                     gen::property_set & post,
                     gen::property_set & headers,
                     gen::property_set & set,
                     ::http::cookies * pcookies,
                     ::fontopus::user * puser,
                     const char * pszVersion,
                     e_status * pestatus)
      {
         retry:
         UNREFERENCED_PARAMETER(pszVersion);
         string strServer = System.url().get_root(pszUrl);
         string strProtocol = System.url().get_protocol(pszUrl);
         string strObject = System.url().get_object(pszUrl);

         int iPort;
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

         string strUrl(pszUrl);

         // Format of script name example "system://server.com/the rain.mp3" => "system://server.com/the%20rain.mp3"
         {
            string strScript = System.url().url_encode(System.url().url_decode(System.url().get_script(strUrl)));
            strScript.replace("+", "%20");
            strScript.replace("%2F", "/");
            strUrl = System.url().set_script(strUrl, strScript);
         }

         string strSessId;
         if(!(bool)set["disable_ca2_sessid"])
         {
            if(puser != NULL && (strSessId = puser->get_sessid(strUrl, !set["interactive_user"].is_new() && (bool)set["interactive_user"])).has_char() &&
               if_then(set.has_property("optional_ca2_login"), !(bool)set["optional_ca2_login"]))
            {
               System.url().set(strUrl, "sessid", strSessId);
            }
            else if(if_then(set.has_property("optional_ca2_login"), (bool)set["optional_ca2_login"]))
            {
            }
            else
            {
               System.url().set(strUrl, "authnone", 1);
            }
         }

         ::sockets::http_client_socket * psocket;

         bool bPost;
         bool bPut;
         if(set["put"].ca2 < ::ex1::file >() != NULL || set["http_request"] == "PUT")
         {
            bPost = false;
            bPut = true;
            psocket = new ::sockets::http_put_socket(handler, strUrl);
            dynamic_cast < ::sockets::http_put_socket * > (psocket)->m_file = set["put"].ca2 < ::ex1::file >();
         }
         else if(post.m_propertya.get_count() > 0 || set["http_request"] == "POST")
         {
            bPost = true;
            bPut = false;
            psocket = new ::sockets::http_post_socket(handler, strUrl);
            dynamic_cast < ::sockets::http_post_socket * > (psocket)->m_fields = post;
         }
         else
         {
            bPost = false;
            bPut = false;
            psocket = new http_get_socket(handler, strUrl);
         }
         psocket->outheaders().add(headers);
         if(set.has_property("minimal_headers") && (bool)set["minimal_headers"])
         {
            psocket->m_request.attrs()["minimal_headers"] = true;
         }
         if(set.has_property("file"))
         {
            psocket->m_pfile = set["file"].ca2 < ::ex1::file >();
         }
         if(pcookies != NULL && pcookies->get_size() > 0)
         {
            psocket->request().header("Cookie") = pcookies->get_cookie_header();
         }
         if(puser != NULL && puser->m_phttpcookies != NULL && !(bool)set["disable_ca2_user_cookies"])
         {
            psocket->request().header("Cookie") = puser->m_phttpcookies->get_cookie_header();
         }
         psocket->SetCloseOnComplete();
         if(strProtocol == "https")
         {
            ::sockets::ssl_client_context * pcontext = set["ssl_client_context"].ca2 < ::sockets::ssl_client_context > ();
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
            psocket->EnableSSL();
         }
         DWORD dw1 = ::GetTickCount();
         if(!psocket->open())
         {
            if(pestatus != NULL)
            {
               *pestatus = status_failed;
            }
            delete psocket;
            return NULL;
         }
         DWORD dw2 = ::GetTickCount();
         TRACE("system::get open time %d\n", dw2 - dw1);
         handler.add(psocket);

         int iIteration = 0;
         ::ca::live_signal keeplive;
         ::ca::application * papp = set["app"].ca2 < ::ca::application >();
         if(papp != NULL)
         {
            keeplive.add(papp);
            keeplive.add(&Berg(papp));
            keeplive.add(&Sys(papp));
         }
         while(handler.get_count() > 0)
         {
            dw1 = ::GetTickCount();
            handler.Select(23, 0);
            keeplive.keep_alive();
            if(psocket->m_estatus == sockets::socket::status_connection_timed_out)
            {
               break;
            }
            if(set["file_out"].ca2 < ::ex1::timeout_file >() != NULL)
            {
               if(psocket->m_content_length != ((size_t) -1) && set["file_out"].ca2 < ::ex1::timeout_file >()->m_uiExpectedSize != psocket->m_content_length)
               {
                  set["file_out"].ca2 < ::ex1::timeout_file >()->m_uiExpectedSize = psocket->m_content_length;
               }
            }
            dw2 = ::GetTickCount();
            TRACE("system::get time(%d) = %d, %d, %d\n", iIteration, dw1, dw2, dw2 - dw1);
            iIteration++;
         }
         keeplive.keep_alive();

         headers = psocket->outheaders();

         if(psocket->IsSSL())
         {
            strSessId = psocket->m_response.m_cookies["sessid"];
            if(strSessId.has_char())
            {
               System.m_clientcontextmap[System.url().get_server(strUrl) + "?sessid=" + strSessId] = psocket->m_spsslclientcontext;
            }
         }

         if(pestatus != NULL)
         {
            int iStatusCode = psocket->outattr("http_status_code");
            if(iStatusCode == 0)
            {
               if(psocket->m_spsslclientcontext.is_set() && psocket->m_spsslclientcontext->m_iRetry == 1)
               {
                  goto retry;
               }
            }
            if(iStatusCode == 200 || psocket->outattr("http_status_code").is_empty())
            {
               *pestatus = status_ok;
            }
            else if(psocket->m_estatus == sockets::socket::status_connection_timed_out)
            {
               *pestatus = status_connection_timed_out;
            }
            else if(iStatusCode >= 300 && iStatusCode <= 399)
            {
               string strCa2Realm = psocket->outheader("ca2realm-x");
               if(gen::str::begins_ci(strCa2Realm, "not licensed: "))
               {
                  string strLocation = psocket->outheader("Location");
                  delete psocket;
                  throw not_licensed(strCa2Realm, strLocation);
                  return NULL;
               }
            }
            else
            {
               *pestatus = status_failed;
            }
         }

         return psocket;

      }

      void system::get(gen::signal_object * pobj)
      {
         SCAST_PTR(signal, psignal, pobj);
         if(psignal == NULL)
         {
            return;
         }
         ::sockets::socket_handler handler(get_app());
         ::sockets::http_client_socket * psocket = get(handler, psignal->m_strUrl, psignal->m_setPost, psignal->m_setHeaders, psignal->operator()(), psignal->m_pcookies, psignal->m_puser, psignal->m_strVersion, &psignal->m_estatusRet);
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
         gen::del(psocket);
         psignal->m_bRet = true;
         return;
      }


      bool system::download(
                     const char * pszUrl,
                     const char * pszFile,
                     gen::property_set & post,
                     gen::property_set & headers,
                     gen::property_set & set,
                     ::http::cookies * pcookies,
                     ::fontopus::user * puser,
                     const char * pszVersion)
      {
         ::sockets::socket_handler handler(get_app());
         ::sockets::http_client_socket * psocket = get(handler, pszUrl, post, headers, set, pcookies, puser, pszVersion);
         if(psocket == NULL)
            return false;

         ex1::filesp spfile(get_app());
         if(!spfile->open(pszFile, ::ex1::file::type_binary | ::ex1::file::mode_create | ::ex1::file::mode_read_write
            | ::ex1::file::defer_create_directory))
         {
            gen::del(psocket);
            return false;
         }
         spfile->write(psocket->GetDataPtr(), psocket->GetContentLength());
         headers = psocket->outheaders();
         gen::del(psocket);
         return true;
      }

      bool system::download(
                     const char * pszUrl,
                     const char * pszFile,
                     const char * pszPost,
                     gen::property_set & headers,
                     ::http::cookies * pcookies,
                     ::fontopus::user * puser,
                     const char * pszVersion)
      {
         gen::property_set post;
         post.parse_url_query(pszPost);
         gen::property_set set;
         if(!download(pszUrl, pszFile, post, headers, set, pcookies, puser, pszVersion))
            return false;
         return true;
      }

      bool system::download(const char * pszUrl, const char * pszFile, ::fontopus::user * puser)
      {
         gen::property_set post;
         gen::property_set headers;
         gen::property_set set;

         if(puser == NULL)
         {
            if(!download(pszUrl, pszFile, post, headers, set))
               return false;
         }
         else
         {
            if(!download(pszUrl, pszFile, post, headers, set, puser->m_phttpcookies, puser))
               return false;
         }

         return true;
      }
      bool system::get(
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
         ::sockets::socket_handler handler(get_app());
         ::sockets::http_client_socket * psocket = get(handler, pszUrl, post, headers, set, pcookies, puser, pszVersion, pestatus);
         if(psocket == NULL)
            return false;
         memory.allocate(psocket->GetContentLength());
         memcpy(memory.get_data(), psocket->GetDataPtr(), memory.get_size());
         headers = psocket->outheaders();
         gen::del(psocket);
         return true;
      }

      bool system::get(
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
         ::sockets::socket_handler handler(get_app());
         ::sockets::http_client_socket * psocket = get(handler, pszUrl, post, headers, set, pcookies, puser, pszVersion, pestatus);
         if(psocket == NULL)
            return false;
         str = string((const char *) psocket->GetDataPtr(), psocket->GetPos() > psocket->GetContentLength()  ? psocket->GetPos() : psocket->GetContentLength());
         headers = psocket->outheaders();
         gen::del(psocket);
         return true;
      }

      bool system::get(const char * pszUrl, primitive::memory_base & storage, ::fontopus::user * puser)
      {
         class signal signal;
         signal.m_strUrl = pszUrl;
         signal.m_puser = puser;
         get(&signal);
         storage = signal.m_memoryRet;
         return signal.m_bRet;
      }


      bool system::get(const char * pszUrl, string & str, ::fontopus::user * puser)
      {
         gen::property_set setPost;
         gen::property_set setHeaders;
         gen::property_set set;
         return get(pszUrl, str, setPost, setHeaders, set, NULL, puser);
      }

      string system::get(const char * pszUrl, ::fontopus::user * puser)
      {
         string str;
         if(!get(pszUrl, str, puser))
            str.Empty();
         return str;
      }

      bool system::request(
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
         ::sockets::socket_handler handler(get_app());
         set["http_request"] = pszRequest;
         ::sockets::http_client_socket * psocket = get(handler, pszUrl, post, headers, set, pcookies, puser, pszVersion, pestatus);
         if(psocket == NULL)
            return false;
         str = string((const char *) psocket->GetDataPtr(), psocket->GetContentLength());
         headers = psocket->outheaders();
         gen::del(psocket);
         return true;
      }

      bool system::request(const char * pszRequest, const char * pszUrl, primitive::memory_base & storage, ::fontopus::user * puser)
      {
         class signal signal;
         signal.m_strUrl = pszUrl;
         signal.m_puser = puser;
         signal.m_set["http_request"] = pszRequest;
         get(&signal);
         storage = signal.m_memoryRet;
         return signal.m_bRet;
      }


      bool system::request(const char * pszRequest, const char * pszUrl, string & str, ::fontopus::user * puser)
      {
         gen::property_set setPost;
         gen::property_set setHeaders;
         gen::property_set set;
         return request(pszRequest, pszUrl, str, setPost, setHeaders, set, NULL, puser);
      }

      string system::request(const char * pszRequest, const char * pszUrl, ::fontopus::user * puser)
      {
         string str;
         if(!request(pszRequest, pszUrl, str, puser))
            str.Empty();
         return str;
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
         string strDateTime;

         strDateTime.Format("%s, %02d-%s-%04d %02d:%02d:%02d GMT",
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
         strSection.Format("proxy_auth\\%s.%s", puser->m_strLogin, "proxy_auth");
         strUserNameFile = System.dir().appdata(strSection + "_1");
         strPasswordFile = System.dir().appdata(strSection + "_2");
         bool bOk = true;
         if(!System.crypt().file_get(strUserNameFile, strUserName, NULL, get_app())
         || strUserName.is_empty())
         {
            bOk = false;
         }
         if(!System.crypt().file_get(strPasswordFile, strPassword, NULL, get_app())
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
               System.crypt().file_set(strUserNameFile, strUserName, NULL, get_app());
               System.crypt().file_set(strPasswordFile, strPassword, NULL, get_app());
               psocket->m_strUserNameFile = strUserNameFile;
               psocket->m_strPasswordFile = strPasswordFile;
            }
         }
      }

      void system::clean_proxy_auth(::fontopus::user * puser)
      {
         string strSection;
         strSection.Format("proxy_auth\\%s.%s", puser->m_strLogin, "proxy_auth");
         System.file().del(System.dir().appdata(strSection + "_1"));
         System.file().del(System.dir().appdata(strSection + "_2"));
      }

      bool system::put(const char * pszUrl, primitive::memory_base & memory, ::fontopus::user * puser)
      {
         gen::memory_file file(get_app(), &memory);
         return put(pszUrl, &file, puser);
      }

      bool system::put(const char * pszUrl, ex1::file * pfile, ::fontopus::user * puser)
      {
         if(puser == NULL)
         {
            puser = &ApplicationUser;
         }
         string str;
         gen::property_set post;
         gen::property_set headers;
         gen::property_set set;
         set["put"] = pfile;
         return System.http().get(pszUrl, str, post, headers, set, NULL, puser);
      }

   } // namespace system


} // namespace ca4

