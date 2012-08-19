#pragma once


namespace dynamic_source
{


   class CLASS_DECL_ca httpd_socket :
      virtual public ::sockets::httpd_socket
   {
   public:


      int                                    m_iCa2FetchMode;

      string                                 m_strLocale;
      dynamic_source::script_instance *      m_pinstanceCurrent;


      httpd_socket(::sockets::socket_handler_base& );
      ~httpd_socket();


   protected:
      httpd_socket(const httpd_socket& s);

   };


} // namespace netnode
