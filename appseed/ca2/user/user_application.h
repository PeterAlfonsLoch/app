#pragma once


namespace ca2
{


   namespace user
   {


      class keyboard;


      class CLASS_DECL_ca2 application :
         virtual public cubebase::application
      {
      public:

      
         stringa                       m_straEscape;







         application();
         virtual ~application();

         int GetVisibleFrameCount();
         int GetVisibleFrameCountExcept(::user::interaction * pwndExcept);
         int GetVisibleTopLevelFrameCountExcept(::user::interaction * pwndExcept);

         virtual void SendMessageToWindows(UINT message, WPARAM wParam, LPARAM lParam);

         DECL_GEN_SIGNAL(VmsGuiiOnAppLanguage)

      
         //::user::LPWndArray & frames();


         virtual bool initialize1();
         virtual bool initialize();

         virtual int exit_instance();

         // Load MRU file list and last preview state.
         void LoadStdProfileSettings(UINT nMaxMRU = ___MRU_COUNT);


         string message_box(const char * pszMatter, gen::property_set & propertyset);


      // Running Operations - to be done on a running application
         // Dealing with document templates
         void add_document_template(document_template * ptemplate);
         count get_template_count() const;
         document_template * get_template(index index) const;


  //       virtual bool set_keyboard_layout(const char * pszPath, bool bUser);
//         virtual void on_set_keyboard_layout(const char * pszPath, bool bUser);




         // Pointer to document_manager used to manage document templates
         // for this application instance.
   //      ::userbase::document_manager* m_pdocmanager;


   // Running Operations - to be done on a running application
      // Dealing with document templates
   /*   void add_document_template(document_template * ptemplate);
      POSITION get_template_count() const;
      document_template * get_template(POSITION& pos) const;

      // open named file, trying to match a regsitered
      // document template to it.
      virtual document * open_document_file(var var);

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
      int get_open_document_count();

      // helpers for standard commdlg dialogs
      bool do_prompt_file_name(var & varFile, UINT nIDSTitle,
            DWORD lFlags, bool bOpenFileDialog, document_template * ptemplate);
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


   } // namespace user


} // namespace ca2


