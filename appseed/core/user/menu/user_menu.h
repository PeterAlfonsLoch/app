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


      ::user::interaction *      m_oswindowParent;
      menu *                     m_pmenuParent;
      HMENU                      m_hmenu;
      //menu *                     _m_pmenu;
      bool                       m_bOwnItem;
      size                       m_size;
      int32_t                    m_iItemHeight;
      bool                       m_bAutoDelete;
      int32_t                    m_iHeaderHeight;
      ::user::button             m_buttonClose;
      id                         m_idSubMenu;
      int32_t                    m_iHoverSubMenu;
      uint32_t                   m_dwOut;
      sp(menu)                     m_psubmenu;
      id                         m_idTimerMenu;
      point                      m_ptTrack;
      ::user::interaction *      m_puiNotify;


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

      ::user::menu_item * GetSubMenu(int32_t i);

      void layout_menu(point pt);

      DECL_GEN_SIGNAL(_001OnLButtonDown);

      void _001OnDraw(::draw2d::dib * pdib);
      DECL_GEN_SIGNAL(OnMessageDestroyWindow);


      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      void _001OnTimer(::timer * ptimer);
      DECL_GEN_SIGNAL(_001OnIdleUpdateCmdUI);
      DECL_GEN_SIGNAL(_001OnNcActivate);
      DECL_GEN_SIGNAL(_001OnNcCalcSize);
      DECL_GEN_SIGNAL(_001OnEnable);

      virtual bool TrackPopupMenu(int32_t iFlags, POINT pt, ::user::interaction * oswindowParent) override;
      virtual bool _TrackPopupMenu(int32_t iFlags, POINT pt, sp(::user::interaction) oswindowParent, menu * pmenuParent);
      /*DECL_GEN_SIGNAL(OnMouseProc);*/
      bool pre_create_window(::user::create_struct& cs);
      //virtual void PostNcDestroy();
      ::user::front_end_schema::menu  * m_pschema;
      virtual void install_message_handling(::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(_001OnShowWindow);


      sp(::user::menu_item) get_item();

      sp(::user::menu_item) get_item(::user::interaction * pui);


      virtual bool get_color(COLORREF & cr,::user::e_color ecolor);

      virtual bool get_translucency(::user::ETranslucency & etranslucency);

   };


} // namespace user




