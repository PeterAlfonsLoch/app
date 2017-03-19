#include "framework.h"


namespace netserver
{


   static ::count s_countNetnodeSocket = 0;


   socket::socket(::sockets::base_socket_handler & h) :
      ::object(h.get_app()),
      base_socket(h),
      ::sockets::socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_base_socket(h),
      http_socket(h),
      httpd_socket(h)
   {
      m_bSetCookie = true;
      s_countNetnodeSocket++;
   }



   socket::~socket()
   {
      s_countNetnodeSocket--;
   }

   void socket::send_response()
   {

      on_send_response();

      int32_t iStatusCode;

      string strStatus;

      if (outattr(__id(http_status_code)).is_new() || outattr(__id(http_status)).is_new())
      {

         if (outheaders().has_property(__id(location)))
         {

            iStatusCode = 303; // 303 (See Other Location)

            strStatus = "See Other";

         }
         else
         {

            iStatusCode = 200;

            strStatus = "OK";

         }

         outattr(__id(http_status_code)) = iStatusCode;

         outattr(__id(http_status)) = strStatus;

      }

      outattr(__id(http_version)) = "HTTP/1.1";

      if (::str::begins(outheader(__id(content_type)), "image/"))
      {

         m_bSetCookie = false;

      }
      else if (outheader(__id(content_type)) == "application/javascript")
      {

         m_bSetCookie = false;

      }
      else if (outheader(__id(content_type)) == "text/css")
      {

         m_bSetCookie = false;

      }

      Respond();

   }

   void socket::OnExecute()
   {
      
      string strUrl = m_request.attr("http_protocol").get_string() + "://" + m_request.header("host").get_string() + m_request.attr("request_uri").get_string();

      TRACE("netserver::socket::OnExecute Url ----**START**====> %s", strUrl);

      DWORD dwExecuteBeg = ::get_tick_count();

      m_bEnd = false;

      send_response();

      DWORD dwExecuteEnd = ::get_tick_count();

      TRACE("netserver::socket::OnExecute Url ----**END****====> %s", strUrl);

      TRACE("netserver::socket::OnExecute Ms -----**END****====> %d", dwExecuteEnd - dwExecuteBeg);

   }


   void socket::OnResponseComplete()
   {

   }

   
   void socket::on_send_response()
   {


   }


   bool socket::http_filter_response_header(id key, stringa & straValue)
   {
      if (key == __id(location) && straValue.get_count() >= 1)
      {
         for (int i = 0; i < straValue.get_size(); i++)
         {
            url_domain domain;
            domain.create(System.url().get_server(straValue[i]));
            if (domain.m_strName == "account.ca2.cc")
            {
               //straValue[i] = "https://" + Application.m_strFontopusServer + System.url().get_object(straValue[i]);
            }
         }
      }
      else if (!m_bSetCookie && key == __id(set_cookie))
      {
         return false;
      }
      return true;
   }



   void socket::simple_file_server(const char * pszPath)
   {

      smart_pointer_array < int_array > rangea;

      if (strlen(inheader("range")) > 0)
      {
         stringa straItem;
         straItem.explode("=", inheader("range"));
         if (straItem.get_count() == 2)
         {
            string strUnit = straItem[0];
            stringa stra;
            stra.explode(",", straItem[1]);
            for (int32_t i = 0; i < stra.get_count(); i++)
            {
               stringa straRange;
               straRange.explode("-", stra[i]);
               if (straRange.get_count() == 2)
               {
                  rangea.add(new int_array());
                  rangea.last_ptr()->add(atoi(straRange[0]));
                  straRange[1].trim();
                  if (strlen(straRange[1]) == 0)
                     rangea.last_ptr()->add(-1);
                  else
                     rangea.last_ptr()->add(atoi(straRange[1]));
               }
            }
         }
      }

      read_file(pszPath, &rangea);

   }

   //void socket::simple_image_server(const char * pszPath, int iMaxWidth, int iMaxHeight)
   //{

   //   if (iMaxWidth <= 0 && iMaxHeight <= 0)
   //   {
   //      simple_file_server(pszPath);
   //   }
   //   else
   //   {
   //      
   //      ::visual::dib_sp spdib(allocer());

   //      spdib.load_from_file(pszPath);

   //      double dRateW = 1.0;

   //      if (iMaxWidth > 0)
   //      {
   //         if (spdib->m_size.cx > iMaxWidth)
   //         {
   //            dRateW = (double)iMaxWidth / (double)spdib->m_size.cx;
   //         }
   //      }

   //      double dRateH = 1.0;

   //      if (iMaxHeight > 0)
   //      {
   //         if (spdib->m_size.cy > iMaxHeight)
   //         {
   //            dRateH = (double)iMaxHeight / (double)spdib->m_size.cx;
   //         }
   //      }

   //      double dRate = MIN(dRateW, dRateH);

   //      ::visual::dib_sp dib(allocer());

   //      dib->create((int32_t)(spdib->m_size.cx * dRate), (int32_t)(spdib->m_size.cy * dRate));

   //      dib->stretch_dib(spdib);

   //      ::visual::save_image saveimage;

   //      saveimage.m_eformat = ::visual::image::format_jpeg;
   //      saveimage.m_iQuality = 50;

   //      outheader(__id(content_type)) = "image/jpeg";


   //      dib.save_to_file(&response().file(), &saveimage);

   //   }


   //}


} // namespace netserver




