#pragma once


namespace user
{


   class keyboard;
   class front_end_schema;
   class ::user::document_manager;
   class document_template;
   class document;


   class CLASS_DECL_ca2 user :
      virtual public ::ca::section,
      virtual public ::user::document_request_interface,
      virtual public BaseMenuCentralContainer,
      virtual public ::database::client
   {
   public:


      filemanager::_shell::ImageSet *        m_pshellimageset;
      sp(::user::keyboard_focus)               m_pkeyboardfocus;
      ::user::mouse_focus *                  m_pmousefocusLButtonDown;
      ::user::mouse_focus *                  m_pmousefocusRButtonDown;
      //class window_map *                     m_pwindowmap;
      ::user::keyboard *                     m_pkeyboard;

      ::user::front_end_schema *   m_pufeschema;
      ::user::front_end *           m_pufe;



      user();
      virtual ~user();

      virtual bool set_keyboard_layout(const char * pszPath, bool bUser);

      filemanager::_shell::ImageSet & shellimageset();

      virtual bool initialize1();
      virtual bool initialize();


      //class window_map & window_map();


      virtual sp(::user::keyboard_focus) get_keyboard_focus();
      virtual void set_keyboard_focus(sp(::user::keyboard_focus) pkeyboardfocus);
      virtual ::user::mouse_focus * get_mouse_focus_LButtonDown();
      virtual void set_mouse_focus_LButtonDown(::user::mouse_focus * pmousefocus);
      virtual ::user::mouse_focus * get_mouse_focus_RButtonDown();
      virtual void set_mouse_focus_RButtonDown(::user::mouse_focus * pmousefocus);


      string message_box(const char * pszMatter, ::ca::property_set & propertyset);
      virtual int32_t simple_message_box_timeout(sp(::user::interaction) puiOwner, const char * pszMessage, int32_t iTimeout, UINT fuStyle = MB_OK);
      virtual int32_t simple_message_box(sp(::user::interaction) puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
      virtual int32_t track_popup_menu(const char * pszMatter, point pt, sp(::user::interaction) puie);

      virtual bool get_fs_size(string & strSize, const char * pszPath, bool & bPending);
      virtual bool get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending);

      virtual void data_on_after_change(::ca::signal_object * pobj);

      class keyboard & keyboard();


      virtual sp(::ca::type_info) controltype_to_typeinfo(::user::control::e_type type);


      virtual int32_t GetVisibleTopLevelFrameCountExcept(sp(::user::interaction) pwndExcept);


      virtual void SendMessageToWindows(UINT message, WPARAM wParam, LPARAM lParam);

      virtual void AddToRecentFileList(const char * lpszPathName);

      ::user::front_end_schema * GetUfeSchema();
      ::user::front_end * GetUfe();

      virtual bool finalize();

      virtual void _001CloseAllDocuments(bool bEndSession);
      void add_document_template(sp(::user::document_template) ptemplate);
      virtual sp(::user::document) _vmsguserbaseOpenDocumentFile(const char * lpszFileName);

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);


      virtual void _001OnFileNew();


      void defer_add_document_template(sp(::user::document_template) ptemplate);

      
         stringa                       m_straEscape;








         int32_t GetVisibleFrameCount();
         int32_t GetVisibleFrameCountExcept(sp(::user::interaction) pwndExcept);
         //int32_t GetVisibleTopLevelFrameCountExcept(sp(::user::interaction) pwndExcept);

         

         DECL_GEN_SIGNAL(VmsGuiiOnAppLanguage)

      
         //::user::interaction_ptr_array & frames();


//         virtual bool initialize1();
         //virtual bool initialize();

         virtual int32_t exit_instance();

         // Load MRU file list and last preview state.
         void LoadStdProfileSettings(UINT nMaxMRU = ___MRU_COUNT);


//         string message_box(const char * pszMatter, ::ca::property_set & propertyset);


      // Running Operations - to be done on a running user
         // Dealing with document templates
//         void add_document_template(sp(document_template) ptemplate);
         ::count get_template_count() const;
         sp(document_template) get_template(index index) const;


  //       virtual bool set_keyboard_layout(const char * pszPath, bool bUser);
//         virtual void on_set_keyboard_layout(const char * pszPath, bool bUser);






   // Running Operations - to be done on a running user
      // Dealing with document templates
   /*   void add_document_template(sp(document_template) ptemplate);
      POSITION get_template_count() const;
      sp(document_template) get_template(POSITION& pos) const;

      // open named file, trying to match a regsitered
      // document template to it.
      virtual sp(document) open_document_file(var var);

      // add a string to the recent file list. remove oldest string,
      // if no space left.
      virtual void AddToRecentFileList(const char * lpszPathName);

      // Printer DC Setup routine, 'struct tagPD' is a PRINTDLG structure.
      void SelectPrinter(HANDLE hDevNames, HANDLE hDevMode,
         bool bFreeOld = TRUE);


      // create a DC for the system default printer.
      bool CreatePrinterDC(::ca::graphics_sp& spgraphics);


   bool GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg);

      // Finds number of opened document items owned by templates
      // registered with the doc manager.
      int32_t get_open_document_count();

      // helpers for standard commdlg dialogs
      bool do_prompt_file_name(var & varFile, UINT nIDSTitle,
            uint32_t lFlags, bool bOpenFileDialog, sp(document_template) ptemplate);
      int_ptr DoPrintDialog(CPrintDialog* pPD);
   // Implementation
         // Server object for document creation
      //{{__MSG(App)
      void OnUpdateRecentFileMenu(cmd_ui * pcmdui) ;
      //}}__MSG

   // Initialization Operations - should be done in initialize_instance
   protected:
      // Load MRU file list and last preview state.
      void LoadStdProfileSettings(UINT nMaxMRU = ___MRU_COUNT);

      void EnableShellOpen();

      // SetDialogBkColor is no longer supported.
      // To change dialog background and text color, handle WM_CTLCOLORDLG instead.
      __DEPRECATED("BaseWinApp::SetDialogBkColor is no longer supported. Instead, handle WM_CTLCOLORDLG in your dialog")
            void SetDialogBkColor(COLORREF clrCtlBk = RGB(192, 192, 192), COLORREF clrCtlText = RGB(0, 0, 0));

   */
    


   };


   CLASS_DECL_ca2 ::user::front_end_schema * GetUfeSchema(sp(::ca::application) papp);
   CLASS_DECL_ca2 ::user::front_end * GetUfe(sp(::ca::application) papp);


} // namespace ca


