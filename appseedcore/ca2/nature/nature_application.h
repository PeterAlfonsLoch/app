#pragma once

namespace nature
{

   class database;

   class CLASS_DECL_ca application :
      virtual public ::icube::application
   {
   public:


      ::userbase::single_document_template *  m_ptemplate_html;
      database *                    m_pdatabase;


      application();
      virtual ~application(void);

      using ::ca::thread::construct;
      using ::ca::application::construct;

      virtual void construct();

      virtual bool initialize_instance();
      virtual int exit_instance();

      bool InitializeLocalDataCentral();

      void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      void request(var & varFile, var & varQuery);



   };


} // namespace nature