#pragma once


namespace window_frame
{

   class WorkSet;
   class ControlBoxButton;

   class CLASS_DECL_ca appearance :
      public CWorkSetDownUpInterface,
      virtual public ::gen::signalizable
   {
      friend class WorkSet;
   public:

      appearance(WorkSet * pworkset);
      virtual ~appearance();

      class CTool001 :
         virtual public ::radix::object
      {
      public:

         CTool001(::ax::application * papp);
         
         void Update(LPCRECT lpcrect,
            COLORREF crHighlight,
            COLORREF crLight,
            COLORREF crBody,
            COLORREF crShadow,
            COLORREF crDkShadow);
         void draw(::ax::graphics * pdc);

         class CColorBezier
         {
         public:
            void draw(::ax::brush & brush, ::ax::graphics * pdc);
            point_array m_pointset;
            ::ax::pen  *   m_ppen;
            void clear();
         };
      public:
         ::ax::pen_sp      m_penHighlight;
         ::ax::pen_sp      m_penLight;
         ::ax::pen_sp      m_penShadow;
         ::ax::pen_sp      m_penDkShadow;
         ::ax::brush_sp      m_brushNull;
         ::ax::brush_sp      m_brushBody;

         point_array m_pointsetBody;
         base_array < CColorBezier, CColorBezier & > m_colorbezieraOutsideBorder;
      };

      CWorkSetDownUpInterface   *   m_pwndframeworkdownupinterface;
      BOOL                          m_fActive;
      bool                          m_bUseNc;

      bool                          m_bAutomaticModeSwitching;

      WorkSet *                     m_pworkset;
      bool                          m_bEnabled;
      EAppearanceMode               m_emode;
      EAppearanceTransparency       m_nTransparency;
      CTool001 *                    m_ptool001;

      bool IsNotifyIconEnabled();
      virtual ::user::interaction * get_guie();
      ::user::interaction * GetWnd();
      
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

      virtual void window_frame_Attach();
      virtual void window_frame_Detach();

   };

} // namespace window_frame
