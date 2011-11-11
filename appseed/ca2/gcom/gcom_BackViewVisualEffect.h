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
         PixelExplosion();
         virtual ~PixelExplosion();


         void create(int iWidth,int iHeight);
         void to(DWORD* pSrcImage,DWORD* pTargetImage);

         void CalcWater(int npage, int density);
         void Calc2(int npage, int density);
         void SmoothWater(int npage);
         void FlattenWater();

         void SineBlob(int x, int y, int radius, int height, int page);
         void WarpBlob(int x, int y, int radius, int height, int page);
         void HeightBox (int x, int y, int radius, int height, int page);
         void Reset();
         void CalcWaterBigFilter(int npage, int density);

         void DrawWaterNoLight(int page,DWORD* pSrcImage,DWORD* pTargetImage);
         //void DrawWaterWithLight(int page, int LightModifier,DWORD* pSrcImage,DWORD* pTargetImage);
         COLORREF GetShiftedColor(COLORREF color,int shift);

         int         m_iWidth;
         int         m_iHeight;
         BOOL      m_bDrawWithLight;
         int         m_iLightModifier;
         int         m_iHpage;// The current heightfield
         double      m_density;// The water density - can change the density...
         double      m_minradius;
         //  the height fields
      //   int*      m_iHeightField1;
      //   int*      m_iHeightField2;

         double m_z;

         base_array < DoublePoint, DoublePoint & > m_pointaM;

         base_array < DoublePoint, DoublePoint & > m_pointa;

      };


      class VisualEffect :
         public Helper
      {
      public:
         static void StepGrow001(
            color & color, 
            int & iGrowColor,
            int & iGrowMax);
         static void StepGrow034(
            color & color, 
            int & iGrowColor,
            int & iGrowMax);
         static void StepGrow001(
            color & color, 
            int & iGrowColor,
            int & iGrowMax,
            bool & bGrowColor);
         struct Tool001
         {
            int   cx;
            int   cy;
            rect rectClient;
            int   page;
            int   frame;
            double  dmod;
            double   dminsize;
            double   dalpha;

            
         };

         struct RandomGrow
         {
            int i;
            int imax;
            int lbound;
            int maxlbound;
            int maxubound;
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


         int GetEffectCount();
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

         VisualEffect(Main & Main);
         virtual ~VisualEffect();



         bool     m_bGrowColor0;
         //int      m_iGrow

         color   m_color;
         int      m_iGrowColor;
         int      m_iGrowMax;
         double   m_dAngle;

         color   m_color2;
         int      m_iGrowColor2;
         int      m_iGrowMax2;

         color   m_color3;
         int      m_iGrowColor3;
         int      m_iGrowMax3;

         color   m_color4;
         int      m_iGrowColor4;
         int      m_iGrowMax4;

         point      m_ptColorTrack;
         RandomGrow  m_rndgrowVelocity;
         double      m_dDirection;
         double      m_dDirectionAddUp;
         RandomGrow  m_rndgrowDirectionLatency;

         RandomGrow  m_rndgrowAngleOffsetLatency;
         double      m_dAngleOffset;
         double      m_dAngleOffsetAddUp;

         base_array < ColorTrack1, ColorTrack1 & >
                     m_colortrack1a;

         Tool001  tool1;

         base_array < point, point & > m_pointa;
         base_array < point, point & > m_pointa1;
         base_array < point, point & > m_pointa2;

         PixelExplosion m_explosion;


         visual::water_routine m_water;

         static void Constraint001(point & pt, LPCRECT lpcrect, double & dDirection);
         static void Constraint001(point & pt, LPCRECT lpcrectIn, LPCRECT lpcrectOut, double & dDirection);
         static void TrackDirection001(double &direction, double & directionAddUp, RandomGrow & randomgrow);

      };

   } // namespace backbiew

} // namespace gcom
