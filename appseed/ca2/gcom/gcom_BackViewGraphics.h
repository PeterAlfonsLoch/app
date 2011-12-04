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
         Graphics(Main & main);
         virtual ~Graphics();
         void UpdateObjects();
         void OnDestroy();
         void OnImageLoaded(::ca::bitmap * hbitmap);
         void LayoutBackBitmap(BITMAP * lpbmBack);
         EImagePlacement GetDefaultPlacement();
         // buffer Level 2 consists of m_dcBackView2,
         // m_bmpBackView2 and m_bmpBackView2Old
         // It buffers the background as it should
         // appear after transition effect has finished.
         // It is a layer between the source bitmap image
         // and the final background buffer.
         bool RenderBufferLevel2();

         ::ca::graphics & GetTransferDC(); // m_dcBackView2
         ::ca::graphics & GetFrame1DC(); // m_dcBackView2
         ::ca::graphics & GetBufferDC(); // m_dcBackView2
         ::ca::graphics & GetSourceDC(); // m_dcBackViewSource
         ::ca::graphics & GetScreenDC(); // m_dcBackViewSource

         ::ca::dib * GetDib(int iIndex);
         ::ca::draw_dib & GetDrawDib();

         ::ca::bitmap & GetTransferBitmap(); // m_bmpBackView2
         ::ca::bitmap & GetFrame1Bitmap(); // m_bmpBackView2
         ::ca::bitmap & GetBufferBitmap(); // m_bmpBackView2
         ::ca::bitmap & GetSourceBitmap(); // m_bmpBackViewSource

         virtual void OnCreateDib(::ca::dib * pdib, int iIndex);
         
         ::collection::map < int, int, ::ca::dib *, ::ca::dib * > m_mapDib;
         ::ca::draw_dib_sp         m_spdrawdib;

         mutex   m_mutex1Back;
         mutex   m_mutex2Buffer;

         ::ca::bitmap & GetBackBitmap(); // m_bmpBackView
         ::ca::graphics & GetBackDC(); // m_dcBackView
         
//         // Back tools keep the current background snapshot
//         ::ca::graphics_sp               m_dcBack;
//         ::ca::bitmap            m_bmpBack;
//         ::ca::bitmap            m_bmpBackOld;

         // Back tools keep the final ::view background snapshot
//         ::ca::graphics_sp               m_dcBuffer;
//         ::ca::bitmap            m_bmpBuffer;
//         ::ca::bitmap            m_bmpBufferOld;

         // Used for fast buffer transfer
//         ::ca::graphics_sp               m_dcTransfer;
//         ::ca::bitmap            m_bmpTransfer;
//         ::ca::bitmap            m_bmpTransferOld;

         // Source tools keep the original bitmap int its original size
//         ::ca::graphics_sp               m_dcSource;
//         ::ca::bitmap            m_bmpSource;
//         ::ca::bitmap            m_bmpSourceOld;

         // Source tools keep the original bitmap int its original size
//         ::ca::graphics_sp               m_dcFrame1;
//         ::ca::bitmap            m_bmpFrame1;
//       ::ca::bitmap            m_bmpFrame1Old;

         ::ca::graphics_sp               m_dcScreen;

         rect             m_rectFinalPlacement;
         void GetFinalPlacement(LPRECT lprect);
         void BackToTransfer();
         void BufferToBack();
         
         
         mutex   m_mutex3Source;
         mutex   m_mutex4Transfer;

      };
   } // namespace backview

} // namespace gcom
