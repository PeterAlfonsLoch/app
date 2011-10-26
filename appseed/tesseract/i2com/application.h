#pragma once

namespace i2com
{

   class thread;

   thread * KickNetNode();

   class document;
   class netnodeScriptManager;

   class CLASS_DECL_CA2_TESSERACT application :
      public ::status::application
   {
   public:
      
      
      ::userbase::multiple_document_template * m_ptemplateRtpRx;
      ::userbase::single_document_template * m_ptemplateEdge;
      ::userbase::multiple_document_template * m_ptemplateHtml;
      ::collection::map < int, int, document *, document * > m_mapEdge;
      ::userbase::document_template * m_ptemplateFront;

      ::userbase::single_document_template * m_ptemplateContact;
      ::userbase::multiple_document_template * m_ptemplateCommunication;

      //msn_socket m_msnsocket;


      application(void);
      virtual ~application(void);

      virtual void construct();

      virtual void on_request(::ca::create_context * pcreatecontext);


      bool initialize_instance();
      BOOL exit_instance();

      int get_free_rtprx_port();

      int open_rtprx(const char * pszHost, int iPort);


      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

         
      void pre_translate_message(gen::signal_object * pobj);

   };


} // namespace i2com

