#pragma once


namespace user
{


   class CLASS_DECL_CORE form_mesh:
      virtual public ::user::form,
      virtual public ::user::mesh
   {
   public:


      class CLASS_DECL_CORE control_keep
      {
      public:
         inline control_keep(form_mesh * pformmesh,index iNewItem,index iNewSubItem)
         {
            m_pformmesh                      = pformmesh;
            m_iItem                          = pformmesh->m_iControlItem;
            m_iSubItem                       = pformmesh->m_iControlSubItem;
            pformmesh->m_iControlItem        = iNewItem;
            pformmesh->m_iControlSubItem     = iNewSubItem;
         }
         inline control_keep(form_mesh * pformmesh,point pt)
         {
            m_pformmesh                      = pformmesh;
            m_iItem                          = pformmesh->m_iControlItem;
            m_iSubItem                       = pformmesh->m_iControlSubItem;
            pformmesh->control_001DisplayHitTest(pt);
         }
         inline ~control_keep()
         {
            m_pformmesh->m_iControlItem      = m_iItem;
            m_pformmesh->m_iControlSubItem   = m_iSubItem;
         }
         form_mesh *             m_pformmesh;
         index                   m_iItem;
         index                   m_iSubItem;
      };


      sp(control)       m_pcontrolEdit;

      ::count           m_iOnClickClickCount;
      index             m_iOnClickClickItem;
      index             m_iOnClickClickSubItem;

      index             m_iControlItem;
      index             m_iControlSubItem;


      form_mesh();
      virtual ~form_mesh();


      void _001OnDraw(::draw2d::dib * pdib);

      virtual void _001DrawSubItem(draw_mesh_item * pdrawitem);

      void _000OnMouse(::message::mouse * pmouse);


      virtual bool _001HitTest_(point point,index &iItem,index &iSubItem);

      void control_get_client_rect(sp(control) pcontrol,LPRECT lprect);
      void control_get_window_rect(sp(control) pcontrol,LPRECT lprect);
      bool control_001DisplayHitTest(POINT pt);

      bool _001IsEditing();

      virtual bool _001IsPointInside(sp(control) pcontrol,point64 ptt);

      void _001HideEditingControls();
      void _001HideControl(sp(control) pcontrol);
      //virtual void _001OnDraw(::draw2d::dib * pdib);
      virtual LRESULT _001BaseWndGetProperty(EProperty eprop,LPARAM lparam);
      ;;void _001UpdateColumns();
      sp(control) _001GetEditControl();
      void _001SetEditControl(sp(control) pcontrol);
      virtual void _001PlaceControl(sp(control) pcontrol);
      virtual sp(control) _001GetControl(index iItem, index iSubItem);
      virtual void _001OnClick(uint_ptr uiFlags,point point);
      virtual void _001OnClick(uint_ptr uiFlags,point point,index iItem,index iSubItem);
      void _001OnTimer(::timer * ptimer);

      virtual void _001GetSelection(::database::id & key,::database::selection & selection);

      DECL_GEN_SIGNAL(_001OnNotify);
      DECL_GEN_SIGNAL(_001OnMessageNotify);

      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);
      DECL_GEN_SIGNAL(_001OnKeyDown);

      virtual bool _001OnMouseActivate(::window_sp pDesktopWnd,UINT nHitTest,UINT message,LRESULT & iResult);


      virtual void install_message_handling(::message::dispatch *pinterface);

      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      virtual bool _001OnControlSetFocus(::user::interaction * pui);

      virtual bool _001OnControlKillFocus(::user::interaction * pui);

      virtual bool _001OnSetItemText(::user::interaction * pui,index iItem,index iSubItem);


   };


} // namespace user








