#include "framework.h"


namespace http
{


   // --------------------------------------------------------------------------------------
   request::request(sp(::aura::application) papp) :
      element(papp),
      transaction(papp),
      m_memfileBody(papp),
      m_ostream(&m_memfileBody),
      m_form(papp)
   {
   }


   // --------------------------------------------------------------------------------------
   request::request(const request& src) :
   element(((request&) src).get_app()),
   transaction(src),
   m_null(src.m_null),
   m_memfileBody(((request&) src).get_app()),
   m_ostream(&m_memfileBody),
   m_form(((request&) src).get_app())
   {
      m_memfileBody = src.m_memfileBody;
      //m_file = src.m_file;
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
      m_memfileBody.Truncate(0);
      /*if (!m_file.get())
         m_file = smart_pointer<IFile>(new MemFile);
   DEBUG_ONLY(   else
         TRACE("Body data file already opened\n");*/
   }


   // --------------------------------------------------------------------------------------
   void request::write( const char *buf, ::primitive::memory_size sz )
   {
         m_memfileBody.write(buf, sz);
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

      m_strQueryString = System.url().object_get_query(m_strRequestUri);
      attr(__id(query_string)) = m_strQueryString;
      m_form.parse_query_string(m_strQueryString, m_strQueryString.get_length());
      m_form.request()         = m_form.get();
      attr(__id(http_referer)) = header(__id(referer));
      if(m_idHttpMethod == __id(put))
      {
         // skip following POST processing below
         return;
      }
      if(m_memfileBody.get_length() > 0)
      {
         m_form.parse_body(&m_memfileBody, ContentType(), ContentLength());
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

   //   m_file = smart_pointer<IFile>(NULL);
      m_form.clear();
      m_cookies.remove_all();
      file().set_length(0);
   }

} // namespace http

