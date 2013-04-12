#pragma once


namespace nature
{


   class database;


   class CLASS_DECL_ca2 application :
      virtual public ::cube::application
   {
   public:


      sp(::userbase::single_document_template)  m_ptemplate_html;
      database *                    m_pdatabase;


      application();
      virtual ~application();

      using ::ca::thread::construct;
      using ::ca::application::construct;

      virtual void construct();

      virtual bool initialize_instance();
      virtual int32_t exit_instance();

      bool InitializeLocalDataCentral();

      void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

   };


} // namespace nature