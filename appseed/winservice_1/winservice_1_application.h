#pragma once


namespace winservice_1
{


   class CLASS_DECL_CA2_WINSERVICE_1 application :
      public ::cube::application
   {
   public:


      class windows_run :
         virtual public thread
      {
      public:
         windows_run(::ca::application * papp);
         bool initialize_instance();
         int run();
      };

      class class_wnd :
         virtual public ::user::interaction
      {
      public:
         class_wnd(const char * pszClassName);
         const char * m_lpszClassName;
         WNDCLASS m_wndclass;
      };

      pointer_list * m_plistShellObjects;
      void FreeShellTrayObjects(pointer_list *objects);
      int LoadShellTrayObjects(pointer_list **ppv);


      class shell_traywnd :
         virtual public class_wnd
      {
      public:
         shell_traywnd(::ca::application * papp);

         array_ptr_alloc < ::userbase::TRAYDATA > m_traydataa;
         array_ptr_alloc < TBBUTTON > m_buttona;

         int find(HWND hwnd, UINT uiId);

         class traynotifywnd :
            virtual public class_wnd
         {
         public:
            traynotifywnd(::ca::application * papp);


            class syspager :
               virtual public class_wnd
            {
            public:
               syspager(::ca::application * papp);


               class toolbar :
                  virtual public class_wnd
               {
               public:
                  toolbar(::ca::application * papp);

                  syspager * m_pwndParent;

                  using class_wnd::create;
                  using ::ex1::request_interface::create;
                  bool create(syspager * pwndParent);
                  DECL_GEN_SIGNAL(message_handler)
               };

               toolbar m_toolbar;
               traynotifywnd * m_pwndParent;

               using class_wnd::create;
               using ::ex1::request_interface::create;
               bool create(traynotifywnd * pwndParent);
               DECL_GEN_SIGNAL(message_handler)
            };

            syspager m_syspager;
            shell_traywnd * m_pwndParent;

            using class_wnd::create;
            using ::ex1::request_interface::create;
            bool create(shell_traywnd * pwndParent);
            DECL_GEN_SIGNAL(message_handler)
         };

         traynotifywnd m_notifywnd;

         using class_wnd::create;
         using ::ex1::request_interface::create;
         bool create();
         DECL_GEN_SIGNAL(message_handler)
      };

      shell_traywnd *               m_ptraywnd;
      winservice_1::thread *        m_pthread;
      update_schedule_thread *      m_pupdatethread;
      ::userbase::single_document_template *  m_ptemplate_html;

      application(void);
      virtual ~application(void);


      virtual bool initialize_instance();
      virtual int  exit_instance();

      virtual void on_request(::ca::create_context * pcreatecontext);

      virtual void _001CloseApplication();

      bool RunShellLink();
      bool RunLoginStartup();
      bool InstallStartupLinks();
      bool make_link(const char * pszLink, const char * pszLocation, const char * pszParameters, const char * pszDirectory);


	   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);


      virtual void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);


      virtual bool on_install();
      virtual bool on_uninstall();
      virtual void on_process_initialize_command_line();
   

   };


} // namespace winservice_1

