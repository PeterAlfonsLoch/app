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

      UINT                                m_uiMessage;
      bool                                m_bAutoClose;
      ::user::interaction *               m_pwndNotify;
      bool                                m_bAutoDelete;
      ::user::front_end_schema::menu *    m_pschema;
      bool                                m_bOwnItem;
      button                              m_buttonClose;
      int                                 m_iHeaderHeight;
      int                                 m_iItemHeight;
      size                                m_size;

      menu_list_window(::ax::application * papp);
      menu_list_window(::ax::application * papp, menu_item * pitem);
      virtual ~menu_list_window();

      void layout();

      virtual void install_message_handling(::gen::message::dispatch * pinterface);


      virtual void clear();

      bool TrackPopupMenu(::user::interaction * pwndParent, ::user::interaction * pwndNotify);

      bool MenuFill(::user::interaction * pwndFill, ::user::interaction * pwndNotify);

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnTimer)

      void _001OnDraw(::ax::graphics *pdc);

      bool BaseOnControlEvent(::user::control_event * pevent);


      bool _TrackPopupMenu(::user::interaction * pwndParent, ::user::interaction * pwndNotify);
      void _CreateButtons(menu_item * pitem);
      void _UpdateCmdUi(menu_item * pitem);
      void _CalcSize(menu_item * pitem, ::ax::graphics * pdc, int & iMaxWidth, int & iMaxHeight);
      void _LayoutButtons(menu_item * pitem, int iMaxWidth, LPRECT lprect, LPCRECT lpcrectBound);

   };


} // namespace userbase