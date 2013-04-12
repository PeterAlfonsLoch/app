#pragma once


namespace ca
{


   namespace user
   {


      class keyboard;


      class CLASS_DECL_ca2 user :
         virtual public ::user::user
      {
      public:

      
         stringa                       m_straEscape;







         user();
         virtual ~user();


         int32_t GetVisibleFrameCount();
         int32_t GetVisibleFrameCountExcept(sp(::user::interaction) pwndExcept);
         int32_t GetVisibleTopLevelFrameCountExcept(sp(::user::interaction) pwndExcept);

         

         DECL_GEN_SIGNAL(VmsGuiiOnAppLanguage)

      
         //::user::interaction_ptr_array & frames();


         virtual bool initialize1();
         virtual bool initialize();

         virtual int32_t exit_instance();

         // Load MRU file list and last preview state.
         void LoadStdProfileSettings(UINT nMaxMRU = ___MRU_COUNT);


         string message_box(const char * pszMatter, ::ca::property_set & propertyset);


      // Running Operations - to be done on a running user
         // Dealing with document templates
         void add_document_template(sp(document_template) ptemplate);
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


   } // namespace user


} // namespace ca


