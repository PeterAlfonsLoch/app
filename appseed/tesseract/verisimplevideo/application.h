#pragma once

namespace verisimplevideo
{

   class CLASS_DECL_CA2_TESSERACT application :
      public ::verifile::application
   {
   public:


      ::userbase::single_document_template * m_ptemplate_html;
      ::userbase::single_document_template * m_ptemplateVideo;


      application(void);
      virtual ~application(void);


      virtual void construct();


      virtual bool initialize_instance();

      virtual bool on_install();

      virtual void on_request(::ca::create_context * pcreatecontext);

   };

} // namespace verisimplevideo
