#include "StdAfx.h"
#include "netnodeSocket.h"
#include "netnodeScriptManager.h"

netnodeSocket::netnodeSocket(::sockets::socket_handler_base & h) :
   ::ca::ca(h.get_app()),
   socket(h),
   stream_socket(h),
   tcp_socket(h),
   httpd_socket(h)
{
   /*m_strHead += "HTTP/1.1 200 OK\n";
   m_strHead += "Server: netnode/1.0 (Windows)\n";
   m_strHead += "Accept-Ranges: bytes\n";
   m_strHead += "Date: Mon, 23 May 2005 22:38:34 GMT\n";
   m_strHead += "Server: netnode/1.0 (Windows)\n";
   m_strHead += "Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT\n";
   //m_memfileSend += "Etag: "3f80f-1b6-3e1cb03b"";
   m_strHead += "Accept-Ranges: bytes\n";
   // m_memfileSend += "Content-Length: 438";
   //m_strHead += "Connection: close\n";*/

/*   m_memfileBody << "<html>\n";
   m_memfileBody << "<head>\n";
   m_memfileBody << "</head>\n";
   m_memfileBody << "<body>\n";
   m_memfileBody << "<h1>Ti Amo Carlos Gustavo Cecyn Lundgren de 15 de novembro de 1984!</h1>\n";
   m_memfileBody << "<h1>Assinado Camilo Sasuke Tsumanuma de 2 de abril de 1977!</h1>\n";
   m_memfileBody << "</body>\n";
   m_memfileBody.Truncate(0);*/
}

netnodeSocket::~netnodeSocket(void)
{
}


void netnodeSocket::send_response()
{

   if(gen::str::begins(inattr("request_uri"), "/passthrough/"))
   {
      outheader("Cache-control") = "public";
      outheader("Pragma") = "public";
      int iPathCount;
      outheader("Expires") = System.http().gmdate(System.datetime().strtotime(NULL, "+1 day", 0, iPathCount));
      simple_file_server(System.dir().ca2("img\\net\\ds\\common"));
   }
   else
   {

      http::response res(get_app());

      string strUri(inattr("request_uri"));
      string strHost(inheader("host"));
      string strScript = System.url().object_get_script(strUri);
      if(strUri.find("thesecret") >= 0)
      {
   //      AfxDebugBreak();
      }
      if(strHost == "ca2.am")
      {
         DWORD dw = ::GetTickCount();
       //  AfxDebugBreak();
      }
      if(strScript == "songs")
      {
         DWORD dw = ::GetTickCount();
      }
      if(strScript == "ca2netnodebergedge")
      {
         bergedge::bergedge * pbergedge = System.get_bergedge(0);
         ::bergedge::document * pdoc = pbergedge->get_document(); 
         ::view * pview = pdoc->get_view(0);
         pview->GetParentFrame()->ShowWindow(SW_RESTORE);
         return;
      }
      script_manager().handle(this);
   }
   if(!outheaders().has_property("content-type") && response().file().get_size() > 0)
   {
        outheader("Content-Type") = "text/html; charset=UTF-8";
   }
   int iStatusCode;
   string strStatus;
   if(outattr("http_status_code").is_new()
   || outattr("http_status").is_new())
   {
      if(outheader("location").is_set())
      {
         iStatusCode = 303; // 303 (See Other Location)
         strStatus = "See Other";
      }
      else 
      {
         iStatusCode = 200;
         strStatus = "OK";
      }
      outattr("http_status_code") = iStatusCode;
      outattr("http_status") = strStatus;
   }
   outattr("http_version") = "HTTP/1.1";
   Respond();
}



netnodeScriptManager & netnodeSocket::script_manager()
{
   return *Application.get_script_manager();
}


void netnodeSocket::OnExecute()
{
   send_response();
}

void netnodeSocket::OnResponseComplete()
{
}


bool netnodeSocket::http_filter_response_header(string & strKey, string & strValue)
{
   if(strKey.CompareNoCase("Location") == 0)
   {
      url_domain domain;
      domain.create(System.url().get_server(strValue));
      if(domain.m_strRadix == "ca2open")
      {
         if(System.url().locale_is_south_america(m_strLocale))
         {
            strValue = "https://amdesur.fontopus.com" + System.url().get_object(strValue);
         }
         else if(System.url().locale_is_eu(m_strLocale))
         {
            strValue = "https://eu.fontopus.com" + System.url().get_object(strValue);
         }
         else if(System.url().locale_is_asia(m_strLocale))
         {
            strValue = "https://asia.fontopus.com" + System.url().get_object(strValue);
         }
         else
         {
            strValue = "https://fontopus.com" + System.url().get_object(strValue);
         }
      }
   }
   strValue.trim();
   if(strValue.is_empty())
      return false;
   return true;
}

void netnodeSocket::OnSSLAccept()
{
   m_strCat = System.db().data_load("netnodec", GetSockAddress(), ::database::id());  
   ::sockets::httpd_socket::OnSSLAccept();
}

void netnodeSocket::simple_file_server(const char * psz, const char * pszRelative)
{
   string strExtension = System.file().extension(inattr("request_uri"));
   string str = strExtension;
   str.make_lower();
   if(str == "mp3")
   {
      outheader("Content-Type") = "audio/mpeg";
   }
   else if(str == "exe")
   {
      outheader("Content-Type") = "application/x-msdownload";
   }
   else if(str == "mid")
   {
      outheader("Content-Type") = "audio/midi";
   }
   else if(str == "js")
   {
      outheader("Content-Type") = "text/javascript";
   }
   else if(str == "xpi")
   {
      outheader("Content-Type") = "application/x-xpinstall";
   }
   else if(str == "ttf")
   {
      outheader("Content-Type") = "font/ttf";
   }
   else if(str == "ogv")
   {
      outheader("Content-type") = "video/ogg";
   }
   array_ptr_alloc < int_array > rangea;
   if(strlen(inheader("range")) > 0)
   {
      stringa straItem;
      straItem.explode("=", inheader("range"));
      if(straItem.get_count() == 2)
      {
         string strUnit = straItem[0];
         stringa stra;
         stra.explode(",", straItem[1]);
         for(int i = 0; i < stra.get_count(); i++)
         {
            stringa straRange;
            straRange.explode("-", stra[i]);
            if(straRange.get_count() == 2)
            {
               rangea.add(int_array());
               rangea.last_element().add(atoi(straRange[0]));
               straRange[1].trim();
               if(strlen(straRange[1]) == 0)
                  rangea.last_element().add(-1);
               else
                  rangea.last_element().add(atoi(straRange[1]));
            }
         }
      }
   }
   string strRelative;
   if(pszRelative != NULL)
   {
      strRelative = string(pszRelative);
   }
   else
   {
      strRelative = System.url().url_decode(inattr("request_uri"));
   }
   string strPath;
   strPath = System.dir().path(psz, strRelative);
   read_file(strPath, &rangea);
}


bool netnodeSocket::read_file(const char * lpcsz, array_ptr_alloc < int_array > * prangea)
{
   ex1::filesp spfile(get_app());
   if(!spfile->open(lpcsz, ::ex1::file::type_binary | ::ex1::file::mode_read | ::ex1::file::shareDenyNone))
   {
      return false;
   }
   if(prangea == NULL || prangea->get_count() == 0)
   {
      response().file() << spfile;
   }
   else
   {
      int iLen = System.file().length(lpcsz);
      if(prangea->get_count() > 1)
      {
         UINT uiTotal = 0;
         primitive::memory mem;
         mem.allocate(128 * 1024 * 1024);
         for(int i = 0; i < prangea->get_count(); i++)
         {
            int iStart = prangea->element_at(i)[0];
            int iEnd = prangea->element_at(i)[1];
            if(iStart >= iLen)
               continue;
            // iEnd > iLen is not verified because file may be growing
            spfile->seek(iStart, ex1::seek_begin);
            UINT uiRead;
            gen::memory_file memfile(get_app());
            int iPos = iStart;
            if(iEnd >= iStart)
            {
            }
            else if(iStart > 0)
            {
               iEnd = iLen - 1;
            }
            else
            {
               continue;
            }
            response().file() << "--THIS_STRING_SEPARATES\r\n\r\n";
            response().file() << "Content-range: bytes " + gen::str::itoa(iStart) + "-" + gen::str::itoa(iEnd) + "/" + gen::str::itoa(iLen) + "\r\n";
            response().file() << "Content-Transfer-Encoding: base64";
            response().file() << "\r\n";
            while(true)
            {
               if(iEnd >= iStart)
               {
                  uiRead = min(mem.GetStorageSize(), iEnd - iPos + 1);
               }
               else
               {
                  uiRead = mem.GetStorageSize();
               }
               uiRead = spfile->read(mem.GetAllocation(), uiRead);
               uiTotal += uiRead;
               if(uiRead == 0)
                  break;
               memfile.write(mem.GetAllocation(), uiRead);
               iPos += uiRead;
               if(iPos >= spfile->get_length())
                  break;
            }
            response().file() << System.base64().encode(*memfile.get_memory());
         }
         response().file() << "--THIS_STRING_SEPARATES--\r\n\r\n";
         outheader("Content-type") = "multipart/x-byteranges; boundary=THIS_STRING_SEPARATES";
      }
      else
      {
         UINT uiTotal = 0;
         primitive::memory mem;
         mem.allocate(128 * 1024 * 1024);
         int iStart = prangea->element_at(0)[0];
         int iEnd = prangea->element_at(0)[1];
         if(iStart < iLen)
         {
            // iEnd > iLen is not verified because file may be growing
            spfile->seek(iStart, ex1::seek_begin);
            UINT uiRead;
            gen::memory_file memfile(get_app());
            int iPos = iStart;
            if(iEnd >= iStart)
            {
            }
            else if(iStart > 0)
            {
               iEnd = iLen - 1;
            }
            while(true)
            {
               if(iEnd != -1 && iEnd >= iStart)
               {
                  uiRead = min(mem.GetStorageSize(), iEnd - iPos + 1);
               }
               else
               {
                  uiRead = mem.GetStorageSize();
               }
               uiRead = spfile->read(mem.GetAllocation(), uiRead);
               uiTotal += uiRead;
               if(uiRead == 0)
                  break;
               response().file().write(mem.GetAllocation(), uiRead);
               iPos += uiRead;
               if(iPos >= spfile->get_length())
                  break;
            }
         }
         outattr("http_status_code") = 206;
         outattr("http_status") = "Partial Content";
         if(iEnd == -1)
         {
            outheader("Content-Range") = "bytes " + gen::str::itoa(iStart) + "-" + gen::str::itoa(iEnd) + "/*";
         }
         else
         {
            outheader("Content-Range") = "bytes " + gen::str::itoa(iStart) + "-" + gen::str::itoa(iEnd) + "/" + gen::str::itoa(iLen);
         }
         
      }
      brk1:;
   }
   return true;
}
