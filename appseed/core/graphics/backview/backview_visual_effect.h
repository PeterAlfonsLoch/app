#pragma once


namespace backview
{


   class VisualEffect :
      public Helper
   {
   public:


      struct Tool001
      {
         int32_t   cx;
         int32_t   cy;
         rect rectClient;
         int32_t   page;
         int32_t   frame;
         double  dmod;
         double   dminsize;
         double   dalpha;


      };

      struct RandomGrow
      {
         int32_t i;
         int32_t imax;
         int32_t lbound;
         int32_t maxlbound;
         int32_t maxubound;
      public:
         bool Step();
      };


      struct ColorTrack1
      {
         RandomGrow  m_rndgrowDirectionLatency;
         double      m_dDirection;
         double      m_dDirectionAddUp;
         point      m_ptColorTrack;
         RandomGrow  m_rndgrowVelocity;
         double      m_dCos;
         double      m_dSin;
         double      m_dSize;
      };


      int32_t                       m_iVisual;
      bool                          m_bGrowColor0;
      color                         m_color;
      int32_t                       m_iGrowColor;
      int32_t                       m_iGrowMax;
      double                        m_dAngle;

      color                         m_color2;
      int32_t                       m_iGrowColor2;
      int32_t                       m_iGrowMax2;

      color                         m_color3;
      int32_t                       m_iGrowColor3;
      int32_t                       m_iGrowMax3;

      color                         m_color4;
      int32_t                       m_iGrowColor4;
      int32_t                       m_iGrowMax4;

      point                         m_ptColorTrack;
      RandomGrow                    m_rndgrowVelocity;
      double                        m_dDirection;
      double                        m_dDirectionAddUp;
      RandomGrow                    m_rndgrowDirectionLatency;

      RandomGrow                    m_rndgrowAngleOffsetLatency;
      double                        m_dAngleOffset;
      double                        m_dAngleOffsetAddUp;

      array < ColorTrack1 >         m_colortrack1a;

      Tool001                       tool1;

      array < point, point & >      m_pointa;
      array < point, point & >      m_pointa1;
      array < point, point & >      m_pointa2;

      ::gcom::pixel_explosion       m_explosion;


      visual::water_routine m_water;


      VisualEffect(Main & Main);
      virtual ~VisualEffect();


      int32_t GetEffectCount();
      void InitialRender();
      void RenderBuffer(rect_array & recta);

      void RenderRotateBlend(rect_array & recta);
      void RenderNPRotateBlend(rect_array & recta);
      void RenderNPRotatecolor_blend_(rect_array & recta);
      void RenderNPRotateTrackcolor_blend_(rect_array & recta);
      void RenderRotateEx1(rect_array & recta);
      void RenderRotateEx2(rect_array & recta);
      void RenderRotateEx3(rect_array & recta);
      void RenderRotateEx4(rect_array & recta);
      void RenderRain1(rect_array & recta);
      void RenderRotateEx5(rect_array & recta);
      void RenderRotateEx6(rect_array & recta);
      void RenderRotateEx7(rect_array & recta);
      void RenderRotateEx8(rect_array & recta);
      void RenderExpand4(rect_array & recta);
      void RenderExpand5(rect_array & recta);
      void RenderExpand6(rect_array & recta);
      void RenderExpand7(rect_array & recta);
      void RenderExpand8(rect_array & recta);
      void RenderPixelExplosion(rect_array & recta);
      void RenderPixelExplosion2(rect_array & recta);
      void RenderAlphaPixelExplosion(rect_array & recta);





      static void Constraint001(point & pt, const RECT & rect, double & dDirection);
      static void Constraint001(point & pt, LPCRECT lpcrectIn, LPCRECT lpcrectOut, double & dDirection);
      static void TrackDirection001(double &direction, double & directionAddUp, RandomGrow & randomgrow);


      static void StepGrow001(color & color, int32_t & iGrowColor, int32_t & iGrowMax);
      static void StepGrow034(color & color, int32_t & iGrowColor, int32_t & iGrowMax);
      static void StepGrow001(color & color, int32_t & iGrowColor, int32_t & iGrowMax, bool & bGrowColor);

   };


} // namespace backbiew


