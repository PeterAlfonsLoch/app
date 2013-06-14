#pragma once

class dib;
class draw_dib;

namespace gcom
{
   namespace backview
   {
      namespace _graphics
      {
         enum EDib
         {
            DibTemp1 = 2,
            DibTemp2,
            DibTemp3,
            DibTemp4,
            DibTemp5,
            DibBuffer = 100,
            DibFrame1 = 101,
            DibSource = 99,
            DibFinal = 98,
            DibBack = 150,
            DibTransfer = 200,
         };
      }

      class Interface;
      class CImageChange;

      class CLASS_DECL_ca2 Graphics :
         public Helper
      {
      public:

         ::ca2::graphics_sp               m_dcScreen;
         rect             m_rectFinalPlacement;

         map < int32_t, int32_t, ::ca2::dib *, ::ca2::dib * > m_mapDib;
//         ::ca2::draw_dib_sp         m_spdrawdib;

         mutex   m_mutgenBack;
         mutex   m_mutgenBuffer;
         mutex   m_mutex3Source;
         mutex   m_mutex4Transfer;



         Graphics(Main & main);
         virtual ~Graphics();
         void UpdateObjects();
         void OnDestroy();
         void OnImageLoaded(::ca2::dib * pdib);
         void LayoutBackBitmap(BITMAP * lpbmBack);
         EImagePlacement GetDefaultPlacement();
         // buffer Level 2 consists of m_dcBackView2,
         // m_bmpBackView2 and m_bmpBackView2Old
         // It buffers the background as it should
         // appear after transition effect has finished.
         // It is a layer between the source bitmap image
         // and the final background buffer.
         bool RenderBufferLevel2();

         ::ca2::graphics & GetTransferDC(); // m_dcBackView2
         ::ca2::graphics & GetFrame1DC(); // m_dcBackView2
         ::ca2::graphics & GetBufferDC(); // m_dcBackView2
         ::ca2::graphics & GetSourceDC(); // m_dcBackViewSource
         ::ca2::graphics & GetScreenDC(); // m_dcBackViewSource

         ::ca2::dib * GetDib(int32_t iIndex);
//         ::ca2::draw_dib & GetDrawDib();

         ::ca2::bitmap & GetTransferBitmap(); // m_bmpBackView2
         ::ca2::bitmap & GetFrame1Bitmap(); // m_bmpBackView2
         ::ca2::bitmap & GetBufferBitmap(); // m_bmpBackView2
         ::ca2::bitmap & GetSourceBitmap(); // m_bmpBackViewSource

         virtual void OnCreateDib(::ca2::dib * pdib, int32_t iIndex);
         

         ::ca2::bitmap & GetBackBitmap(); // m_bmpBackView
         ::ca2::graphics & GetBackDC(); // m_dcBackView
         
//         // Back tools keep the current background snapshot
//         ::ca2::graphics_sp               m_dcBack;
//         ::ca2::bitmap            m_bmpBack;
//         ::ca2::bitmap            m_bmpBackOld;

         // Back tools keep the final ::user::view background snapshot
//         ::ca2::graphics_sp               m_dcBuffer;
//         ::ca2::bitmap            m_bmpBuffer;
//         ::ca2::bitmap            m_bmpBufferOld;

         // Used for fast buffer transfer
//         ::ca2::graphics_sp               m_dcTransfer;
//         ::ca2::bitmap            m_bmpTransfer;
//         ::ca2::bitmap            m_bmpTransferOld;

         // Source tools keep the original bitmap int32_t its original size
//         ::ca2::graphics_sp               m_dcSource;
//         ::ca2::bitmap            m_bmpSource;
//         ::ca2::bitmap            m_bmpSourceOld;

         // Source tools keep the original bitmap int32_t its original size
//         ::ca2::graphics_sp               m_dcFrame1;
//         ::ca2::bitmap            m_bmpFrame1;
//       ::ca2::bitmap            m_bmpFrame1Old;

         void GetFinalPlacement(LPRECT lprect);
         void BackToTransfer();
         void BufferToBack();
         
         
      };
   } // namespace backview

} // namespace gcom
