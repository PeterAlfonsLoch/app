#pragma once


namespace user
{


   class CLASS_DECL_CORE menu : 
      virtual public ::user::control,
      virtual public menu_base
   {
   public:


      enum e_message
      {

         MessageDestroyWindow = WM_USER + 128

      };

      enum EChildId
      {
         ChildIdClose = 0x00800000
      };


      ::user::interaction *                  m_oswindowParent;
      menu *                                 m_pmenuParent;
      HMENU                                  m_hmenu;
      //menu *                                 _m_pmenu;
      bool                                   m_bOwnItem;
      size                                   m_size;
      int32_t                                m_iItemHeight;
      int32_t                                m_iCheckBoxSize;
      bool                                   m_bAutoDelete;
      int32_t                                m_iHeaderHeight;
      ::user::button                         m_buttonClose;
      id                                     m_idSubMenu;
      int32_t                                m_iHoverSubMenu;
      uint32_t                               m_dwOut;
      sp(menu)                                 m_psubmenu;
      id                                     m_idTimerMenu;
      point                                  m_ptTrack;
      ::user::interaction *                  m_puiNotify;
      ::user::front_end_schema::menu  *      m_pschema;
      


      menu();
      menu(::aura::application * papp);
      menu(::aura::application * papp, sp(::user::menu_item) pitem);
      virtual ~menu();


      virtual int64_t add_ref()
      {

         return ::object::add_ref();

      }

      virtual int64_t dec_ref()
      {

         return ::object::dec_ref();

      }

      virtual ::user::interaction * get_target_window();

      ::user::menu_item * GetSubMenu(int32_t i);

      void layout_menu(point pt);


      virtual bool TrackPopupMenu(int32_t iFlags, POINT pt, ::user::interaction * oswindowParent) override;
      virtual bool _TrackPopupMenu(int32_t iFlags, POINT pt, sp(::user::interaction) oswindowParent, menu * pmenuParent);

      void _001OnTimer(::timer * ptimer);
      void _001OnDraw(::draw2d::graphics * pgraphics);

      DECL_GEN_SIGNAL(OnMessageDestroyWindow);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnIdleUpdateCmdUI);
      DECL_GEN_SIGNAL(_001OnNcActivate);
      DECL_GEN_SIGNAL(_001OnNcCalcSize);
      DECL_GEN_SIGNAL(_001OnEnable);
      DECL_GEN_SIGNAL(_001OnShowWindow);


      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      /*DECL_GEN_SIGNAL(OnMouseProc);*/
      bool pre_create_window(::user::create_struct& cs);
      //virtual void PostNcDestroy();
      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual bool get_font(::draw2d::font_sp & spfont) override;

      sp(::user::menu_item) get_item();

      sp(::user::menu_item) get_item(::user::interaction * pui);


      virtual bool get_color(COLORREF & cr,::user::e_color ecolor);

      virtual bool get_translucency(::user::ETranslucency & etranslucency);

      virtual bool has_pending_graphical_update();


   };


} // namespace user




