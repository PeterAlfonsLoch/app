#pragma once


namespace user
{

   class keyboard;

   class CLASS_DECL_ca application :
      virtual public database::application,
      virtual public visual::application,
      virtual public document_request_interface
   {
   public:

      
      keyboard *           m_pkeyboard;
      stringa              m_straEscape;
      class window_map *   m_pwindowmap;


      application();
      virtual ~application();

      int GetVisibleFrameCount();
      int GetVisibleFrameCountExcept(::user::interaction * pwndExcept);
      int GetVisibleTopLevelFrameCountExcept(::user::interaction * pwndExcept);

      virtual void SendMessageToWindows(UINT message, WPARAM wParam, LPARAM lParam);

      DECL_GEN_SIGNAL(VmsGuiiOnAppLanguage)

      virtual bool initialize();

      virtual int exit_instance();

      virtual ::ca::type_info controltype_to_typeinfo(user::control::e_type type);

      class keyboard & keyboard();


      virtual bool set_keyboard_layout(const char * pszPath, bool bUser);
      virtual void on_set_keyboard_layout(const char * pszPath, bool bUser);


      class window_map & window_map();


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
      BOOL bFreeOld = TRUE);


   // create a DC for the system default printer.
   BOOL CreatePrinterDC(::ca::graphics_sp& spgraphics);


BOOL GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg);

   // Finds number of opened document items owned by templates
   // registered with the doc manager.
   int get_open_document_count();

   // helpers for standard commdlg dialogs
   BOOL do_prompt_file_name(string & fileName, UINT nIDSTitle,
         DWORD lFlags, BOOL bOpenFileDialog, document_template * ptemplate);
   INT_PTR DoPrintDialog(CPrintDialog* pPD);
// Implementation
      // Server object for document creation
   //{{AFX_MSG(App)
   void OnUpdateRecentFileMenu(cmd_ui * pcmdui) ;
   //}}AFX_MSG

// Initialization Operations - should be done in initialize_instance
protected:
   // Load MRU file list and last preview state.
   void LoadStdProfileSettings(UINT nMaxMRU = _AFX_MRU_COUNT);

   void EnableShellOpen();

   // SetDialogBkColor is no longer supported.
   // To change dialog background and text color, handle WM_CTLCOLORDLG instead.
   AFX_DEPRECATED("BaseWinApp::SetDialogBkColor is no longer supported. Instead, handle WM_CTLCOLORDLG in your dialog")
         void SetDialogBkColor(COLORREF clrCtlBk = RGB(192, 192, 192), COLORREF clrCtlText = RGB(0, 0, 0));

*/
   };


   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }
///inline void AppInterface::SetDialogBkColor(COLORREF /*clrCtlBk*/, COLORREF /*clrCtlText*/)
//{
//}

} // namespace user
