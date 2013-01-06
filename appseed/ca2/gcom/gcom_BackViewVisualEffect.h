#pragma once


namespace gcom
{


   namespace backview
   {


      class DoublePoint
      {
      public:
         double x;
         double y;
         double z;
      };


      class Main;


      enum EVisualEffect
      {
         VisualEffectPixelExplosion,
         VisualEffectAlphaPixelExplosion,
         VisualEffectPixelExplosion2,

         VisualEffectRotateEx8,
         VisualEffectRotateEx4,
         VisualEffectRain1,
         VisualEffectRotateEx5,
         VisualEffectRotateEx6,
         VisualEffectRotateEx7,

         VisualEffectExpand8,
         VisualEffectExpand4,
         VisualEffectExpand5,
         VisualEffectExpand6,
         VisualEffectExpand7,

         VisualEffectRotateBlend,
         VisualEffectNoPrecisionRotateBlend,
         VisualEffectNoPrecisionRotatecolor_blend_,
         VisualEffectNoPrecisionRotateTrackcolor_blend_,
         VisualEffectRotateEx1,
         VisualEffectRotateEx2,
         VisualEffectRotateEx3,
         VisualEffectEnd,
      };


      class PixelExplosion
      {
      public:

         int32_t         m_iWidth;
         int32_t         m_iHeight;
         bool      m_bDrawWithLight;
         int32_t         m_iLightModifier;
         int32_t         m_iHpage;// The current heightfield
         double      m_density;// The water density - can change the density...
         double      m_minradius;
         //  the height fields
      //   int32_t*      m_iHeightField1;
      //   int32_t*      m_iHeightField2;

         double m_z;

         base_array < DoublePoint, DoublePoint & > m_pointaM;

         base_array < DoublePoint, DoublePoint & > m_pointa;


         PixelExplosion();
         virtual ~PixelExplosion();

         void create(int32_t iWidth,int32_t iHeight);
         void to(COLORREF * pSrcImage, COLORREF * pTargetImage);

         void CalcWater(int32_t npage, int32_t density);
         void Calc2(int32_t npage, int32_t density);
         void SmoothWater(int32_t npage);
         void FlattenWater();

         void SineBlob(int32_t x, int32_t y, int32_t radius, int32_t height, int32_t page);
         void WarpBlob(int32_t x, int32_t y, int32_t radius, int32_t height, int32_t page);
         void HeightBox (int32_t x, int32_t y, int32_t radius, int32_t height, int32_t page);
         void Reset();
         void CalcWaterBigFilter(int32_t npage, int32_t density);

         void DrawWaterNoLight(int32_t page, COLORREF * pSrcImage, COLORREF * pTargetImage);
         //void DrawWaterWithLight(int32_t page, int32_t LightModifier,uint32_t* pSrcImage,uint32_t* pTargetImage);
         COLORREF GetShiftedColor(COLORREF color,int32_t shift);

      };


      class VisualEffect :
         public Helper
      {
      public:


         static void StepGrow001(
            color & color, 
            int32_t & iGrowColor,
            int32_t & iGrowMax);
         static void StepGrow034(
            color & color, 
            int32_t & iGrowColor,
            int32_t & iGrowMax);
         static void StepGrow001(
            color & color, 
            int32_t & iGrowColor,
            int32_t & iGrowMax,
            bool & bGrowColor);
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


         int32_t            m_iVisual;
         bool           m_bGrowColor0;
         color          m_color;
         int32_t            m_iGrowColor;
         int32_t            m_iGrowMax;
         double         m_dAngle;

         color          m_color2;
         int32_t            m_iGrowColor2;
         int32_t            m_iGrowMax2;

         color          m_color3;
         int32_t            m_iGrowColor3;
         int32_t            m_iGrowMax3;

         color          m_color4;
         int32_t            m_iGrowColor4;
         int32_t            m_iGrowMax4;

         point          m_ptColorTrack;
         RandomGrow     m_rndgrowVelocity;
         double         m_dDirection;
         double         m_dDirectionAddUp;
         RandomGrow     m_rndgrowDirectionLatency;

         RandomGrow     m_rndgrowAngleOffsetLatency;
         double         m_dAngleOffset;
         double         m_dAngleOffsetAddUp;

         base_array < ColorTrack1, ColorTrack1 & >
                        m_colortrack1a;

         Tool001        tool1;

         base_array < point, point & > m_pointa;
         base_array < point, point & > m_pointa1;
         base_array < point, point & > m_pointa2;

         PixelExplosion m_explosion;


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





         static void Constraint001(point & pt, LPCRECT lpcrect, double & dDirection);
         static void Constraint001(point & pt, LPCRECT lpcrectIn, LPCRECT lpcrectOut, double & dDirection);
         static void TrackDirection001(double &direction, double & directionAddUp, RandomGrow & randomgrow);

      };


   } // namespace backbiew


} // namespace gcom


