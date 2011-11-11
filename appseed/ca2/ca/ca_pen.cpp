#include "StdAfx.h"

namespace ca
 {

   void pen::construct(int nPenStyle, int nWidth, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(nPenStyle);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }

   void pen::construct(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush, int nStyleCount, const DWORD* lpStyle)
   {
      UNREFERENCED_PARAMETER(nPenStyle);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(pLogBrush);
      UNREFERENCED_PARAMETER(nStyleCount);
      UNREFERENCED_PARAMETER(lpStyle);
      throw interface_only_exception();
   }

   #ifdef _DEBUG
   void pen::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception();
   }
   #endif

   /////////////////////////////////////////////////////////////////////////////
   // Standard exception processing


   // resource failure
   void AfxThrowResourceException()
   {
      throw resource_exception();
   }

   // ::fontopus::user alert
   void AfxThrowUserException()
   {
      throw user_exception();
   }

   void AfxGetGrayBitmap(::ca::application * papp, const ::ca::bitmap &rSrc, ::ca::bitmap *pDest, COLORREF crBackground)
   {
      ASSERT(pDest);
      ASSERT_KINDOF(::ca::bitmap, pDest);

      BITMAP bm;
      ::ca::graphics_sp graphicsMem, graphicsMask;
      COLORREF cr;
      ::ca::bitmap_sp bmpMask(papp);
      ::ca::bitmap *pOldMask, *pOldMem;
      const DWORD   CP_ROP = 0xE20746;
      ::ca::brush_sp brHighLight(papp, ::GetSysColor(COLOR_3DHIGHLIGHT)),
         brShadow(papp, ::GetSysColor(COLOR_3DSHADOW)), spbr;

      if(graphicsMem->CreateCompatibleDC(NULL) &&
         graphicsMask->CreateCompatibleDC(NULL))
      {
         const_cast<::ca::bitmap &>(rSrc).GetBitmap(&bm);
         pDest->delete_object();
         if(pDest->CreateBitmap(bm.bmWidth, bm.bmHeight, bm.bmPlanes, bm.bmBitsPixel, NULL) &&
            bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL))
         {
            pOldMem = graphicsMem->SelectObject(const_cast<::ca::bitmap *>(&rSrc));
            pOldMask = graphicsMask->SelectObject(bmpMask);

            ASSERT(pOldMem && pOldMask);
            if(!pOldMem || !pOldMask)
               return;

            // Make the upper left corner pixel the "transparent" pixel
            cr = graphicsMem->SetBkColor(graphicsMem->GetPixel(0, 0));
            graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0, SRCCOPY);
            // Make white pixels transparent too
            graphicsMem->SetBkColor(RGB(255, 255, 255));
            graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0, NOTSRCERASE);

            if(graphicsMem->SelectObject(pDest))
            {
               graphicsMem->FillSolidRect(0, 0, bm.bmWidth, bm.bmHeight, crBackground);

               graphicsMem->SetBkColor(RGB(255, 255, 255));

               spbr = graphicsMem->SelectObject(brHighLight);
               graphicsMem->BitBlt(1, 1, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

               graphicsMem->SelectObject(brShadow);
               graphicsMem->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

               graphicsMem->SelectObject(spbr);

               graphicsMem->SetBkColor(cr);
            }
            graphicsMask->SelectObject(pOldMask);
            graphicsMem->SelectObject(pOldMem);
         }
      }
   }

   void AfxDrawGrayBitmap(::ca::application * papp, ::ca::graphics * pgraphics, int x, int y, const ::ca::bitmap &rSrc, COLORREF crBackground)
   {
      ASSERT(pgraphics);
      ASSERT_KINDOF(::ca::graphics_sp, pgraphics);

      BITMAP bm;
      ::ca::graphics_sp graphicsMem, graphicsMask;
      COLORREF cr;
      ::ca::bitmap_sp bmpMask(papp);
      ::ca::bitmap *pOldMask, *pOldMem;
      const DWORD   CP_ROP = 0xE20746;
      ::ca::brush_sp brHighLight(papp, ::GetSysColor(COLOR_3DHIGHLIGHT)),
         brShadow(papp, ::GetSysColor(COLOR_3DSHADOW)), spbr;

      if(graphicsMem->CreateCompatibleDC(pgraphics) &&
         graphicsMask->CreateCompatibleDC(pgraphics) &&
         const_cast<::ca::bitmap &>(rSrc).GetBitmap(&bm) &&
         bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL))
      {
         pOldMem = graphicsMem->SelectObject(const_cast<::ca::bitmap *>(&rSrc));
         pOldMask = graphicsMask->SelectObject(bmpMask);

         ASSERT(pOldMem && pOldMask);
         if(!pOldMem || !pOldMask)
            return;

         cr = graphicsMem->SetBkColor(graphicsMem->GetPixel(0, 0));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0, SRCCOPY);
         graphicsMem->SetBkColor(RGB(255, 255, 255));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMem, 0, 0, NOTSRCERASE);

         pgraphics->FillSolidRect(x, y, bm.bmWidth, bm.bmHeight, crBackground);

         pgraphics->SetBkColor(RGB(255, 255, 255));

         spbr = pgraphics->SelectObject(brHighLight);
         pgraphics->BitBlt(x + 1, y + 1, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

         pgraphics->SelectObject(brShadow);
         pgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, CP_ROP);

         pgraphics->SelectObject(spbr);

         pgraphics->SetBkColor(cr);
         graphicsMask->SelectObject(pOldMask);
      }
   }

   void AfxGetDitheredBitmap(::ca::application * papp, const ::ca::bitmap &rSrc, ::ca::bitmap *pDest, COLORREF cr1, COLORREF cr2)
   {
      ASSERT(pDest);
      ASSERT_KINDOF(::ca::bitmap, pDest);

      BITMAP bm;
      ::ca::graphics_sp graphicsSrc, graphicsMask, graphicsDest;
      COLORREF cr;
      ::ca::bitmap_sp bmpMask(papp);
      ::ca::bitmap *pOldMask, *pOldSrc;
      ::ca::brush brChecker;
      static const WORD wPat[8] = {0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa};

      if(graphicsSrc->CreateCompatibleDC(NULL) &&
         graphicsMask->CreateCompatibleDC(NULL) &&
         graphicsDest->CreateCompatibleDC(NULL))
      {
         if(const_cast<::ca::bitmap &>(rSrc).GetBitmap(&bm))
         {
            pDest->delete_object();
            if(pDest->CreateBitmap(bm.bmWidth, bm.bmHeight, bm.bmPlanes, bm.bmBitsPixel, NULL))
            {
               // create checker brush
               bmpMask->CreateBitmap(8, 8, 1, 1, wPat);
               brChecker.CreatePatternBrush(bmpMask);
               bmpMask->delete_object();

               // Mask
               bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

               pOldSrc = graphicsSrc->SelectObject(const_cast<::ca::bitmap *>(&rSrc));
               pOldMask = graphicsMask->SelectObject(bmpMask);

               ASSERT(pOldSrc && pOldMask);
               if(!pOldSrc || !pOldMask)
                  return;

               // Make the upper left corner pixel of the source a "transparent" color
               cr = graphicsSrc->SetBkColor(graphicsSrc->GetPixel(0, 0));
               graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCCOPY);
               // Make white pixels of the source "transparent" too
               graphicsSrc->SetBkColor(RGB(255, 255, 255));
               graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCPAINT);
               graphicsSrc->SetBkColor(cr);

               // Checker the background with white and crBackground
               pDest = graphicsDest->SelectObject(pDest);
               ASSERT(pDest);
               if(pDest)
               {
                  cr1 = graphicsDest->SetTextColor(cr1);
                  cr2 = graphicsDest->SetBkColor(cr2);
                  graphicsDest->FillRect(rect(0, 0, bm.bmWidth, bm.bmHeight), &brChecker);
                  graphicsDest->SetTextColor(cr1);
                  graphicsDest->SetBkColor(cr2);

                  // Blt it
                  graphicsDest->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);
                  graphicsDest->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, SRCAND);
                  graphicsDest->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);
               }
               graphicsDest->SelectObject(pDest);
               graphicsMask->SelectObject(pOldMask);
               graphicsSrc->SelectObject(pOldSrc);
            }
         }
      }
   }

   void AfxDrawDitheredBitmap(::ca::application * papp, ::ca::graphics * pgraphics, int x, int y, const ::ca::bitmap &rSrc, COLORREF cr1, COLORREF cr2)
   {
      ASSERT(pgraphics);
      ASSERT_KINDOF(::ca::graphics_sp, pgraphics);

      BITMAP bm;
      ::ca::graphics_sp graphicsSrc, graphicsMask;
      COLORREF cr;
      ::ca::bitmap_sp bmpMask(papp);
      ::ca::bitmap *pOldMask, *pOldSrc;
      ::ca::brush brChecker;
      static const WORD wPat[8] = {0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa};

      if(graphicsSrc->CreateCompatibleDC(pgraphics) &&
         graphicsMask->CreateCompatibleDC(pgraphics) &&
         const_cast<::ca::bitmap &>(rSrc).GetBitmap(&bm))
      {
         // create checker brush
         bmpMask->CreateBitmap(8, 8, 1, 1, wPat);
         brChecker.CreatePatternBrush(bmpMask);
         bmpMask->delete_object();

         // Mask
         bmpMask->CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

         pOldSrc = graphicsSrc->SelectObject(const_cast<::ca::bitmap *>(&rSrc));
         pOldMask = graphicsMask->SelectObject(bmpMask);

         ASSERT(pOldSrc && pOldMask);
         if(!pOldSrc || !pOldMask)
            return;

         // Make the upper left corner pixel of the source a "transparent" color
         cr = graphicsSrc->SetBkColor(graphicsSrc->GetPixel(0, 0));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCCOPY);
         // Make white pixels of the source "transparent" too
         graphicsSrc->SetBkColor(RGB(255, 255, 255));
         graphicsMask->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCPAINT);
         graphicsSrc->SetBkColor(cr);

         // Checker the background with white and crBackground
         cr1 = pgraphics->SetTextColor(cr1);
         cr2 = pgraphics->SetBkColor(cr2);
         pgraphics->FillRect(rect(x, y, x + bm.bmWidth, y + bm.bmHeight), &brChecker);
         pgraphics->SetTextColor(cr1);
         pgraphics->SetBkColor(cr2);

         // Blt it
         pgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);
         pgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsMask, 0, 0, SRCAND);
         pgraphics->BitBlt(x, y, bm.bmWidth, bm.bmHeight, graphicsSrc, 0, 0, SRCINVERT);

         graphicsMask->SelectObject(pOldMask);
         graphicsSrc->SelectObject(pOldSrc);
      }
   }

   BOOL pen::CreatePen(int nPenStyle, int nWidth, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(nPenStyle);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(crColor);
      throw interface_only_exception();
   }

   BOOL pen::CreatePenIndirect(LPLOGPEN lpLogPen)
   {
      UNREFERENCED_PARAMETER(lpLogPen);
      throw interface_only_exception();
   }

   BOOL pen::CreatePen(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush, int nStyleCount, const DWORD* lpStyle)
   {
      UNREFERENCED_PARAMETER(nPenStyle);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(pLogBrush);
      UNREFERENCED_PARAMETER(nStyleCount);
      UNREFERENCED_PARAMETER(lpStyle);
      throw interface_only_exception();
   }

   int pen::GetExtLogPen(EXTLOGPEN * pLogPen)
   {
      UNREFERENCED_PARAMETER(pLogPen);
      throw interface_only_exception();
   }

   int pen::GetLogPen(LOGPEN* pLogPen)
   {
      UNREFERENCED_PARAMETER(pLogPen);
      throw interface_only_exception();
   }

   } // namespace ca