#pragma once


namespace user
{


   class front_end_schema;


} // namespace user


namespace uinteraction
{


   namespace frame
   {


      // implemented in ca2
      class WorkSet;

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



      class CLASS_DECL_ca frame : 
         virtual public gen::signalizable,
         virtual public ::radix::object
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



         ::ca::type_info                                             m_typeinfoControlBoxButton;

         ::collection::map < e_button, e_button, id, id >            m_mapButtonId;
         ::collection::map < id, id, e_button, e_button >            m_mapIdButton;
         ::collection::map < e_button, e_button, bool, bool >        m_buttonmapPresent;


         WorkSet *                                                   m_pworkset;




         frame(::ca::application * papp);
         virtual ~frame();


         virtual ::user::front_end_schema * get_user_front_end_schema();

         virtual void set_style(const char * pszStyle);
         virtual void OnInitializeAppearance();
         virtual void OnAppearanceModeChange();
         virtual int UpdateControlBox();

         virtual void SetControlBoxButtonId(e_button ebutton, id id);
         virtual id GetControlId(e_button ebutton);
         virtual e_button GetButtonId(id id);

         virtual void hide_button(e_button ebutton, bool bHide = true);
         virtual bool has_button(e_button ebutton);



         virtual void OnMove(::user::interaction * pwnd);


         virtual void _001OnDraw(::ca::graphics * pca);

         virtual void GetWndClientRect(LPRECT lprect);
         virtual size GetMinSize();

         virtual void OnActivate();
         virtual void OnNcCalcSize(LPRECT lprect);
         virtual void _000OnBeforeSize(LPCRECT lpcrectWindow);
         virtual void layout();


         virtual COLORREF get_border_main_body_color();

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

      virtual void OnAttach();

      };

   } // namespace frame


} // namespace frame




