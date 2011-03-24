#pragma once

namespace user
{

   class CLASS_DECL_ca form_list :
      virtual public ::user::form,
      virtual public ::user::list
   {
   protected:
      control * m_pcontrolEdit;

      count         m_iOnClickClickCount;
      index         m_iOnClickClickItem;
      index         m_iOnClickClickSubItem;

   public:
      index         m_iControlItem;
      index         m_iControlSubItem;

      class CLASS_DECL_ca control_keep
      {
      public:
         inline control_keep(form_list * pformlist, index iNewItem, index iNewSubItem)
         {
            m_pformlist                      = pformlist;
            m_iItem                          = pformlist->m_iControlItem; 
            m_iSubItem                       = pformlist->m_iControlSubItem;
            pformlist->m_iControlItem        = iNewItem;
            pformlist->m_iControlSubItem     = iNewSubItem;
         }
         inline control_keep(form_list * pformlist, point pt)
         {
            m_pformlist                      = pformlist;
            m_iItem                          = pformlist->m_iControlItem; 
            m_iSubItem                       = pformlist->m_iControlSubItem;
            pformlist->control_001DisplayHitTest(pt); 
         }
         inline ~control_keep()
         {
            m_pformlist->m_iControlItem      = m_iItem;
            m_pformlist->m_iControlSubItem   = m_iSubItem;
         }
         form_list *    m_pformlist;
         index            m_iItem;
         index            m_iSubItem;
      };

      void _001DrawSubItem(
         ::ca::graphics * pdc,
         draw_item * pdrawitem,
         LPCRECT lpcrect,
         index iSubItem,
         bool bItemHover,
         bool bSubItemHover,
         bool bFocus);

      void _000OnMouse(::user::win::message::mouse * pmouse);

      void control_get_client_rect(LPRECT lprect);
      void control_get_window_rect(LPRECT lprect);
      bool control_001DisplayHitTest(POINT pt);

      bool _001IsEditing();

      virtual bool _001IsPointInside(control * pcontrol, point64 ptt);

      void _001HideEditingControls();
      void _001HideControl(control * pcontrol);
      virtual void _001OnDraw(::ca::graphics * pdc);
      virtual LRESULT _001BaseWndGetProperty(EProperty eprop, LPARAM lparam);
      virtual ::user::interaction* _GetWnd();
      void _001UpdateColumns();
      control * _001GetEditControl();
      void _001SetEditControl(control * pcontrol);
      virtual void OnDrawInterfaceDraw(::ca::graphics *pdc);
      virtual void _001PlaceControl(control * pcontrol);
      control * _001GetControlBySubItem(index iSubItem);
      virtual void _001OnClick(UINT uiFlags, point point);
      virtual void _001OnClick(UINT uiFlags, point point, index iItem, index iSubItem);
      DECL_GEN_VSIGNAL(_001OnTimer)

#if !core_level_1
      using list::_001GetSelection;
#endif
      virtual void _001GetSelection(::database::id & key, ::database::selection & selection);
      form_list(::ca::application * papp);
      virtual ~form_list();

      bool _001OnNotify(WPARAM wparam, LPARAM lparam, LRESULT & lresult);
      virtual bool _001OnMessageNotify(WPARAM wparam, LPARAM lparam, LRESULT & lresult);

      DECL_GEN_SIGNAL(_001OnVScroll)
      DECL_GEN_SIGNAL(_001OnHScroll)
      DECL_GEN_SIGNAL(_001OnKeyDown)

      virtual bool _001OnMouseActivate(::ca::window* pDesktopWnd, UINT nHitTest, UINT message, LRESULT & iResult);


      virtual void _001InstallMessageHandling( ::user::win::message::dispatch *pinterface);

      bool BaseOnControlEvent(::user::control_event * pevent);
   };

} // namespace user