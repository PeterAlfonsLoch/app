#pragma once

namespace tarsila
{

   class CLASS_DECL_CA2_CUBE application :
      public ::i2com::application
   {
   public:


      ::userbase::single_document_template * m_pdoctemplate;


      application(void);
      virtual ~application(void);


      virtual bool initialize_instance();
      virtual int exit_instance();

      virtual bool bergedge_start();

      virtual void _001OnFileNew();

      virtual ::document * _001OpenDocumentFile(var varFile);

      virtual bool on_install();

   };

} // namespace tarsila