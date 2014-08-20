#pragma once


namespace user
{


   class CLASS_DECL_CORE form_list :
      virtual public ::user::form,
      virtual public ::user::list
   {
   protected:
      sp(control) m_pcontrolEdit;

      ::count m_iOnClickClickCount;
      index         m_iOnClickClickItem;
      index         m_iOnClickClickSubItem;

   public:
      index         m_iControlItem;
      index         m_iControlSubItem;

      class CLASS_DECL_CORE control_keep
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


      form_list(sp(::axis::application) papp);
      virtual ~form_list();


      virtual void _001DrawSubItem(draw_list_item * pdrawitem);

      void _000OnMouse(::message::mouse * pmouse);

      void control_get_client_rect(sp(control) pcontrol, LPRECT lprect);
      void control_get_window_rect(sp(control) pcontrol, LPRECT lprect);
      bool control_001DisplayHitTest(POINT pt);

      bool _001IsEditing();

      virtual bool _001IsPointInside(sp(control) pcontrol, point64 ptt);

      void _001HideEditingControls();
      void _001HideControl(sp(control) pcontrol);
      virtual void _001OnDraw(::draw2d::graphics * pdc);
      virtual LRESULT _001BaseWndGetProperty(EProperty eprop, LPARAM lparam);
      virtual sp(::user::interaction) _GetWnd();
      void _001UpdateColumns();
      sp(control) _001GetEditControl();
      void _001SetEditControl(sp(control) pcontrol);
      virtual void _001PlaceControl(sp(control) pcontrol);
      sp(control) _001GetControlBySubItem(index iSubItem);
      virtual void _001OnClick(uint_ptr uiFlags, point point);
      virtual void _001OnClick(uint_ptr uiFlags, point point, index iItem, index iSubItem);
      DECL_GEN_VSIGNAL(_001OnTimer);

      using list::_001GetSelection;
      virtual void _001GetSelection(::database::id & key, ::database::selection & selection);

      DECL_GEN_VSIGNAL(_001OnNotify);
      DECL_GEN_VSIGNAL(_001OnMessageNotify);

      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);
      DECL_GEN_SIGNAL(_001OnKeyDown);

      virtual bool _001OnMouseActivate(::window_sp pDesktopWnd, UINT nHitTest, UINT message, LRESULT & iResult);


      virtual void install_message_handling( ::message::dispatch *pinterface);

      bool BaseOnControlEvent(::user::control_event * pevent);

      virtual void _001OnColumnChange();


   };


} // namespace user





