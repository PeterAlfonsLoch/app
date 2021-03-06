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

      virtual bool _001IsEditing();

      virtual bool _001IsPointInside(sp(control) pcontrol,point64 ptt);

      virtual void _001HideEditingControls();
      virtual void _001HideControl(sp(control) pcontrol);
      virtual void _001OnDraw(::draw2d::graphics * pgraphics);
      virtual LRESULT _001BaseWndGetProperty(EProperty eprop,LPARAM lparam);
      void _001UpdateColumns();
      sp(control) _001GetEditControl();
      void _001SetEditControl(sp(control) pcontrol);
      virtual void _001PlaceControl(sp(control) pcontrol, index iEditItem, bool bClick = false, bool bOnlySizeAndPosition = false) override;
      virtual void _001OnShowControl(sp(control) pcontrol);
      sp(control) _001GetControl(index iItem, index iSubItem) override;
      virtual bool _001OnClick(uint_ptr uiFlags,point point);
      virtual bool _001OnClick(uint_ptr uiFlags,point point,index iItem,index iSubItem);
      virtual bool _001OnRightClick(uint_ptr uiFlags, point point);
      virtual bool _001OnRightClick(uint_ptr uiFlags, point point, index iItem, index iSubItem);
      void _001OnTimer(::timer * ptimer);

      using list::_001GetSelection;
      virtual void _001GetSelection(::database::id & key,::database::selection & selection);

      DECL_GEN_SIGNAL(_001OnNotify);
      DECL_GEN_SIGNAL(_001OnMessageNotify);

      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);
      DECL_GEN_SIGNAL(_001OnKeyDown);

      virtual bool _001OnUpdateItemCount(uint32_t dwFlags = 0) override;

      virtual void _001UpdateComboBox(sp(control) pcontrol) override;

      virtual void _001UpdateEdit(sp(control) pcontrol) override;
      virtual bool _001SaveEdit(sp(control) pcontrol) override;

      virtual bool _001OnMouseActivate(::window_sp pDesktopWnd,UINT nHitTest,UINT message,LRESULT & iResult);


      virtual void install_message_handling(::message::dispatch *pinterface);

      bool BaseOnControlEvent(::user::control_event * pevent);

      virtual void _001OnColumnChange();


      virtual void _001DrawChildren(::draw2d::graphics * pgraphics);


      virtual bool _001UpperEditableControl(int & iItem, int & iSubItem);
      virtual bool _001PreviousEditableControl(int & iItem, int & iSubItem);
      virtual bool _001NextEditableControl(int & iItem, int & iSubItem);
      virtual bool _001LowerEditableControl(int & iItem, int & iSubItem);

      //virtual void _001DrawSubItem(draw_list_item * pdrawitem);

      virtual ::check::e_check _001GetSubItemCheck(index iItem, index iSubItem);
      virtual bool _001SetSubItemCheck(index iItem, index iSubItem, ::check::e_check echeck);
      virtual bool _001IsSubItemEnabled(index iItem, index iSubItem);

   };

} // namespace user





