#include "framework.h"


namespace sockets
{


   http_debug_socket::http_debug_socket(base_socket_handler& h) : 
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      m_content_length(-1),
      m_read_ptr(0)
   {
   }


   http_debug_socket::~http_debug_socket()
   {
   }


   void http_debug_socket::Init()
   {
      if (get_parent() -> GetPort() == 443)
      {
   #ifdef HAVE_OPENSSL
         EnableSSL();
   #else
         log("url_this", -1, "SSL not available", ::axis::log::level_warning);
   #endif
      }
   }


   void http_debug_socket::OnFirst()
   {
      write(
         "HTTP/1.1 200 OK\n"
         "Content-type: text/html\n"
         "Connection: close\n"
         "Server: http_debug_socket/1.0\n"
         "\n");
      write(
         "<html><head><title>Echo Request</title></head>"
         "<body><h3>Request header</h3>");
      write(   "<form method='post' action='/test_post'>"
         "<input type='text' name='text' value='test text'><br>"
         "<input type='submit' name='submit' value=' OK '></form>");
      write(   "<pre style='background: #e0e0e0'>");
      write(m_request.attr(__id(http_method)).get_string() + " " + m_request.attr(__id(request_uri)) + " " + m_request.attr(__id(http_version)) + "\n");
   }


   void http_debug_socket::OnHeader(id key, const string & value)
   {
      if(key == __id(content_length))
         m_content_length = atoi(value);

      write(key + ": " + value + "\n");
   }


   void http_debug_socket::OnHeaderComplete()
   {
      if (m_content_length || m_content_length != ((size_t)(-1)) || IsChunked())
      {
         write("</pre><h3>Request Body</h3><pre style='background: #e0e0e0'>");
      }
      else
      {
         write("</pre><hr></body></html>");
         SetCloseAndDelete();
      }
   }


   void http_debug_socket::OnData(const char *p,size_t l)
   {
      write(p,l);
      m_read_ptr += (int)l;
      if (m_read_ptr >= m_content_length && m_content_length && m_content_length != ((size_t)(-1)))
      {
         write("</pre><hr></body></html>");
         SetCloseAndDelete();
      }
   }


   void http_debug_socket::OnDataComplete()
   {
      if (!CloseAndDelete())
      {
         write("</pre><hr></body></html>");
         SetCloseAndDelete();
      }
   }


} // namespace sockets


