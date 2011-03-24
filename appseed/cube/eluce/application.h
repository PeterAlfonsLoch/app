#pragma once

namespace eluce
{

   class CLASS_DECL_CA2_CUBE application :
      public ::biteditor_application
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

      void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
         

      virtual ::ca::application * get_app() const;

      void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);

   };

} // namespace eluce
