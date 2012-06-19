#pragma once


namespace command
{


   class CLASS_DECL_ca2 application :
      virtual public ::mail::application
   {
   public:


      ::userbase::single_document_template *    m_ptemplateCommandMain;


      application();
      virtual ~application();


      using ::mail::application::construct;
      void construct();


      bool initialize_instance();
      virtual int exit_instance();


	   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);


      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

   };

} // namespace command