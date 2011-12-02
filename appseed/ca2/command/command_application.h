#pragma once


namespace command
{


   class CLASS_DECL_ca application :
      public ::mail::application
   {
   public:


      ::userbase::single_document_template *    m_ptemplateCommandMain;


      application(void);
      virtual ~application(void);

      void construct();


      bool initialize_instance();
      BOOL exit_instance();


	   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);



   		

      virtual ::ax::application * get_app() const;
      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

   };

} // namespace command