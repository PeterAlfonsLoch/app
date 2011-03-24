#pragma once

namespace verisimplevideo
{

   class CLASS_DECL_CA2_CUBE application :
      public ::verifile::application
   {
   public:


      ::userbase::single_document_template * m_ptemplate_html;
      ::userbase::single_document_template * m_ptemplateVideo;


      application(void);
      virtual ~application(void);


      virtual void construct();


      virtual bool initialize_instance();
      virtual int  exit_instance();

      ::document * _001OpenDocumentFile(var varFile);

      virtual bool on_install();

      virtual bool bergedge_start();

      virtual void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
         

      virtual ::ca::application * get_app() const;
      virtual void on_request(var & varFile, var & varQuery);

   };

} // namespace verisimplevideo
