#pragma once


namespace winservice_filesystemsize
{


   class CLASS_DECL_CA2_TESSERACT application :
      public ::cube::application
   {
   public:


      ::userbase::single_document_template * m_ptemplate_html;
      FileSystemSizeWnd * m_pwnd;


      application(void);
      virtual ~application(void);

      virtual void construct();


      virtual bool initialize_instance();
      virtual BOOL exit_instance();

      virtual bool bergedge_start();

      bool InstallStartupLinks();
      int RunService();
      bool RunShellLink();

      void _001CloseApplication();

   };

} // namespace winservice_filesystemsize