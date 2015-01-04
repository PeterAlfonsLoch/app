#pragma once


namespace http
{
   class form;
}


namespace sockets
{

   /** \defgroup webserver Webserver framework */
   /** Web server socket framework.
      \ingroup webserver */
   class CLASS_DECL_AXIS httpd_socket : public http_base_socket
   {
   public:
      httpd_socket(base_socket_handler& );
      ~httpd_socket();


   protected:
      httpd_socket(const httpd_socket& s);
      /** Decode and send a base64-encoded string.
         \param str64 Base64-encoded string
         \param type Mime type of content (content-type header) */
      void Send64(const string & str64, const string & type);
      string datetime2httpdate(const string & dt);
      string GetDate();
      void Reset();

      virtual void InitSSLServer();



   private:
      httpd_socket& operator=(const httpd_socket& s);
      size_t m_received;
      string m_http_date;

   };


} // namespace sockets



