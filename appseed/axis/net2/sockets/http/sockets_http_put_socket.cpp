#include "framework.h"


namespace sockets
{


   http_put_socket::http_put_socket(base_socket_handler& h) : 
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h)
   {

      m_content_length = -1;

   }


   http_put_socket::http_put_socket(base_socket_handler& h,const string & url_in) : 
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h, url_in)
   {

      m_content_length = -1;

   }


   http_put_socket::~http_put_socket()
   {

   }


   void http_put_socket::SetFile(const string & file)
   {

      if(Application.file().exists(file))
      {
         
         m_filename = file;
         
         m_content_length = Application.file().length(file);

      }
      else
      {

         log("SetFile", Errno, StrError(Errno), ::base::log::level_fatal);

         SetCloseAndDelete();

      }

   }


   void http_put_socket::SetContentType(const string & type)
   {
      m_content_type = type;
   }





   void http_put_socket::step()
   {

      if(m_file.is_set())
      {
         m_content_length = (long) m_file->get_length();
      }


      m_request.attr(__id(http_method))    = "PUT";
      m_request.attr(__id(http_version))   = "HTTP/1.1";
      inheader(__id(host))                = GetUrlHost();
      if(m_content_type.has_char())
      {
         outheader(__id(content_type))     = m_content_type;
      }
      inheader(__id(content_length))      = (int64_t) m_content_length;
      inheader(__id(user_agent))          = MyUseragent();
      inheader(__id(connection))          = "close";
      SendRequest();

      if(m_file.is_set())
      {
         size_t n;
         char buf[32768];
         m_file->seek_to_begin();
         while ((n = m_file->read(buf, 32768)) > 0)
         {
            write(buf, n);
         }
      }
      else
      {
         FILE *fil = fopen(m_filename, "rb");
         if (fil)
         {
            size_t n;
            char buf[32768];
            while ((n = fread(buf, 1, 32768, fil)) > 0)
            {
               write(buf, n);
            }
            fclose(fil);
         }
      }
      
   }

}


