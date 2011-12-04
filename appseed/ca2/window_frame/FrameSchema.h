#pragma once


namespace window_frame
{

   class appearance;
   class WorkSet;

   class CLASS_DECL_ca2 FrameSchema : 
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


      ::ca::brush_sp                m_brushControlBoxBack;
      ::ca::brush_sp                m_brushControlBoxBackSel;
      ::ca::brush_sp                m_brushControlBoxBackFocus;
      ::ca::brush_sp                m_brushControlBoxBackDisabled;

      ::ca::pen_sp                  m_penControlBoxBack;
      ::ca::pen_sp                  m_penControlBoxBackSel;
      ::ca::pen_sp                  m_penControlBoxBackFocus;
      ::ca::pen_sp                  m_penControlBoxBackDisabled;
      
      COLORREF                      m_crControlBoxFore;
      COLORREF                      m_crControlBoxForeSel;
      COLORREF                      m_crControlBoxForeFocus;
      COLORREF                      m_crControlBoxForeDisabled;

      ::ca::dibmap                  m_dibmap;

      ::ca::font_sp                 m_fontMarlett;

      ::user::front_end_schema      m_schema;

      ::ca::type_info                                                                     m_typeinfoControlBoxButton;


      ::collection::map < EButton, EButton, ControlBoxButton *, ControlBoxButton * >      m_buttonmap;

      WorkSet *                                                                           m_pworkset;

      ::collection::map < EButton, EButton, id, id >                                      m_mapButtonId;
      ::collection::map < id, id, EButton, EButton >                                      m_mapIdButton;

      ::collection::map < EButton, EButton, bool, bool >                                  m_buttonmapPresent;


      FrameSchema(::ca::application * papp);
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
      
      
      virtual void _001OnDraw(::ca::graphics * pca);


      virtual void Glass(::ca::graphics * pdc, LPRECT lprect);
      virtual void ColorGlass(::ca::graphics * pdc, LPRECT lprect, COLORREF cr, BYTE bAlpha);


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


