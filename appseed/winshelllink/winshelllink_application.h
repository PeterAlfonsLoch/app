#pragma once


namespace winshelllink
{


   class CLASS_DECL_CA2_WINSHELLLINK application :
      public cube2::application
   {
   public:
   
   
      ::userbase::single_document_template * m_ptemplate_html;


      application();
      virtual ~application();

      virtual bool initialize_instance();
      virtual int  exit_instance();

      virtual void on_request(::ca::create_context * pcreatecontext);

      virtual void _001OnFileNew();

	   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
		
      virtual void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);


   };


} // namespace winshelllink


