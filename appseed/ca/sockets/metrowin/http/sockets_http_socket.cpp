#include "framework.h"

namespace sockets
{

   http_socket::http_socket(socket_handler_base& h) :
      ::ca::ca(h.get_app()),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      m_request(h.get_app()),
      m_response(h.get_app()),
      m_bFirst(true),
      m_bHeader(true),
      m_bRequest(false),
      m_bResponse(false),
      m_body_size_left(0),
      m_b_http_1_1(false),
      m_b_keepalive(false),
      m_b_chunked(false),
      m_chunk_size(0),
      m_chunk_state(0)
   {
      m_bOnlyHeaders = false;
      m_bNoClose = false;
      m_request.attr("http_version") = "HTTP/1.1";
      SetLineProtocol();
      DisableInputBuffer();
   }


   http_socket::~http_socket()
   {
   }


   void http_socket::OnRawData(char *buf,size_t len)
   {
      if (!m_bHeader)
      {
         if (m_b_chunked)
         {
            size_t ptr = 0;
            while (ptr < len)
            {
               switch (m_chunk_state)
               {
               case 4:
                  while (ptr < len && (m_chunk_line.get_length() < 2 || m_chunk_line.Mid(m_chunk_line.get_length() - 2) != "\r\n"))
                     m_chunk_line += buf[ptr++];
                  if (m_chunk_line.get_length() > 1 && m_chunk_line.Mid(m_chunk_line.get_length() - 2) == "\r\n")
                  {
                     OnDataComplete();
                     // prepare for next request(or response)
                     m_b_chunked = false;
                     SetLineProtocol( true );
                     m_bFirst = true;
                     m_bHeader = true;
                     m_body_size_left = 0;
                     if (len - ptr > 0)
                     {
                        char tmp[TCP_BUFSIZE_READ];
                        memcpy(tmp, buf + ptr, len - ptr);
                        tmp[len - ptr] = 0;
                        OnRead( tmp, len - ptr );
                        ptr = len;
                     }
                  }
                  break;
               case 0:
                  while (ptr < len && (m_chunk_line.get_length() < 2 || m_chunk_line.Mid(m_chunk_line.get_length() - 2) != "\r\n"))
                     m_chunk_line += buf[ptr++];
                  if (m_chunk_line.get_length() > 1 && m_chunk_line.Mid(m_chunk_line.get_length() - 2) == "\r\n")
                  {
                     m_chunk_line = m_chunk_line.Left(m_chunk_line.get_length() - 2);
                     ::ca::parse pa(m_chunk_line, ";");
                     string size_str = pa.getword();
                     m_chunk_size = ::ca::hex::to_uint(size_str);
                     if (!m_chunk_size)
                     {
                        m_chunk_state = 4;
                        m_chunk_line = "";
                     }
                     else
                     {
                        m_chunk_state = 1;
                        m_chunk_line = "";
                     }
                  }
                  break;
               case 1:
                  {
                     size_t left = len - ptr;
                     size_t sz = m_chunk_size < left ? m_chunk_size : left;
                     OnData(buf + ptr, sz);
                     m_chunk_size -= sz;
                     ptr += sz;
                     if (!m_chunk_size)
                     {
                        m_chunk_state = 2;
                     }
                  }
                  break;
               case 2: // skip CR
                  ptr++;
                  m_chunk_state = 3;
                  break;
               case 3: // skip LF
                  ptr++;
                  m_chunk_state = 0;
                  break;
               }
            }
         }
         else
         if (!m_b_keepalive)
         {
            OnData(buf, len);
            /*
               request is HTTP/1.0 _or_ HTTP/1.1 and not keep-alive

               This means we destroy the connection after the response has been delivered,
               hence no need to reset all internal state variables for a new incoming
               request.
            */
            m_body_size_left -= len;
            if (!m_body_size_left)
            {
               OnDataComplete();
            }
         }
         else
         {
            size_t sz = m_body_size_left < len ? m_body_size_left : len;
            OnData(buf, sz);
            m_body_size_left -= sz;
            if (!m_body_size_left)
            {
               OnDataComplete();
               // prepare for next request(or response)
               SetLineProtocol( true );
               m_bFirst = true;
               m_bHeader = true;
               m_body_size_left = 0;
               if (len - sz > 0)
               {
                  char tmp[TCP_BUFSIZE_READ];
                  memcpy(tmp, buf + sz, len - sz);
                  tmp[len - sz] = 0;
                  OnRead( tmp, len - sz );
               }
            }
         }
      }
   }


   void http_socket::OnLine(const string & line)
   {
      if (m_bFirst)
      {
         m_request.lowattr(__str(remote_addr)) = GetRemoteAddress().get_display_number();
         {
#ifdef WINDOWS

            int64_t count;
            int64_t freq;
            if(QueryPerformanceCounter((LARGE_INTEGER *) &count)
            && QueryPerformanceFrequency((LARGE_INTEGER *) &freq))
            {
               m_iFirstTime = count * 1000 * 1000 / freq;
            }
            else
            {
               m_iFirstTime = ::get_tick_count();
            }

#else

            timeval t;
            gettimeofday(&t, NULL);
            m_iFirstTime = t.tv_sec * 1000 * 1000 + t.tv_usec;

#endif

         }
         ::ca::parse pa(line);
         string str = pa.getword();
         if (str.get_length() > 4 &&  ::ca::str::begins_ci(str, "http/")) // response
         {
            m_response.lowattr(__str(http_version)) = str;
            m_response.lowattr(__str(http_status_code)) = pa.getword();
            m_response.lowattr(__str(http_status)) = pa.getrest();
            m_bResponse    = true;
            m_bRequest     = false;
         }
         else // request
         {
            m_request.m_strHttpMethod = str;
            m_request.m_strHttpMethod.make_lower();
            m_request.lowattr(__str(http_method)) = m_request.m_strHttpMethod;
            m_request.lowattr(__str(https)) = IsSSL();
            if(IsSSL())
            {
               m_request.lowattr(__str(http_protocol)) = "https";
            }
            else
            {
               m_request.lowattr(__str(http_protocol)) = "http";
            }
            string strRequestUri = pa.getword();
            string strScript = System.url().get_script(strRequestUri);
            string strQuery = System.url().object_get_query(strRequestUri);
            m_request.m_strRequestUri = System.url().url_decode(strScript) + ::ca::str::has_char(strQuery, "?");
            m_request.lowattr(__str(request_uri)) = m_request.m_strRequestUri;
            m_request.lowattr(__str(http_version)) = pa.getword();
            m_b_http_1_1 = ::ca::str::ends(m_request.lowattr(__str(http_version)), "/1.1");
            m_b_keepalive = m_b_http_1_1;
            m_bRequest     = true;
            m_bResponse    = false;
         }
         m_bFirst = false;
         OnFirst();
         return;
      }
      if (!line.get_length())
      {
         if (m_body_size_left || !m_b_keepalive || m_b_chunked)
         {
            SetLineProtocol(false);
            m_bHeader = false;
         }
         OnHeaderComplete();
         if(!m_body_size_left && !m_b_chunked)
         {
            OnDataComplete();
         }
         return;
      }
      string key;
      string value;
      string lowvalue;
      strsize iFind = line.find(':');
      if(iFind < 0)
      {
         key = line;
      }
      else
      {
         key = line.Left(iFind);
         key.trim();
         iFind++;
         while(isspace((unsigned char) line[iFind]) && iFind < line.get_length())
         {
            iFind++;
         }
         strsize iLen = line.get_length();
         while(iLen >= iFind && isspace((unsigned char ) line[iLen - 1]))
         {
            iLen--;
         }
         value = line.Mid(iFind, iLen - iFind);
         lowvalue = value;
         lowvalue.make_lower();
      }
      key.make_lower();
      OnHeader(key, value, lowvalue);
      if(key == __str(host))
      {
         m_request.m_strHttpHost = lowvalue;
         m_request.lowattr(__str(http_host)) = lowvalue;
      }
      else if(key == __str(content_length))
      {
         m_body_size_left = atol(value);
      }
      else if(key == __str(connection))
      {
         if (m_b_http_1_1)
         {
            if(lowvalue == __str(close))
            {
               m_b_keepalive = false;
            }
            else
            {
               m_b_keepalive = true;
            }
         }
         else
         {
            if(::ca::str::equals_ci(value, "keep-alive"))
            {
               m_b_keepalive = true;
            }
            else
            {
               m_b_keepalive = false;
            }
         }
      }
      if (::ca::str::equals_ci(key, "transfer-encoding") && ::ca::str::ends_ci(value, "chunked"))
      {
         m_b_chunked = true;
      }
      /* If remote end tells us to keep connection alive, and we're operating
      in http/1.1 mode (not http/1.0 mode), then we mark the socket to be
      retained. */
   #ifdef ENABLE_POOL
      if(m_b_keepalive)
      {
         SetRetain();
      }
   #endif
   }

   bool http_socket::http_filter_response_header(string & strKey, string & strValue)
   {
      UNREFERENCED_PARAMETER(strKey);
      UNREFERENCED_PARAMETER(strValue);
      return true;
   }


   void http_socket::SendResponse()
   {
      //TRACE("\n");
      //TRACE("SendResponse\n");
      string msg;
      string strLine;
      strLine = m_response.lowattr(__str(http_version)).get_string() + " " + m_response.lowattr(__str(http_status_code)) + " " + m_response.lowattr(__str(http_status));
      msg = strLine + "\r\n";
      string strHost = m_response.lowheader(__str(host));
      if(strHost.has_char())
      {
         msg += "Host: " + strHost + "\r\n";
         TRACE0("Host: " + strHost  + "\n");
      }


      bool bContentLength = m_response.lowattr(__str(http_status_code)) != 304;

      if(!bContentLength)
         m_response.m_propertysetHeader.remove_by_name("Content-Length");

      for(int i = 0; i < m_response.m_propertysetHeader.m_propertya.get_size(); i++)
      {
         string strKey = m_response.m_propertysetHeader.m_propertya[i].name();
         string strValue = m_response.m_propertysetHeader.m_propertya[i].get_string();
         if(!http_filter_response_header(strKey, strValue))
            continue;
         if(strKey.CompareNoCase("host") == 0)
            continue;
//         strLine = ;
         msg += strKey + ": " + strValue + "\r\n";
         TRACE0(strKey + ": " + strValue +  + "\n");
         //TRACE(strTrace + "\n");
      }

      msg += "\r\n";

      Send( msg );

      if(bContentLength)
      {

         SendResponseBody();

      }

   }

   void http_socket::SendResponseBody()
   {
      if(response().file().get_size() > 0)
      {
         primitive::memory_size iSize = response().file().get_size();
         while(iSize > 0)
         {
            primitive::memory_size iSend = min(iSize, 1024 * 16);
            SendBuf(&((const char *) response().file().get_data())[response().file().get_size() - iSize], iSend);
            iSize -= iSend;
         }
      }
   }




   void http_socket::SendRequest()
   {
      string msg;
      string strLine;
      msg = m_request.attr("http_method").get_string() + " " + m_request.attr("http_protocol") + "://" +  m_request.m_propertysetHeader["host"] +  m_request.attr("request_uri").get_string() + " " + m_request.attr("http_version").get_string() + "\r\n";
/*         msg = m_request.attr("http_method").get_string() + " " + m_request.attr("request_uri").get_string() + " " + m_request.attr("http_version").get_string() + "\r\n";
      }*/
      if(m_request.m_propertysetHeader["host"].get_string().has_char())
      {
         strLine = "Host: " + m_request.m_propertysetHeader["host"];
         msg += strLine + "\r\n";
      }
      for(int i = 0; i < m_request.m_propertysetHeader.m_propertya.get_count(); i++)
      {
         string strKey = m_request.m_propertysetHeader.m_propertya[i].name();
         string strValue = m_request.m_propertysetHeader.m_propertya[i].get_string();
         if(strKey.CompareNoCase("host") == 0)
            continue;
         strValue.trim();
         if(strValue.is_empty())
            continue;
         msg += strKey + ": " + strValue + "\r\n";
      }
      msg += "\r\n";
      Send( msg );
   }


   string http_socket::MyUseragent()
   {
      string version = "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:10.0) Gecko/20100101 veriview/10.0";

      //string version = "Mozilla/5.0 (Windows; U; Windows NT 6.0; pt-BR; rv:1.9.2.13) Gecko/20101203 Firefox/3.6.13";
      //string version = "C++Sockets/";
   #ifdef _VERSION
      version += _VERSION;
   #endif
      return version;
   }


   void http_socket::Reset()
   {
      m_bFirst       = true;
      m_bHeader      = true;
      m_bRequest     = false;
      m_bResponse    = false;
      SetLineProtocol(true);
      m_request.clear();
      m_response.clear();
   }




   void http_socket::url_this(const string & url_in,string & protocol,string & host,port_t& port,string & url,string & file)
   {
      ::ca::parse pa(url_in,"/");
      protocol = pa.getword(); // http
      protocol.trim(":");
      if (!stricmp(protocol, "https"))
      {
   #ifdef HAVE_OPENSSL
         EnableSSL();
   #else
         Handler().LogError(this, "url_this", -1, "SSL not available", ::ca::log::level_warning);
   #endif
         port = 443;
      }
      else
      {
         port = 80;
      }
      host = pa.getword();
      if (strstr(host,":"))
      {
         ::ca::parse pa(host,":");
         pa.getword(host);
         port = static_cast<port_t>(pa.getvalue());
      }
      url = "/" + pa.getrest();
      {
         ::ca::parse pa(url,"/");
/*         index iEnd = url.find("?");
         bool bHasQuery = iEnd > 0;
         if(!bHasQuery)
            iEnd = url.get_length();
         string strScript;
         strScript = System.url().url_encode(url.Mid(1, iEnd - 1));
         string strChar;
         strChar.Format("%%%02X", '_');
         strScript.replace("_", strChar);
         url = "/" + strScript + (bHasQuery ? url.Mid(iEnd + 1) : "");*/
         string tmp = pa.getword();
         while (tmp.get_length())
         {
            file = tmp;
            tmp = pa.getword();
         }
      }
   } // url_this


   void http_socket::OnHeader(const string & key,const string & value, const string & lowalue)
   {
      //http_socket::OnHeader(key, value);
      /*if(key.CompareNoCase("user-agent") == 0)
      {
         TRACE("  (request)OnHeader %s: %s\n", (const char *) key, (const char *) value);
      }*/
      if(key == __str(cookie))
      {
         m_request.cookies().parse_header(value);
         m_response.cookies().parse_header(value);
      }
      else
         m_request.lowheader(key) = value;
   }


   void http_socket::OnHeaderComplete()
   {

      if(IsRequest())
      {
         m_body_size_left = atol(m_request.lowheader(__str(content_length)));
      }
      if(IsResponse())
      {
         m_body_size_left = atol(m_response.lowheader(__str(content_length)));
      }

      if(m_bOnlyHeaders)
      {
         SetCloseAndDelete();
      }



   }


   void http_socket::client_to_server(http_socket * psocket)
   {

      //m_ssl             = psocket->m_ssl;
      m_socket          = psocket->m_socket;
      m_bSsl            = psocket->m_bSsl;
      m_bSslServer      = psocket->m_bSslServer;
      m_bEnableSsl      = psocket->m_bEnableSsl;
      m_bConnected      = psocket->m_bConnected;

      SetRemoteHostname(psocket->GetRemoteHostname());


   }

} // namespace sockets
