#pragma once

namespace netnodecfg
{

   class CLASS_DECL_CA2_TESSERACT application :
      public ::eluce::application
   {
   public:


      ::userbase::single_document_template *    m_pdoctemplate;
      configuration *                           m_pconfiguration;


      application(void);
      virtual ~application(void);

      virtual void construct();

      virtual bool initialize_instance();
      virtual int exit_instance();

      virtual void on_request(::ca::create_context * pcreatecontext);

      void _001OnFileNew();

   };

} // namespace netnodecfg

