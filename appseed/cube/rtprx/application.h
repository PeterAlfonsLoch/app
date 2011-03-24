#pragma once

namespace rtprx
{

   class CLASS_DECL_CA2_CUBE application :
      virtual public ::paint::application
   {
   public:


      ::userbase::single_document_template * m_ptemplate_html;
      ::userbase::single_document_template * m_ptemplateVideo;


      application(void);
      virtual ~application(void);

      virtual void construct();

      virtual bool initialize_instance();
      virtual int exit_instance();

      virtual bool bergedge_start();

      virtual void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
         

      virtual ::ca::application * get_app() const;
      void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);

      ::document * _001OpenDocumentFile(var varFile);


   };

} // namespace rtprx

