#pragma once

namespace userbase
{

   class menu_item;


   class CLASS_DECL_ca menu_list_window :
      virtual public ::user::control,
      virtual public menu_base
   {
   public:

      enum EChildId
      {
         ChildIdClose = 0x00800000
      };

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      menu_list_window(::ca::application * papp);
      menu_list_window(::ca::application * papp, menu_item * pitem);
      virtual ~menu_list_window();

      void layout();

      bool TrackPopupMenu(::user::interaction * pwndParent, ::user::interaction * pwndNotify);

      bool MenuFill(::user::interaction * pwndFill, ::user::interaction * pwndNotify);

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnTimer)

      void _001OnDraw(::ca::graphics *pdc);

      bool BaseOnControlEvent(::user::control_event * pevent);

      UINT m_uiMessage;
      bool m_bAutoClose;

      bool _TrackPopupMenu(::user::interaction * pwndParent, ::user::interaction * pwndNotify);
      void _CreateButtons(menu_item * pitem);
      void _UpdateCmdUi(menu_item * pitem);
      void _CalcSize(menu_item * pitem, ::ca::graphics * pdc, int & iMaxWidth, int & iMaxHeight);
      void _LayoutButtons(menu_item * pitem, int iMaxWidth, LPRECT lprect, LPCRECT lpcrectBound);
      ::user::interaction *                 m_pwndNotify;
      //menu_list_window *           _m_pmenu;
      bool                             m_bAutoDelete;
      ::user::front_end_schema::menu *   m_pschema;
      bool                             m_bOwnItem;
      button                m_buttonClose;
      int                              m_iHeaderHeight;
      int                              m_iItemHeight;
      size                             m_size;

   };


} // namespace userbase