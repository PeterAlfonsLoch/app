#pragma once


namespace visual
{


   class CLASS_DECL_CORE water_routine  
   {
   public:
      water_routine();
      virtual ~water_routine();


      void create(int32_t iWidth,int32_t iHeight);
      void to(COLORREF * pSrcImage, COLORREF * pTargetImage);

      void CalcWater(int32_t npage, int32_t density);
      void SmoothWater(int32_t npage);
      void FlattenWater();

      void SineBlob(int32_t x, int32_t y, int32_t radius, int32_t height, int32_t page);
      void WarpBlob(int32_t x, int32_t y, int32_t radius, int32_t height, int32_t page);
      void HeightBox (int32_t x, int32_t y, int32_t radius, int32_t height, int32_t page);
      void HeightBlob(int32_t x, int32_t y, int32_t radius, int32_t height, int32_t page);
      void CalcWaterBigFilter(int32_t npage, int32_t density);

      void DrawWaterNoLight(int32_t page, COLORREF * pSrcImage, COLORREF * pTargetImage);
      void DrawWaterWithLight(int32_t page, int32_t LightModifier, COLORREF * pSrcImage, COLORREF * pTargetImage);
      COLORREF GetShiftedColor(COLORREF color,int32_t shift);

      int32_t            m_iWidth;
      int32_t            m_iHeight;
      bool            m_bDrawWithLight;
      int32_t            m_iLightModifier;
      int32_t            m_iHpage;// The current heightfield
      int32_t            m_density;// The water density - can change the density...
      //  the height fields
      int32_t*            m_iHeightField1;
      int32_t*            m_iHeightField2;


   };


}



