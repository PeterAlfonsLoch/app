/** \file httpd_socket.cpp
*/
/*
Copyright (C) 2001-2007  Anders Hedstrom (grymse@alhem.net)

This library is made available under the terms of the GNU GPL.

If you would like to use this library in a closed-source application,
a separate license agreement is available. For information about
the closed-source license agreement for the C++ sockets library,
please visit http://www.alhem.net/Sockets/license.html and/or
email license@alhem.net.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#include "framework.h"
#include <openssl/ssl.h>


namespace sockets
{

   #define TMPSIZE 10000




   httpd_socket::httpd_socket(base_socket_handler& h) :
      element(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_base_socket(h),
      m_received(0)
   {
      m_http_date = datetime2httpdate(GetDate());
   }

   httpd_socket::httpd_socket(const httpd_socket& s) :
      element(s.get_app()),
      base_socket(s),
      socket(s),
      stream_socket(s),
      tcp_socket(s),
      http_base_socket(s)
   {
   }

   httpd_socket::~httpd_socket()
   {
   }







   void httpd_socket::Send64(const string & str64, const string & type)
   {
   //   Base64 bb;

   /*   if (request().headers()["if-modified-since"].get_string().CompareNoCase(m_start) == 0)
      {
         m_response.attr("http_status_code") = 304;
         m_response.attr("http_status") = "Not Modified";
         SendResponse();
      }
      else*/
      {
         primitive::memory mem;
         System.base64().decode(mem, str64);
         m_response.attr("http_status_code") = 200;
         m_response.attr("http_status") = "OK";

         m_response.header("Content-length") = (int64_t) mem.get_size();
         m_response.header(__id(content_type)) = type;
   //      m_response.header("Last-modified") = m_start;
         SendResponse();

         write((char *)mem.get_data(), (int32_t) mem.get_size());
      }
   }


   string httpd_socket::datetime2httpdate(const string & dt)
   {
      struct tm tp;
      time_t t;
      const char *days[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
      const char *months[] = { "Jan","Feb","Mar","Apr","May","Jun",
                         "Jul","Aug","Sep","Oct","Nov","Dec" };
      int32_t i;
      char s[40];

   /* 1997-12-16 09:50:40 */

      if (dt.get_length() == 19)
      {
         tp.tm_year = atoi(dt.Mid(0,4)) - 1900;
         i = atoi(dt.Mid(5,2)) - 1;
         tp.tm_mon = i >= 0 ? i : 0;
         tp.tm_mday = atoi(dt.Mid(8,2));
         tp.tm_hour = atoi(dt.Mid(11,2));
         tp.tm_min = atoi(dt.Mid(14,2));
         tp.tm_sec = atoi(dt.Mid(17,2));
         tp.tm_wday = 0;
         tp.tm_yday = 0;
         tp.tm_isdst = 0;
         t = mktime(&tp);
         if (t == -1)
         {
            log("datetime2httpdate", 0, "mktime() failed");
         }

         sprintf(s,"%s, %02d %s %d %02d:%02d:%02d GMT",
          days[tp.tm_wday],
          tp.tm_mday,
          months[tp.tm_mon],
          tp.tm_year + 1900,
          tp.tm_hour,tp.tm_min,tp.tm_sec);
      }
      else
      {
         *s = 0;
      }
      return s;
   }


   string httpd_socket::GetDate()
   {
      time_t t = time(NULL);
      struct tm tp;
   #ifdef _WIN32
      memcpy(&tp, localtime(&t), sizeof(tp));
   #else
      localtime_r(&t, &tp);
   #endif
      char slask[40]; // yyyy-mm-dd hh:mm:ss
      sprintf(slask,"%d-%02d-%02d %02d:%02d:%02d",
         tp.tm_year + 1900,
         tp.tm_mon + 1,
         tp.tm_mday,
         tp.tm_hour,tp.tm_min,tp.tm_sec);
      return slask;
   }


   void httpd_socket::Reset()
   {
      http_socket::Reset();
      m_received = 0;
   }


   map < int, int, map < SSL_CTX *, SSL_CTX *, DH *, DH * >, map < SSL_CTX *, SSL_CTX *, DH *, DH * > & > g_dh;

   DH * tmp_dh_callback(SSL *ssl, int is_export, int keylength)
   {
      switch(keylength)
      {
      case 512:
      case 1024:
      case 2048:
      case 4096:
         return g_dh[keylength][ssl->ctx];
         break;
      }
      return NULL;
   }


   void httpd_socket::InitSSLServer()
   {
      // here's the server.pem file we just created above
      // %! remember to change the password to the one you used for your server key
      InitializeContext(m_strCat, m_strCat, "", SSLv23_server_method());

      int_array ia;

      ia.add(512);
      ia.add(1024);
      ia.add(2048);
      ia.add(4096);

      for(index i = 0; i < ia.get_count(); i++)
      {

         int keylength = ia[i];

         string strTitle = System.file().name_(m_strCat);

         if(strTitle.find_ci(".") >= 0)
         {

            strTitle = strTitle.Left(strTitle.reverse_find("."));

         }


         string strFile = System.dir().path(System.dir().name(m_strCat), strTitle + ".dh" + ::str::from(keylength) + ".pem");

         FILE * paramfile = fopen(strFile, "r");

         if(paramfile)
         {

            DH * pdh = PEM_read_DHparams(paramfile, NULL, NULL, NULL);

            g_dh[keylength][m_ssl_ctx] = pdh;

            fclose(paramfile);

         }

      }

      SSL_CTX_set_tmp_dh_callback(m_ssl_ctx, &tmp_dh_callback);


      //int nid = OBJ_sn2nid(ECDHE_CURVE);

      EC_KEY *ecdh = EC_KEY_new_by_curve_name(NID_secp384r1);

      SSL_CTX_set_tmp_ecdh(m_ssl_ctx, ecdh);

      SSL_CTX_set_options(m_ssl_ctx, SSL_CTX_get_options(m_ssl_ctx) | SSL_OP_SINGLE_DH_USE | SSL_OP_CIPHER_SERVER_PREFERENCE);

      SSL_CTX_set_cipher_list(m_ssl_ctx, "ECDHE-RSA-AES256-SHA384:ECDHE-RSA-AES256-SHA:ECDHE-RSA-AES128-SHA:ECDHE-RSA-RC4-SHA:DHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA:RSA:SHA:3DES:!aNULL:!eNULL:!EXP:!LOW:!MD5:@STRENGTH");

   }


   httpd_socket & httpd_socket::operator=(const httpd_socket& s)
   {
      UNREFERENCED_PARAMETER(s);
      return *this;
   }


} // namespace sockets


