#pragma once


namespace user
{


   namespace uinteraction
   {


      namespace frame
      {

         class WorkSet;
         class control_box_button;

         class CLASS_DECL_CORE appearance :
            public CWorkSetDownUpInterface,
            virtual public signalizable
         {
            friend class WorkSet;
         public:

            appearance(WorkSet * pworkset);
            virtual ~appearance();

            class CTool001 :
               virtual public ::object
            {
            public:

               CTool001(sp(::base::application) papp);

               void Update(::draw2d::graphics * pdc, LPCRECT lpcrect,
                  COLORREF crHighlight,
                  COLORREF crLight,
                  COLORREF crBody,
                  COLORREF crShadow,
                  COLORREF crDkShadow);
               void draw(::draw2d::graphics * pdc);

               class CColorBezier
               {
               public:
                  void draw(::draw2d::brush & brush, ::draw2d::graphics * pdc);
                  point_array m_pointset;
                  ::draw2d::pen  *   m_ppen;
                  void clear();
               };
            public:
               ::draw2d::pen_sp      m_penHighlight;
               ::draw2d::pen_sp      m_penLight;
               ::draw2d::pen_sp      m_penShadow;
               ::draw2d::pen_sp      m_penDkShadow;
               ::draw2d::brush_sp      m_brushNull;
               ::draw2d::brush_sp      m_brushBody;

               point_array m_pointsetBody;
               array < CColorBezier, CColorBezier & > m_colorbezieraOutsideBorder;
            };

            CWorkSetDownUpInterface   *         m_pwndframeworkdownupinterface;
            bool                                m_fActive;
            bool                                m_bUseNc;

            WorkSet *                           m_pworkset;
            bool                                m_bEnabled;
            ::user::EAppearance                 m_emode;
            EAppearanceTransparency             m_nTransparency;
            CTool001 *                    m_ptool001;

            ::visual::icon *              m_picon;

            bool IsNotifyIconEnabled();
            sp(::user::interaction) get_window();



            void UpdateAppearance(bool bFullScreen);
            void SetDownUpInterface(CWorkSetDownUpInterface * pinterface);
            bool WndFrameworkDownUpGetDownEnable();
            virtual bool WndFrameworkDownUpGetUpEnable();
            ::user::EAppearance GetAppearance();
            bool update();
            bool IsIconic();
            bool IsFullScreen();
            bool IsZoomed();
            bool IsEnabled();
            void Enable(bool bEnable);

            void SetTransparency(EAppearanceTransparency nTransparency);
            void SetAppearance(::user::EAppearance nMode);
            void SetAppearance();

            EHitTest hit_test(point pt);

            virtual void frame_Attach();
            virtual void frame_Detach();

            virtual sp(control_box_button) get_box_button(e_button ebutton);

         };


      } // namespace frame


   } // namespace uinteraction


} // namespace user




