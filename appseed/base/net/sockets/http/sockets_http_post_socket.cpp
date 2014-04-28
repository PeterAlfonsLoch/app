#include "framework.h"


namespace sockets
{


   http_post_socket::http_post_socket(base_socket_handler& h) :
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h),
      m_fields(h.get_app()),
      m_bMultipart(false)
   {

      m_emethod = http_method_post;

   }


   http_post_socket::http_post_socket(base_socket_handler& h,const string & url_in) :
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h, url_in),
      m_fields(h.get_app()),
      m_bMultipart(false)
   {

      m_emethod = http_method_post;

      single_lock lock(&System.sockets().m_mutexHttpPostBoundary, true);

      m_boundary = "----";
      for (int i = 0; i < 12; i++)
      {
         char c = System.sockets().m_countHttpPostBoundary++ % 128;
         while (!isalnum((unsigned char) c))
            c = System.sockets().m_countHttpPostBoundary++ % 128;
         m_boundary += c;
      }
      m_boundary += "__" + ::str::from(System.sockets().m_countHttpPostBoundary++);
   }


   http_post_socket::~http_post_socket()
   {
   }


   void http_post_socket::AddField(const string & name, const string & value)
   {
      m_fields[name] = value;
   }


   void http_post_socket::AddMultilineField(const string & name, stringa & value)
   {
      m_fields[name] = value;
   }


   void http_post_socket::AddFile(const string & name,const string & filename,const string & type)
   {
      if (Application.file().exists(filename))
      {
         m_mapFiles[name]              = filename;
         m_mapContentLength[filename]  = Application.file().length(filename);
         m_mapContentType[filename]    = type;
         m_bMultipart                  = true;
      }
      else
      {
         log("AddFile", Errno, StrError(Errno), ::core::log::level_fatal);
         SetCloseAndDelete();
      }
   }

   void http_post_socket::step()
   {



      if (m_bMultipart)
      {
         DoMultipartPost();
      }
      else
      {


         string body;

         if (m_fields.has_property("json") && m_fields["json"].get_value().get_type() == var::type_propset)
         {
            body = m_fields["json"].propset().get_json();
            if (inheader(__id(content_type)).get_string().find_ci("application/json") < 0)
            {
               inheader(__id(content_type)) = "application/json" + ::str::has_char(inheader(__id(content_type)).get_string(), "; ");
            }
         }
         else if (m_fields.has_property("xml") && m_fields["xml"].get_value().get_type() == var::type_element)
         {
            ::xml::node * pnode = m_fields["xml"].cast < ::xml::node >();
            body = pnode->get_xml();
            body.trim();
            if(inheader(__id(content_type)).get_string().find_ci("application/xml") < 0)
            {
               inheader(__id(content_type)) = "application/xml; " + inheader(__id(content_type)).get_string();
            }
         }
         else
         {
            body = m_fields.get_http_post();
            if(inheader(__id(content_type)).get_string().find_ci("application/x-www-form-urlencoded") < 0)
            {
               inheader(__id(content_type)) = "application/x-www-form-urlencoded; " + inheader(__id(content_type)).get_string();
            }
         }

         // only fields, no files, add urlencoding
         /*for (std::map<string,list<string> >::iterator it = m_fields.begin(); it != m_fields.end(); it++)
         {
            string name = (*it).first;
            list<string>& ref = (*it).second;
            if (body.get_length())
            {
               body += '&';
            }
            body += name + "=";
            bool first = true;
            for (list<string>::iterator it = ref.begin(); it != ref.end(); it++)
            {
               string value = *it;
               if (!first)
               {
                  body += "%0d%0a"; // CRLF
               }
               body += Utility::rfc1738_encode(value);
               first = false;
            }
         }*/

         // build header, send body
         m_request.attr(__id(http_method)) = "POST";
         m_request.attr(__id(http_version)) = "HTTP/1.1";
         string strHost = GetUrlHost();
         inheader(__id(host)) = strHost; // oops - this is actually a request header that we're adding..
         string strUserAgent = MyUseragent();
         if(!(bool)m_request.attr("minimal_headers"))
         {
            inheader(__id(user_agent)) = "ca2_netnode";
            inheader(__id(accept)) = "text/html, text/plain, application/xml, */*;q=0.01";
            inheader(__id(connection)) = "close";
         }
         inheader(__id(content_length)) = (int64_t) body.get_length();

      m_bExpectResponse = true;
      m_bExpectRequest = false;

         SendRequest();

         if(body.get_length() > 0)
         {
         // send body
         write( body );
         }
      }
   }


   void http_post_socket::DoMultipartPost()
   {
      uint64_t length = 0; // calculate content_length of our post body
      string tmp;

      // fields
      {
         for(int i = 0; i < m_fields.m_propertya.get_count(); i++)
         {
            string name = m_fields.m_propertya[i].name();
            var & var = m_fields.m_propertya[i].get_value();
            tmp = "--" + m_boundary + "\r\n"
               "content-disposition: form-data; name=\"" + name + "\"\r\n"
               "\r\n";
            for(int j = 0; j < var.get_count(); j++)
            {
               string value = var[j].get_string();
               tmp += value + "\r\n";
            }
            length += (long)tmp.get_length();
         }
      }

      // files
      {
         
         POSITION pos = m_mapFiles.get_start_position();

         for(; pos != NULL; )
         {
            
            string name;
            
            string filename;
            
            m_mapFiles.get_next_assoc(pos, name, filename);
            
            uint64_t content_length = m_mapContentLength[filename];

            string content_type = m_mapContentType[filename];

            tmp = "--" + m_boundary + "\r\n"
               "content-disposition: form-data; name=\"" + name + "\"; filename=\"" + filename + "\"\r\n"
               "content-type: " + content_type + "\r\n"
               "\r\n";

            length += (long)tmp.get_length();

            length += content_length;

            length += 2; // crlf after file

         }

      }

      // end
      tmp = "--" + m_boundary + "--\r\n";
      length += (long)tmp.get_length();

      // build header, send body
      m_request.attr(__id(http_method)) = "POST";
      m_request.attr(__id(http_version)) = "HTTP/1.1";
      inheader(__id(host)) = GetUrlHost(); // oops - this is actually a request header that we're adding..
      inheader(__id(user_agent)) = MyUseragent();
      inheader(__id(accept)) = "text/html, text/plain, */*;q=0.01";
      inheader(__id(connection)) = "close";
      inheader(__id(content_type)) = "multipart/form-data; boundary=" + m_boundary;
      inheader(__id(content_length)) = (int64_t) length;

      m_bExpectResponse = true;
      m_bExpectRequest = false;

      SendRequest();

      // send fields
      {
         for(int i = 0; i < m_fields.m_propertya.get_count(); i++)
         {
            string name = m_fields.m_propertya[i].name();
            var & var = m_fields.m_propertya[i].get_value();
            tmp = "--" + m_boundary + "\r\n"
               "content-disposition: form-data; name=\"" + name + "\"\r\n"
               "\r\n";
            for(int j = 0; j < var.get_count(); j++)
            {
               string value = var[j].get_string();
               tmp += value + "\r\n";
            }
            write( tmp );
         }
      }

      // send files
      {
         POSITION pos = m_mapFiles.get_start_position();
         for(; pos != NULL;)
         {
            string name;
            string filename;
            m_mapFiles.get_next_assoc(pos, name, filename);
            string content_type = m_mapContentType[filename];
            tmp = "--" + m_boundary + "\r\n"
               "content-disposition: form-data; name=\"" + name + "\"; filename=\"" + filename + "\"\r\n"
               "content-type: " + content_type + "\r\n"
               "\r\n";
            write( tmp );
            {
               ::file::binary_buffer_sp spfile(allocer());
               if(spfile->open(filename, ::file::type_binary | ::file::mode_read))
               {
                  transfer_from(*spfile);
               }
            }
            write("\r\n");
         }
      }

      // end of send
      write("--" + m_boundary + "--\r\n");
   }


   void http_post_socket::SetMultipart()
   {
      m_bMultipart = true;
   }


}


