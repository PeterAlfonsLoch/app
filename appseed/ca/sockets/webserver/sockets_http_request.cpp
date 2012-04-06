#include "StdAfx.h"

namespace http
{

   // --------------------------------------------------------------------------------------
   request::request(::ca::application * papp) :
      ca(papp),
      transaction(papp),
      m_file(papp),
      m_form(papp)
   {
   }


   // --------------------------------------------------------------------------------------
   request::request(const request& src) :
   ::ca::ca(((request&) src).get_app()),
   transaction(src),
   m_null(src.m_null),
   m_file(((request&) src).get_app()),
   m_form(((request&) src).get_app())
   {
      m_file = src.m_file;
   }



   // --------------------------------------------------------------------------------------
   request::~request()
   {
   }






   // --------------------------------------------------------------------------------------
   void request::add_cookie(const char * pszSetCookie)
   {
      m_cookies.add(pszSetCookie);
   }


   // --------------------------------------------------------------------------------------
   void request::InitBody( size_t sz )
   {
      UNREFERENCED_PARAMETER(sz);
      m_file.Truncate(0);
      /*if (!m_file.get())
         m_file = std::auto_ptr<IFile>(new MemFile);
   DEB(   else
         TRACE("Body data file already opened\n");*/
   }


   // --------------------------------------------------------------------------------------
   void request::write( const char *buf, ::primitive::memory_size sz )
   {
         m_file.write(buf, sz);
   }


   // --------------------------------------------------------------------------------------
   void request::CloseBody()
   {
      //m_file.close();
   }


   // --------------------------------------------------------------------------------------
   void request::ParseBody()
   {
      m_form.clear();
      if(attrs().has_property("request_uri"))
      {
         attr("query_string") = System.url().object_get_query(attr("request_uri"));
         string str = attrs()["query_string"];
         m_form.parse_query_string(str, str.get_length());
      }
      m_form.request().merge(m_form.get());
      attr("http_host")       = header("host");
      attr("http_referer")    = header("referer");
      if(attr("http_method").get_string().CompareNoCase("PUT") == 0)
      {
         // skip following POST processing below
         return;
      }
      if(m_file.get_size() > 0)
      {
         m_form.parse_body(&m_file, ContentType(), ContentLength());
      }
      m_form.request().merge(m_form.post());
   }





   // --------------------------------------------------------------------------------------
   void request::clear()
   {
      transaction::clear();
   /*   attr("http_method") = "";
      attr("http_protocol") = "";
      attr("request_uri") = "";
      attr("remote_address") = "";
      attr("remote_host") = "";
      attr("server_name") = "";
      attr("server_port") = 0;
      attr("https") = false;*/

   //   m_file = std::auto_ptr<IFile>(NULL);
      m_form.clear();
      m_cookies.remove_all();
      file().Truncate(0);
   }

} // namespace http

