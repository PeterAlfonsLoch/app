#pragma once


namespace user
{


   class CLASS_DECL_CORE form_list:
      virtual public ::user::form_mesh,
      virtual public ::user::list
   {
   public:




      form_list();
      virtual ~form_list();


      virtual void _001DrawSubItem(draw_list_item * pdrawitem);

      using ::user::list::_001HitTest_;
      virtual bool _001HitTest_(point point,index &iItem,index &iSubItem);

      void _000OnMouse(::message::mouse * pmouse);

      void control_get_client_rect(sp(control) pcontrol,LPRECT lprect);
      void control_get_window_rect(sp(control) pcontrol,LPRECT lprect);
      bool control_001DisplayHitTest(POINT pt);

      bool _001IsEditing();

      virtual bool _001IsPointInside(sp(control) pcontrol,point64 ptt);

      void _001HideEditingControls();
      void _001HideControl(sp(control) pcontrol);
      virtual void _001OnDraw(::draw2d::graphics * pdc);
      virtual LRESULT _001BaseWndGetProperty(EProperty eprop,LPARAM lparam);
      void _001UpdateColumns();
      sp(control) _001GetEditControl();
      void _001SetEditControl(sp(control) pcontrol);
      virtual void _001PlaceControl(sp(control) pcontrol);
      sp(control) _001GetControlBySubItem(index iSubItem);
      virtual void _001OnClick(uint_ptr uiFlags,point point);
      virtual void _001OnClick(uint_ptr uiFlags,point point,index iItem,index iSubItem);
      void _001OnTimer(::timer * ptimer);

      using list::_001GetSelection;
      virtual void _001GetSelection(::database::id & key,::database::selection & selection);

      DECL_GEN_SIGNAL(_001OnNotify);
      DECL_GEN_SIGNAL(_001OnMessageNotify);

      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);
      DECL_GEN_SIGNAL(_001OnKeyDown);

      virtual bool _001OnMouseActivate(::window_sp pDesktopWnd,UINT nHitTest,UINT message,LRESULT & iResult);


      virtual void install_message_handling(::message::dispatch *pinterface);

      bool BaseOnControlEvent(::user::control_event * pevent);

      virtual void _001OnColumnChange();


   };

} // namespace user





