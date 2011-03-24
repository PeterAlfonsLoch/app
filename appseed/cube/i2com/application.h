#pragma once

namespace i2com
{

   class thread;

   thread * KickNetNode();

   class document;
   class netnodeScriptManager;

   class CLASS_DECL_CA2_CUBE application :
      public ::status::application
   {
   public:
      application(void);
      virtual ~application(void);

      virtual void construct();

      virtual bool bergedge_start();


      bool initialize_instance();
      BOOL exit_instance();



      //status::status_class m_status;

      

      Ex1FactoryImpl * Ex1AppGetFactoryImpl();

      ::userbase::multiple_document_template * m_ptemplateRtpRx;
      ::userbase::multiple_document_template * m_ptemplateEdge;
      ::userbase::multiple_document_template * m_ptemplateHtml;
      ::collection::map < int, int, document *, document * > m_mapEdge;
      ::userbase::document_template * m_ptemplateFront;

      ::userbase::single_document_template * m_ptemplateContact;
      ::userbase::multiple_document_template * m_ptemplateCommunication;

      void get_Votagus_folder(string &str);


      //msn_socket m_msnsocket;

      int get_free_rtprx_port();

      int open_rtprx();




      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

         
      void pre_translate_message(gen::signal_object * pobj);

      virtual ::ca::application * get_app() const;
   };


} // namespace i2com

