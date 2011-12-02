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


      ::ax::brush_sp                m_brushControlBoxBack;
      ::ax::brush_sp                m_brushControlBoxBackSel;
      ::ax::brush_sp                m_brushControlBoxBackFocus;
      ::ax::brush_sp                m_brushControlBoxBackDisabled;

      ::ax::pen_sp                  m_penControlBoxBack;
      ::ax::pen_sp                  m_penControlBoxBackSel;
      ::ax::pen_sp                  m_penControlBoxBackFocus;
      ::ax::pen_sp                  m_penControlBoxBackDisabled;
      
      COLORREF                      m_crControlBoxFore;
      COLORREF                      m_crControlBoxForeSel;
      COLORREF                      m_crControlBoxForeFocus;
      COLORREF                      m_crControlBoxForeDisabled;

      ::ax::dibmap                  m_dibmap;

      ::ax::font_sp                 m_fontMarlett;

      ::user::front_end_schema      m_schema;

      ::ax::type_info                                                                     m_typeinfoControlBoxButton;


      ::collection::map < EButton, EButton, ControlBoxButton *, ControlBoxButton * >      m_buttonmap;

      WorkSet *                                                                           m_pworkset;

      ::collection::map < EButton, EButton, id, id >                                      m_mapButtonId;
      ::collection::map < id, id, EButton, EButton >                                      m_mapIdButton;

      ::collection::map < EButton, EButton, bool, bool >                                  m_buttonmapPresent;


      FrameSchema(::ax::application * papp);
      virtual ~FrameSchema();


      virtual COLORREF get_border_main_body_color();


      virtual void OnMove(::user::interaction * pwnd);
      virtual void SetControlBoxButtonId(EButton ebutton, id id);
      virtual id GetControlId(EButton ebutton);
      virtual EButton GetButtonId(id id);

      virtual ControlBoxButton * get_button(EButton ebutton);
      virtual bool create_button(EButton ebutton);
      virtual bool GetControlBoxButtonCaption(EButton ebutton, string & str);
      virtual bool CreateButtons();
      virtual int UpdateControlBox();
      virtual void UpdateControlBoxButton(EButton ebutton);
      virtual void UpdateControlBoxButtons();


      virtual bool has_button(EButton ebutton);
      virtual void hide_button(EButton ebutton, bool bHide = true);

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
      
      
      virtual void _001OnDraw(::ax::graphics * pca);


      virtual void Glass(::ax::graphics * pdc, LPRECT lprect);
      virtual void ColorGlass(::ax::graphics * pdc, LPRECT lprect, COLORREF cr, BYTE bAlpha);


      // point should be in screen coordinates

      virtual EHitTest _000HitTest(point pt) = 0;
      virtual bool _000OnLButtonDown(::gen::message::mouse * pmouse);
      virtual bool _000OnLButtonUp(::gen::message::mouse * pmouse);
      virtual bool _000OnMouseMove(::gen::message::mouse * pmouse);
      virtual bool _000OnNcLButtonDown(::gen::message::mouse * pmouse);
      virtual bool _000OnNcLButtonUp(::gen::message::mouse * pmouse);
      virtual bool _000OnNcMouseMove(::gen::message::mouse * pmouse);
      virtual bool _000OnNcHitTest(point pt, LRESULT & nHitTest);
      virtual bool _000OnTimer(UINT nIDEvent);
      virtual bool _000OnSize(UINT nType, int cx, int cy);
      virtual bool _000OnMove(int x, int y);
      virtual bool _000OnCommand(WPARAM wparam, LPARAM lparam, LRESULT & lresult);

   };


} // namespace window_frame


