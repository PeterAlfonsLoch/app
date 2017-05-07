#pragma once


namespace user
{

   class CLASS_DECL_BASE mouse
   {
   public:
      uint_ptr                m_nFlags;
      point                   m_pt;
      point                   m_ptDesired;
      bool                    m_bTranslated;
      ::visual::e_cursor      m_ecursor;
      ::visual::cursor *      m_pcursor;


      virtual unsigned int get_message()
      {
         return 0;
      }

   };


} // namespace user



namespace base
{


   class CLASS_DECL_BASE session:
      virtual public ::axis::session,
      virtual public :: base ::application,
      virtual public ::user::schema
   {
   public:


      ::visual::e_cursor                                       m_ecursor;
      ::visual::cursor *                                       m_pcursor;
      ::visual::e_cursor                                       m_ecursorDefault;


      ::user::user *                m_puser;
      sp(::user::schema)            m_puserschemasimple;
      string_map < sp(::user::schema) >   m_mapSchema;

      ::user::interaction *         m_puiCapture;


      session(::aura::application * papp);
      virtual ~session_parent;

      inline ::user::user *                        user() { return m_puser; }

      virtual void set_cursor(::visual::cursor * pcursor);
      virtual void set_cursor(::visual::e_cursor ecursor);
      virtual void set_default_cursor(::visual::e_cursor ecursor);
      virtual ::visual::cursor * get_cursor();
      virtual ::visual::cursor * get_default_cursor();

      virtual bool on_ui_mouse_message(::user::mouse * pmouse);



      virtual index get_good_restore(LPRECT lprect,const RECT & rect,::user::interaction * pui);
      virtual index get_good_move(LPRECT lprect,const RECT & rect,::user::interaction * pui);
      virtual index get_ui_wkspace(::user::interaction * pui);

      virtual index initial_frame_position(LPRECT lprect,const RECT & rect,bool bMove,::user::interaction * pui);

      virtual void frame_pre_translate_message(signal_details * pobj) override;

      virtual bool process_initialize() override;

      virtual bool initialize1() override;

      virtual bool initialize() override;

      virtual int32_t exit_application() override;

      virtual string fontopus_get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive, ::user::interactive * pinteractive = NULL) override;

      virtual void get_cursor_pos(LPPOINT lppoint) override;

      virtual ::user::primitive * GetActiveWindow();
      virtual ::user::primitive * GetFocus();

      ::user::elemental * get_keyboard_focus() override;
      virtual bool ReleaseCapture();
      virtual sp(::user::interaction) GetCapture();


      sp(::user::schema) create_new_user_schema(const char * pszUinteractionLibrary);

      sp(::user::schema) get_user_schema(const char * pszUinteractionLibrary);


      virtual void on_finally_focus_set(::user::elemental * pelementalFocus) override;


      virtual oswindow get_capture();


      virtual void defer_create_user_schema(const char * pszUiInteractionLibrary = NULL);

      


   };


} // namespace base





































