#pragma once



namespace uinteraction
{


   namespace frame
   {

      class WorkSet;
      class ControlBoxButton;

      class CLASS_DECL_ca2 appearance :
         public CWorkSetDownUpInterface,
         virtual public ::ca2::signalizable
      {
         friend class WorkSet;
      public:

         appearance(WorkSet * pworkset);
         virtual ~appearance();

         class CTool001 :
            virtual public ::ca2::object
         {
         public:

            CTool001(sp(::ca2::application) papp);

            void Update(::ca2::graphics * pdc, LPCRECT lpcrect,
               COLORREF crHighlight,
               COLORREF crLight,
               COLORREF crBody,
               COLORREF crShadow,
               COLORREF crDkShadow);
            void draw(::ca2::graphics * pdc);

            class CColorBezier
            {
            public:
               void draw(::ca2::brush & brush, ::ca2::graphics * pdc);
               point_array m_pointset;
               ::ca2::pen  *   m_ppen;
               void clear();
            };
         public:
            ::ca2::pen_sp      m_penHighlight;
            ::ca2::pen_sp      m_penLight;
            ::ca2::pen_sp      m_penShadow;
            ::ca2::pen_sp      m_penDkShadow;
            ::ca2::brush_sp      m_brushNull;
            ::ca2::brush_sp      m_brushBody;

            point_array m_pointsetBody;
            array < CColorBezier, CColorBezier & > m_colorbezieraOutsideBorder;
         };

         CWorkSetDownUpInterface   *   m_pwndframeworkdownupinterface;
         bool                          m_fActive;
         bool                          m_bUseNc;

         bool                          m_bAutomaticModeSwitching;

         WorkSet *                     m_pworkset;
         bool                          m_bEnabled;
         EAppearanceMode               m_emode;
         EAppearanceTransparency       m_nTransparency;
         CTool001 *                    m_ptool001;

         bool IsNotifyIconEnabled();
         virtual sp(::user::interaction) get_guie();
         sp(::user::interaction) GetWnd();

         bool IsInAutomaticModeSwitching();
         void SetAutomaticModeSwitching(bool bSetting);


         void UpdateAppearanceMode(bool bFullScreen);
         void SetDownUpInterface(CWorkSetDownUpInterface * pinterface);
         bool WndFrameworkDownUpGetDownEnable();
         virtual bool WndFrameworkDownUpGetUpEnable();
         EAppearanceMode GetAppearanceMode();
         bool update();
         bool IsIconic();
         bool IsFullScreen();
         bool IsZoomed();
         bool IsEnabled();
         void Enable(bool bEnable);

         void SetTransparency(EAppearanceTransparency nTransparency);
         void SetAppearanceMode(EAppearanceMode nMode);
         void SetAppearanceMode();

         EHitTest hit_test(point pt);

         virtual void frame_Attach();
         virtual void frame_Detach();

      };

   } // namespace frame


} // namespace uinteraction


