#pragma once



namespace uinteraction
{


   namespace frame
   {

      class WorkSet;
      class ControlBoxButton;

      class CLASS_DECL_ca2 appearance :
         public CWorkSetDownUpInterface,
         virtual public ::ca::signalizable
      {
         friend class WorkSet;
      public:

         appearance(WorkSet * pworkset);
         virtual ~appearance();

         class CTool001 :
            virtual public ::ca::object
         {
         public:

            CTool001(::ca::applicationsp papp);

            void Update(::ca::graphics * pdc, LPCRECT lpcrect,
               COLORREF crHighlight,
               COLORREF crLight,
               COLORREF crBody,
               COLORREF crShadow,
               COLORREF crDkShadow);
            void draw(::ca::graphics * pdc);

            class CColorBezier
            {
            public:
               void draw(::ca::brush & brush, ::ca::graphics * pdc);
               point_array m_pointset;
               ::ca::pen  *   m_ppen;
               void clear();
            };
         public:
            ::ca::pen_sp      m_penHighlight;
            ::ca::pen_sp      m_penLight;
            ::ca::pen_sp      m_penShadow;
            ::ca::pen_sp      m_penDkShadow;
            ::ca::brush_sp      m_brushNull;
            ::ca::brush_sp      m_brushBody;

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


