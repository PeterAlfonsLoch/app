#pragma once


namespace user
{


   namespace uinteraction
   {


      namespace frame
      {


         class CLASS_DECL_CORE frame :
            virtual public signalizable,
            virtual public ::object
         {
         public:


            rect                                         m_rectCaption;
            rect                                         m_rectCaptionTextBk;
            rect                                         m_rectWindowText;
            rect                                         m_rectControlBoxFullScreen;
            rect                                         m_rectControlBoxZoomed;
            rect                                         m_rectControlBoxNormal;
            point                                        m_pointWindowIcon;



            sp(type)                                     m_typeinfoControlBoxButton;
            sp(type)                                     m_typeinfoControlBox;




            WorkSet *                                    m_pworkset;

            sp(control_box)                              m_spcontrolbox;

            int32_t                                      m_iCaptionHeight;

            ::rect                                       m_rectControlBoxMarginFullScreen;
            ::rect                                       m_rectControlBoxMarginZoomed;
            ::rect                                       m_rectControlBoxMarginNormal;


            ::rect                                       m_rectMarginFullScreen;
            ::rect                                       m_rectMarginZoomed;
            ::rect                                       m_rectMarginNormal;


            ::rect                                       m_rectClient;
            ::rect                                       m_rectWindow;
            int                                          m_iControlBoxRight;
            bool                                         m_bControlBoxAlignRight;





            frame(sp(::base::application) papp);
            virtual ~frame();


            virtual appearance * get_appearance();

            virtual ::user::front_end_schema * get_user_front_end_schema();

            virtual void set_style(const char * pszStyle);
            virtual void on_initialize_appearance();


            virtual void update_drawing_objects();
            virtual void update_window_client_rect();
            virtual void update_window_region(LPCRECT lpcrectWindow);
            virtual void update_window();
            virtual void update_window_style();


            virtual void get_window_client_rect(LPRECT lprect);
            virtual void get_draw_client_rect(LPRECT lprect);

            virtual void calc_window_client_rect(LPRECT lprect, LPCRECT lprectWindow);


            virtual sp(::user::interaction) get_draw_window();
            virtual sp(::user::interaction) get_window();


            virtual rect * get_control_box_rect();
            virtual rect * get_control_box_margin_rect();
            virtual rect * get_margin_rect();
            virtual int32_t get_caption_height();
            virtual int32_t calc_caption_height();

            virtual int32_t title_bar_layout(bool bInitialControlBoxPosition);

            virtual void reset_layout();


            virtual sp(control_box) get_control_box();


            virtual void OnMove(sp(::user::interaction) pwnd);


            virtual void on_style_change();


            virtual void _001OnDraw(::draw2d::graphics * pca);

            virtual size GetMinSize();

            virtual void OnActivate();
            virtual void OnNcCalcSize(LPRECT lprect);
            virtual void _000OnBeforeSize(LPCRECT lpcrectWindow);
            virtual void layout();


            virtual EHitTest _000HitTest(point pt);


            virtual COLORREF get_border_main_body_color();

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


} // namespace user












