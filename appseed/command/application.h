#pragma once

namespace command
{

   class CLASS_DECL_CA2_COMMAND application :
      public ::cube::application
   {
   public:
      application(void);
      virtual ~application(void);

      ::userbase::single_document_template * m_ptemplate_html;

      bool initialize_instance();
      BOOL exit_instance();


	   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
   		

      virtual ::ca::application * get_app() const;
      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

   };

} // namespace command