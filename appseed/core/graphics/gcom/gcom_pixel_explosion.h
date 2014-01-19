#pragma once


namespace gcom
{


   class pixel_explosion
   {
   public:


      int32_t                       m_iWidth;
      int32_t                       m_iHeight;
      bool                          m_bDrawWithLight;
      int32_t                       m_iLightModifier;
      int32_t                       m_iHpage; // The current heightfield
      double                        m_density; // The water density - can change the density...
      double                        m_minradius;
      double                        m_z;
      raw_array < double3d_point >  m_pointaM;
      raw_array < double3d_point >  m_pointa;


      pixel_explosion();
      virtual ~pixel_explosion();

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


} // namespace gcom




