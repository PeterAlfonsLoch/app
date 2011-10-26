#pragma once

namespace status
{

   class CLASS_DECL_CA2_TESSERACT application :
      public ::paint::application
   {
   public:


      ::userbase::single_document_template * m_pdoctemplate;
      status_class * m_pstatus;


      application(void);
      virtual ~application(void);

      virtual void construct();

      virtual bool initialize_instance();
      virtual int exit_instance();

      virtual bool bergedge_start();

      virtual void _001OnFileNew();

   };

} // namespace status