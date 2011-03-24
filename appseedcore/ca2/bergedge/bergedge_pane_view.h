#pragma once


namespace bergedge
{

   class CLASS_DECL_ca pane_view : 
      public ::userex::pane_tab_view,
      public FileManagerCallbackInterface,
      public ::bergedge::form_callback
   {
   public:


      form_view *                               m_pformOptions;
      visual::dib_sp                            m_dibBk;
      int                                       m_iNewArea;
      int                                       m_iArea;
      int                                       m_iDisplay;
      filemanager::SimpleFilePropertiesForm *   m_ppropform;
      ::fs::item_array                      m_itema;



      pane_view(::ca::application * papp);
      virtual ~pane_view();

      using ::userbase::tab_view::on_show_view;
      using ::bergedge::form_callback::on_update;

      void rotate();
      
      void on_create_view(view_data * pviewdata);
      void on_show_view();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      void check_3click_dir(const char * psz);
      void check_menu_dir(const char * psz);
      void check_desktop_dir(const char * psz);

      void _001InitializeFormPreData(::user::form * pform);
      bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);
      
   /*   virtual void OnFileManagerOpenContextMenuFolder(
         ::filemanager::data * pdata, 
         ::fs::item & item);*/
      virtual void OnFileManagerOpenContextMenuFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);
      virtual void OnFileManagerOpenContextMenu(::filemanager::data * pdata);

      void _001OnDraw(::ca::graphics * pdc);

      virtual void set_display(int iDisplay);

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnMenuMessage)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnRButtonUp)
      DECL_GEN_SIGNAL(_001OnProperties)

   };


} // namespace windesk

