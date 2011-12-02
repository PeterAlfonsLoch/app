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

      class CLASS_DECL_ca Graphics :
         public Helper
      {
      public:
         Graphics(Main & main);
         virtual ~Graphics();
         void UpdateObjects();
         void OnDestroy();
         void OnImageLoaded(::ax::bitmap * hbitmap);
         void LayoutBackBitmap(BITMAP * lpbmBack);
         EImagePlacement GetDefaultPlacement();
         // buffer Level 2 consists of m_dcBackView2,
         // m_bmpBackView2 and m_bmpBackView2Old
         // It buffers the background as it should
         // appear after transition effect has finished.
         // It is a layer between the source bitmap image
         // and the final background buffer.
         bool RenderBufferLevel2();

         ::ax::graphics & GetTransferDC(); // m_dcBackView2
         ::ax::graphics & GetFrame1DC(); // m_dcBackView2
         ::ax::graphics & GetBufferDC(); // m_dcBackView2
         ::ax::graphics & GetSourceDC(); // m_dcBackViewSource
         ::ax::graphics & GetScreenDC(); // m_dcBackViewSource

         ::ax::dib * GetDib(int iIndex);
         ::ax::draw_dib & GetDrawDib();

         ::ax::bitmap & GetTransferBitmap(); // m_bmpBackView2
         ::ax::bitmap & GetFrame1Bitmap(); // m_bmpBackView2
         ::ax::bitmap & GetBufferBitmap(); // m_bmpBackView2
         ::ax::bitmap & GetSourceBitmap(); // m_bmpBackViewSource

         virtual void OnCreateDib(::ax::dib * pdib, int iIndex);
         
         ::collection::map < int, int, ::ax::dib *, ::ax::dib * > m_mapDib;
         ::ax::draw_dib_sp         m_spdrawdib;

         mutex   m_mutex1Back;
         mutex   m_mutex2Buffer;

         ::ax::bitmap & GetBackBitmap(); // m_bmpBackView
         ::ax::graphics & GetBackDC(); // m_dcBackView
         
//         // Back tools keep the current background snapshot
//         ::ax::graphics_sp               m_dcBack;
//         ::ax::bitmap            m_bmpBack;
//         ::ax::bitmap            m_bmpBackOld;

         // Back tools keep the final ::view background snapshot
//         ::ax::graphics_sp               m_dcBuffer;
//         ::ax::bitmap            m_bmpBuffer;
//         ::ax::bitmap            m_bmpBufferOld;

         // Used for fast buffer transfer
//         ::ax::graphics_sp               m_dcTransfer;
//         ::ax::bitmap            m_bmpTransfer;
//         ::ax::bitmap            m_bmpTransferOld;

         // Source tools keep the original bitmap int its original size
//         ::ax::graphics_sp               m_dcSource;
//         ::ax::bitmap            m_bmpSource;
//         ::ax::bitmap            m_bmpSourceOld;

         // Source tools keep the original bitmap int its original size
//         ::ax::graphics_sp               m_dcFrame1;
//         ::ax::bitmap            m_bmpFrame1;
//       ::ax::bitmap            m_bmpFrame1Old;

         ::ax::graphics_sp               m_dcScreen;

         rect             m_rectFinalPlacement;
         void GetFinalPlacement(LPRECT lprect);
         void BackToTransfer();
         void BufferToBack();
         
         
         mutex   m_mutex3Source;
         mutex   m_mutex4Transfer;

      };
   } // namespace backview

} // namespace gcom
