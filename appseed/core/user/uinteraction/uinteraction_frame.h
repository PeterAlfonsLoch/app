#pragma once


namespace user
{


   class front_end_schema;


} // namespace user


namespace uinteraction
{


   namespace frame
   {


      // implemented in core
      class WorkSet;
      class control_box;

      enum EHitTest
      {
         HitTestNone,
         HitTestClient,
         HitTestSizingLeft,
         HitTestSizingTopLeft,
         HitTestSizingTop,
         HitTestSizingTopRight,
         HitTestSizingRight,
         HitTestSizingBottomRight,
         HitTestSizingBottom,
         HitTestSizingBottomLeft,
         HitTestMove,
      };



      class CLASS_DECL_CORE frame : 
         virtual public signalizable,
         virtual public ::object
      {
      public:


         enum e_button
         {
            button_none,
            button_close,
            button_up,
            button_down,
            button_minimize,
            button_restore,
            button_maximize,
            button_notify_icon,
         };



         sp(type)                                      m_typeinfoControlBoxButton;
         sp(type)                                      m_typeinfoControlBox;


         map < e_button, e_button, id, id >            m_mapButtonId;
         map < id, id, e_button, e_button >            m_mapIdButton;
         map < e_button, e_button, bool, bool >        m_buttonmapPresent;


         WorkSet *                                                   m_pworkset;




         frame(sp(base_application) papp);
         virtual ~frame();


         virtual ::user::front_end_schema * get_user_front_end_schema();

         virtual void set_style(const char * pszStyle);
         virtual void OnInitializeAppearance();
         virtual void OnAppearanceModeChange();
         virtual int32_t UpdateControlBox();

         virtual sp(::uinteraction::frame::control_box) get_control_box() = 0;

         virtual void SetControlBoxButtonId(e_button ebutton, id id);
         virtual id GetControlId(e_button ebutton);
         virtual e_button GetButtonId(id id);

         virtual void hide_button(e_button ebutton, bool bHide = true);
         virtual bool has_button(e_button ebutton);



         virtual void OnMove(sp(::user::interaction) pwnd);


         virtual void _001OnDraw(::draw2d::graphics * pca);

         virtual void GetWndClientRect(LPRECT lprect);
         virtual size GetMinSize();

         virtual void OnActivate();
         virtual void OnNcCalcSize(LPRECT lprect);
         virtual void _000OnBeforeSize(LPCRECT lpcrectWindow);
         virtual void layout();


         virtual COLORREF get_border_main_body_color();

         virtual EHitTest _000HitTest(point pt) = 0;
         virtual bool _000OnLButtonDown(::message::mouse * pmouse);
         virtual bool _000OnLButtonUp(::message::mouse * pmouse);
         virtual bool _000OnMouseMove(::message::mouse * pmouse);
         virtual bool _000OnNcLButtonDown(::message::mouse * pmouse);
         virtual bool _000OnNcLButtonUp(::message::mouse * pmouse);
         virtual bool _000OnNcMouseMove(::message::mouse * pmouse);
         virtual bool _000OnNcHitTest(point pt, LRESULT & nHitTest);
         virtual bool _000OnTimer(UINT nIDEvent);
         virtual bool _000OnSize(UINT nType, int32_t cx, int32_t cy);
         virtual bool _000OnMove(int32_t x, int32_t y);
         virtual bool _000OnCommand(WPARAM wparam, LPARAM lparam, LRESULT & lresult);

      virtual void OnAttach();

      };

   } // namespace frame


} // namespace frame




