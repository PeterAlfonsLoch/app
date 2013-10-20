#pragma once


namespace backview
{


   class CLASS_DECL_CORE Graphics :
      public Helper
   {
   public:


      ::draw2d::graphics_sp               m_dcScreen;
      rect                                m_rectFinalPlacement;


      int_map < ::draw2d::dib_sp >        m_mapDib;


      mutex   m_mutex1Back;
      mutex   m_mutex2Buffer;
      mutex   m_mutex3Source;
      mutex   m_mutex4Transfer;



      Graphics(Main & main);
      virtual ~Graphics();
      void UpdateObjects();
      void OnDestroy();
      void OnImageLoaded(::draw2d::dib * pdib);
      void LayoutBackBitmap(BITMAP * lpbmBack);
      EImagePlacement GetDefaultPlacement();
      // buffer Level 2 consists of m_dcBackView2,
      // m_bmpBackView2 and m_bmpBackView2Old
      // It buffers the background as it is usually expected to
      // appear after transition effect has finished.
      // It is a layer between the source bitmap image
      // and the final background buffer.
      bool RenderBufferLevel2();

      ::draw2d::graphics_sp GetTransferDC(); // m_dcBackView2
      ::draw2d::graphics_sp GetFrame1DC(); // m_dcBackView2
      ::draw2d::graphics_sp GetBufferDC(); // m_dcBackView2
      ::draw2d::graphics_sp GetSourceDC(); // m_dcBackViewSource
      ::draw2d::graphics_sp GetScreenDC(); // m_dcBackViewSource

      ::draw2d::dib_sp GetDib(int32_t iIndex);

      ::draw2d::bitmap_sp GetTransferBitmap(); // m_bmpBackView2
      ::draw2d::bitmap_sp GetFrame1Bitmap(); // m_bmpBackView2
      ::draw2d::bitmap_sp GetBufferBitmap(); // m_bmpBackView2
      ::draw2d::bitmap_sp GetSourceBitmap(); // m_bmpBackViewSource

      virtual void OnCreateDib(::draw2d::dib * pdib, int32_t iIndex);


      ::draw2d::bitmap_sp GetBackBitmap(); // m_bmpBackView
      ::draw2d::graphics_sp GetBackDC(); // m_dcBackView

//         // Back tools keep the current background snapshot
//         ::draw2d::graphics_sp               m_dcBack;
//         ::draw2d::bitmap            m_bmpBack;
//         ::draw2d::bitmap            m_bmpBackOld;

      // Back tools keep the final ::user::view background snapshot
//         ::draw2d::graphics_sp               m_dcBuffer;
//         ::draw2d::bitmap            m_bmpBuffer;
//         ::draw2d::bitmap            m_bmpBufferOld;

      // Used for fast buffer transfer
//         ::draw2d::graphics_sp               m_dcTransfer;
//         ::draw2d::bitmap            m_bmpTransfer;
//         ::draw2d::bitmap            m_bmpTransferOld;

      // Source tools keep the original bitmap int32_t its original size
//         ::draw2d::graphics_sp               m_dcSource;
//         ::draw2d::bitmap            m_bmpSource;
//         ::draw2d::bitmap            m_bmpSourceOld;

      // Source tools keep the original bitmap int32_t its original size
//         ::draw2d::graphics_sp               m_dcFrame1;
//         ::draw2d::bitmap            m_bmpFrame1;
//       ::draw2d::bitmap            m_bmpFrame1Old;

      void GetFinalPlacement(LPRECT lprect);
      void BackToTransfer();
      void BufferToBack();


   };


} // namespace backview





