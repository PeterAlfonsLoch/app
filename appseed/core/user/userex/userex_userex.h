#pragma once


class form_document;
class form_view;


namespace userex
{


   class keyboard;
   class front_end_schema;
   class document_manager;
   class impact_system;
   class document;


   class CLASS_DECL_CORE userex :
      virtual public ::user::core,
      virtual public ::user::server,
      virtual public BaseMenuCentralContainer,
      virtual public ::database::client
   {
   public:



      sp(::user::multiple_document_template)    m_ptemplateForm;
      sp(::user::multiple_document_template)    m_ptemplateChildForm;
      sp(::user::multiple_document_template)    m_ptemplatePlaceHolder;


      filemanager::_shell::ImageSet *           m_pshellimageset;


      ::user::front_end_schema *                m_pufeschema;
      ::user::front_end *                       m_pufe;



      userex(::base::application * papp);
      virtual ~userex();


      filemanager::_shell::ImageSet & shellimageset();

      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize();



      string message_box(const char * pszMatter, property_set & propertyset);
      virtual int32_t simple_message_box_timeout(sp(::user::interaction) puiOwner, const char * pszMessage, ::duration durationTimeout, UINT fuStyle = MB_OK);
      virtual int32_t simple_message_box(sp(::user::interaction) puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
      virtual int32_t track_popup_menu(const char * pszMatter, point pt, sp(::user::interaction) puie);

      virtual bool get_fs_size(string & strSize, const char * pszPath, bool & bPending);
      virtual bool get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending);

      virtual void data_on_after_change(signal_details * pobj);

      class keyboard & keyboard();


      virtual sp(type) controltype_to_typeinfo(::user::control::e_type type);


      virtual int32_t GetVisibleTopLevelFrameCountExcept(sp(::user::interaction) pwndExcept);


      virtual void SendMessageToWindows(UINT message, WPARAM wParam, LPARAM lParam);

      virtual void AddToRecentFileList(const char * lpszPathName);

      ::user::front_end_schema * GetUfeSchema();
      ::user::front_end * GetUfe();

      virtual bool finalize();

      virtual void _001CloseAllDocuments(bool bEndSession);
      void add_document_template(sp(::user::impact_system) ptemplate);
      virtual sp(::user::object) _vmsguserbaseOpenDocumentFile(const char * lpszFileName);

      virtual bool _001OnCmdMsg(base_cmd_msg * pcmdmsg);


      virtual void _001OnFileNew();


      void defer_add_document_template(sp(::user::impact_system) ptemplate);


      stringa                       m_straEscape;








      int32_t GetVisibleFrameCount();
      int32_t GetVisibleFrameCountExcept(sp(::user::interaction) pwndExcept);
      //int32_t GetVisibleTopLevelFrameCountExcept(sp(::user::interaction) pwndExcept);



      DECL_GEN_SIGNAL(VmsGuiiOnAppLanguage);


         //::user::interaction_ptr_array & frames();


         //         virtual bool initialize1();
         //virtual bool initialize();

         virtual int32_t exit_instance();

      // Load MRU file list and last preview state.
      void LoadStdProfileSettings(UINT nMaxMRU = ___MRU_COUNT);


      //         string message_box(const char * pszMatter, property_set & propertyset);


      // Running Operations - to be done on a running user
      // Dealing with document templates
      //         void add_document_template(sp(impact_system) ptemplate);
      ::count get_template_count() const;
      sp(impact_system) get_template(index index) const;


      //       virtual bool set_keyboard_layout(const char * pszPath, ::action::context actioncontext);
      //         virtual void on_set_keyboard_layout(const char * pszPath, ::action::context actioncontext);






      // Running Operations - to be done on a running user
      // Dealing with document templates
      /*   void add_document_template(sp(impact_system) ptemplate);
      POSITION get_template_count() const;
      sp(impact_system) get_template(POSITION& pos) const;

      // open named file, trying to match a regsitered
      // document template to it.
      virtual sp(::user::object) open_document_file(var var);

      // add a string to the recent file list. remove oldest string,
      // if no space left.
      virtual void AddToRecentFileList(const char * lpszPathName);

      // Printer DC Setup routine, 'struct tagPD' is a PRINTDLG structure.
      void SelectPrinter(HANDLE hDevNames, HANDLE hDevMode,
      bool bFreeOld = TRUE);


      // create a DC for the system default printer.
      bool CreatePrinterDC(::draw2d::graphics_sp& spgraphics);


      bool GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg);

      // Finds number of opened document items owned by templates
      // registered with the doc manager.
      int32_t get_open_document_count();

      // helpers for standard commdlg dialogs
      bool do_prompt_file_name(var & varFile, UINT nIDSTitle,
      uint32_t lFlags, bool bOpenFileDialog, sp(impact_system) ptemplate);
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



      sp(::form_document)   create_form(::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var = ::var(::var::type_empty_argument));
      sp(::form_document)   create_form(sp(form_view) pview, ::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var = ::var(::var::type_empty_argument));
      sp(::form_document)   create_child_form(::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var = ::var(::var::type_empty_argument));
      sp(::form_document)   create_child_form(sp(form_view) pview, ::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var = ::var(::var::type_empty_argument));
      sp(::user::object) hold(sp(::user::interaction) pui);

   };


   CLASS_DECL_CORE::user::front_end_schema * GetUfeSchema(sp(::base::application) papp);
   CLASS_DECL_CORE::user::front_end * GetUfe(sp(::base::application) papp);


} // namespace core


