#pragma once

namespace netnodecfg
{

   class CLASS_DECL_CA2_CUBE application :
      public ::mplite::application
   {
   public:


      ::userbase::single_document_template * m_pdoctemplate;


      application(void);
      virtual ~application(void);

      virtual void construct();

      virtual bool initialize_instance();
      virtual int exit_instance();

      virtual bool bergedge_start();

      void _001OnFileNew();

   };

} // namespace netnodecfg

