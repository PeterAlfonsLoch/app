#pragma once


namespace command
{


   class CLASS_DECL_ca application :
      public ::mail::application
   {
   public:


      ::userbase::single_document_template *    m_ptemplate_html;


      application(void);
      virtual ~application(void);

      void construct();


      bool initialize_instance();
      BOOL exit_instance();


	   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);



   		

      virtual ::ca::application * get_app() const;
      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

   };

} // namespace command