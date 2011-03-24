#pragma once

namespace veriview
{

   class CLASS_DECL_CA2_CUBE application :
      virtual public ::devedge::application
   {
   public:


      ::userbase::single_document_template *  m_ptemplate_main;
      ::userbase::multiple_document_template *  m_ptemplate_html;
      ::userbase::single_document_template *  m_ptemplate_html_edit;
      ::userbase::document_template *        m_ptemplate_devedge;


      application(void);
      virtual ~application(void);


      virtual void construct();


      virtual bool initialize_instance();
      virtual int  exit_instance();

      virtual bool bergedge_start();

      virtual void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
         
      virtual void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);

   };

} // namespace veriview
