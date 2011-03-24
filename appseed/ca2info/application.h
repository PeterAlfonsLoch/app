#pragma once

namespace ca2info
{

   class CLASS_DECL_CA2_STATUS application :
      public ca84::application
   {
   public:


      ::userbase::single_document_template * m_pdoctemplate;


      application(void);
      virtual ~application(void);


      virtual bool initialize_instance();
      virtual int  exit_instance();

      virtual bool bergedge_start();

      virtual void _001OnFileNew();

   };

} // namespace ca2info