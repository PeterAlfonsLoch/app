#pragma once


namespace netserver
{



   class CLASS_DECL_AURA socket_thread :
      virtual public ::thread
   {
   public:



      string                                       m_strIp;
      int32_t                                      m_iPort;
      int                                          m_iSsl;

      SOCKET                                       m_hsocket;
      string                                       m_strCat;
      string                                       m_strCipherList;

      sp(::netserver::socket_handler)              m_psockethandler;


      socket_thread(::aura::application * papp);
      ~socket_thread();


      virtual int32_t run() override;

      virtual ::netserver::socket_handler * create_socket_handler();


      ::netserver::socket_handler * socket_handler();


   };


} // namespace netserver




