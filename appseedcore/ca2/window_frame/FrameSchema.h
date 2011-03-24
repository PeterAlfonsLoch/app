#pragma once

namespace window_frame
{

   class appearance;
   class WorkSet;

   class CLASS_DECL_ca FrameSchema : 
      virtual public gen::signalizable,
      virtual public ::radix::object
   {
   public:

      enum EButton
      {
         ButtonNone,
         ButtonClose,
         ButtonUp,
         ButtonDown,
         ButtonMinimize,
         ButtonRestore,
         ButtonMaximize,
         ButtonNotifyIcon,
      };

   /*
      class CLASS_DECL_ca ButtonIdSpace :
         public BaseIdSpaceHolder
      {
      public:
         ButtonIdSpace();
      };
   */

      virtual void OnMove(::user::interaction * pwnd);
      virtual void SetControlBoxButtonId(EButton ebutton, id id);
      virtual id GetControlId(EButton ebutton);
      virtual EButton GetButtonId(id id);

      virtual int UpdateControlBox() = 0;

      virtual void OnAttach();
      virtual void _000OnBeforeMove(LPCRECT lpcrectWindow);
      virtual void _000OnBeforeSize(LPCRECT lpcrectWindow);
      virtual void layout();
      virtual void OnActivate();
      size GetMinSize();
      virtual void GetWndClientRect(LPRECT lprect);
      appearance * GetAppearance();
      virtual bool _000OnDisplayChange(int iBitsPerPixel, size sizeScreen);
      virtual void OnInitializeAppearance();
      virtual void OnNcCalcSize(LPRECT lprect);
      virtual void OnAppearanceModeChange();
      DECL_GEN_VSIGNAL(_000OnDraw)
      DECL_GEN_VSIGNAL(_000OnNcDraw);
      FrameSchema(::ca::application * papp);
      virtual ~FrameSchema();


      virtual void Glass(::ca::graphics * pdc, LPRECT lprect);
      virtual void ColorGlass(::ca::graphics * pdc, LPRECT lprect, COLORREF cr, BYTE bAlpha);

      WorkSet *      m_pworkset;

      ::collection::map < EButton, EButton, id, id > m_mapButtonId;
      ::collection::map < id, id, EButton, EButton > m_mapIdButton;

      // point should be in screen coordinates

      virtual EHitTest _000HitTest(point pt) = 0;
      virtual bool _000OnLButtonDown(::user::win::message::mouse * pmouse);
      virtual bool _000OnLButtonUp(::user::win::message::mouse * pmouse);
      virtual bool _000OnMouseMove(::user::win::message::mouse * pmouse);
      virtual bool _000OnNcLButtonDown(::user::win::message::mouse * pmouse);
      virtual bool _000OnNcLButtonUp(::user::win::message::mouse * pmouse);
      virtual bool _000OnNcMouseMove(::user::win::message::mouse * pmouse);
      virtual bool _000OnNcHitTest(point pt, LRESULT & nHitTest);
      virtual bool _000OnTimer(UINT nIDEvent);
      virtual bool _000OnSize(UINT nType, int cx, int cy);
      virtual bool _000OnMove(int x, int y);
      virtual bool _000OnCommand(WPARAM wparam, LPARAM lparam, LRESULT & lresult);

   };

} // namespace window_frame
