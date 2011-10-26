#pragma once

namespace vericalc
{

   class CLASS_DECL_CA2_TESSERACT application :
      public ::tarsila::application
   {
   public:


      ::userbase::single_document_template * m_ptemplate_html;


      application(void);
      virtual ~application(void);


      virtual bool initialize_instance();
      virtual int exit_instance();

      virtual void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
         

      virtual ::ca::application * get_app() const;
      virtual void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);

   };


} // namespace vericalc