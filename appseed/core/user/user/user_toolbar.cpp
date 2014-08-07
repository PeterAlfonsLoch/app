#include "framework.h"

/*
UINT HashKey(string & okey)
{
   const char * key = okey;
   UINT nHash = 0;
   while (*key)
      nHash = (nHash<<5) + nHash + *key++;
   return nHash;
}
*/


/*
   DIBs use RGBQUAD format:
      0xbb 0xgg 0xrr 0x00

   Reasonably efficient code to convert a COLORREF into an
   RGBQUAD is byte-order-dependent, so we need different
   code depending on the byte order we're targeting.
*/
#define RGB_TO_RGBQUAD(r,g,b)   (RGB(b,g,r))
#define CLR_TO_RGBQUAD(clr)     (RGB(rgba_get_b(clr), rgba_get_g(clr), rgba_get_r(clr)))

struct __COLORMAP
{
   // use uint32_t instead of RGBQUAD so we can compare two RGBQUADs easily
   uint32_t rgbqFrom;
   int32_t iSysColorTo;
};

//static const __COLORMAP gen_SysColorMap[] =
//{
   // mapping from color in DIB to system color
  // { RGB_TO_RGBQUAD(0x00, 0x00, 0x00),  COLOR_BTNTEXT },       // black
   //{ RGB_TO_RGBQUAD(0x80, 0x80, 0x80),  COLOR_BTNSHADOW },     // dark gray
   //{ RGB_TO_RGBQUAD(0xC0, 0xC0, 0xC0),  COLOR_BTNFACE },       // bright gray
   //{ RGB_TO_RGBQUAD(0xFF, 0xFF, 0xFF),  COLOR_BTNHIGHLIGHT }   // white
//};



namespace user
{

   tool_bar::tool_bar()
   {
          m_bSimpleLayout = true;

      // initialize state
      m_pStringMap = NULL;

      m_bDelayedButtonLayout = TRUE;

      // default image sizes
      m_sizeImage.cx = 16;
      m_sizeImage.cy = 15;

      // default button sizes
      m_sizeButton.cx = 23;
      m_sizeButton.cy = 22;

      // top and bottom borders are 1 larger than default for ease of grabbing
      m_cyTopBorder = 3;
      m_cyBottomBorder = 3;
   }

   tool_bar::~tool_bar()
   {
//#ifdef WINDOWSEX
//      ::DeleteObject((HGDIOBJ*)&m_hbmImageWell);
//#else
  //    throw todo(get_app());
//#endif
      delete m_pStringMap;

      //m_nCount = 0;
   }

   void tool_bar::install_message_handling(::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_NCHITTEST         , pinterface, this, &tool_bar::_001OnNcHitTest);
      //IGUI_WIN_MSG_LINK(WM_NCPAINT         , pinterface, this, &tool_bar::_001On);
      //IGUI_WIN_MSG_LINK(WM_PAINT           , pinterface, this, &tool_bar::_001On);
      //IGUI_WIN_MSG_LINK(WM_ERASEBKGND      , pinterface, this, &tool_bar::_001On);
      IGUI_WIN_MSG_LINK(WM_NCCALCSIZE        , pinterface, this, &tool_bar::_001OnNcCalcSize);
      IGUI_WIN_MSG_LINK(WM_WINDOWPOSCHANGING , pinterface, this, &tool_bar::_001OnWindowPosChanging);
      IGUI_WIN_MSG_LINK(WM_NCCREATE          , pinterface, this, &tool_bar::_001OnNcCreate);
#ifdef WINDOWSEX
      IGUI_WIN_MSG_LINK(TB_SETBITMAPSIZE     , pinterface, this, &tool_bar::_001OnSetBitmapSize);
      IGUI_WIN_MSG_LINK(TB_SETBUTTONSIZE     , pinterface, this, &tool_bar::_001OnSetButtonSize);
#endif
      IGUI_WIN_MSG_LINK(WM_SETTINGCHANGE     , pinterface, this, &tool_bar::_001OnPreserveZeroBorderHelper);
      IGUI_WIN_MSG_LINK(WM_SETFONT           , pinterface, this, &tool_bar::_001OnPreserveZeroBorderHelper);
      IGUI_WIN_MSG_LINK(WM_SYSCOLORCHANGE    , pinterface, this, &tool_bar::_001OnSysColorChange);
   }

   bool tool_bar::create_window(sp(::user::interaction) pParentWnd,uint32_t dwStyle,UINT nID)
   {
      return create_window_ex(pParentWnd, 0, dwStyle,
         rect(m_cxLeftBorder, m_cyTopBorder, m_cxRightBorder, m_cyBottomBorder), nID);
   }

   bool tool_bar::create_window_ex(sp(::user::interaction) pParentWnd,uint32_t dwCtrlStyle,uint32_t dwStyle,LPCRECT lpcrect,UINT nID)
   {
      ASSERT_VALID(pParentWnd);   // must have a parent
      ASSERT (!((dwStyle & CBRS_SIZE_FIXED) && (dwStyle & CBRS_SIZE_DYNAMIC)));

      SetBorders(lpcrect);

      // save the style
      m_dwStyle = (dwStyle & CBRS_ALL);
      if (nID == __IDW_TOOLBAR)
         m_dwStyle |= CBRS_HIDE_INPLACE;

      dwStyle &= ~CBRS_ALL;
      dwStyle |= CCS_NOPARENTALIGN|CCS_NOMOVEY|CCS_NODIVIDER|CCS_NORESIZE;


      if (!::user::interaction::create_window(TOOLBARCLASSNAME, NULL, dwStyle, lpcrect, pParentWnd, nID))
         return FALSE;

      // sync up the sizes
      SetSizes(m_sizeButton, m_sizeImage);

      // Note: Parent must resize itself for control bar to be resized

      return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // tool_bar

   void tool_bar::_001OnNcCreate(signal_details * pobj)
   {
      if(pobj->previous())
         return;

      // if the owner was set before the toolbar was created, set it now
#ifdef WINDOWSEX
      if (m_puiOwner != NULL)
         DefWindowProc(TB_SETPARENT, (WPARAM)m_puiOwner, 0);

      DefWindowProc(TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
#else
      throw todo(get_app());

#endif
   }

   sp(::user::interaction) tool_bar::SetOwner(sp(::user::interaction) pOwnerWnd)
   {
#ifdef WINDOWSEX
      ASSERT_VALID(this);
      ASSERT(IsWindow());
      DefWindowProc(TB_SETPARENT, (WPARAM)pOwnerWnd.m_p, 0);
#else
      throw todo(get_app());

#endif
      return ::user::control_bar::SetOwner(pOwnerWnd);
   }

   void tool_bar::SetSizes(SIZE sizeButton, SIZE sizeImage)
   {
      ASSERT_VALID(this);

      // sizes must be non-zero and positive
      ASSERT(sizeButton.cx > 0 && sizeButton.cy > 0);
      ASSERT(sizeImage.cx > 0 && sizeImage.cy > 0);

      // button must be big enough to hold image
      //   + 7 pixels on x
      //   + 6 pixels on y
      ASSERT(sizeButton.cx >= sizeImage.cx + 7);
      ASSERT(sizeButton.cy >= sizeImage.cy + 6);

      if (IsWindow())
      {
         // set the sizes via TB_SETBITMAPSIZE and TB_SETBUTTONSIZE
#ifdef WINDOWSEX
         VERIFY(send_message(TB_SETBITMAPSIZE, 0, MAKELONG(sizeImage.cx, sizeImage.cy)));
         VERIFY(send_message(TB_SETBUTTONSIZE, 0, MAKELONG(sizeButton.cx, sizeButton.cy)));
#else
         throw todo(get_app());
#endif
         Invalidate();   // just to be nice if called when toolbar is visible
      }
      else
      {
         // just set our internal values for later
         m_sizeButton = sizeButton;
         m_sizeImage = sizeImage;
      }
   }

   void tool_bar::SetHeight(int32_t cyHeight)
   {
      ASSERT_VALID(this);

      int32_t nHeight = cyHeight;
      if (m_dwStyle & CBRS_BORDER_TOP)
//         cyHeight -= afxData.cyBorder2;
            cyHeight -= 2;
      if (m_dwStyle & CBRS_BORDER_BOTTOM)
         //cyHeight -= afxData.cyBorder2;
         cyHeight -= 2;

      m_cyBottomBorder = (cyHeight - m_sizeButton.cy) / 2;
      // if there is an extra pixel, m_cyTopBorder will get it
      m_cyTopBorder = cyHeight - m_sizeButton.cy - m_cyBottomBorder;
      if (m_cyTopBorder < 0)
      {
         TRACE1("Warning: tool_bar::SetHeight(%d) is smaller than button.\n",
            nHeight);
         m_cyBottomBorder += m_cyTopBorder;
         m_cyTopBorder = 0;  // will clip at bottom
      }

      // recalculate the non-client region
      SetWindowPos(0, 0, 0, 0, 0, SWP_DRAWFRAME|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER);
      Invalidate();   // just to be nice if called when toolbar is visible
   }


   /*bool tool_bar::LoadToolBar(const char * lpszResourceName)
   {
      ASSERT_VALID(this);
      ASSERT(lpszResourceName != NULL);

      // determine location of the bitmap in resource fork
      HINSTANCE hInst = ::core::FindResourceHandle(lpszResourceName, RT_TOOLBAR);
      HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, RT_TOOLBAR);
      if (hRsrc == NULL)
         return FALSE;

      HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
      if (hGlobal == NULL)
         return FALSE;

      tool_bar_data* pData = (tool_bar_data*)LockResource(hGlobal);
      if (pData == NULL)
         return FALSE;
      ASSERT(pData->wVersion == 1);

      UINT* pItems = new UINT[pData->wItemCount];
      for (int32_t i = 0; i < pData->wItemCount; i++)
         pItems[i] = pData->items()[i];
      bool bResult = SetButtons(pItems, pData->wItemCount);
      delete[] pItems;


      if (bResult)
      {

         // set new sizes of the buttons
         size sizeImage(pData->wWidth, pData->wHeight);
         size sizeButton(pData->wWidth + 7, pData->wHeight + 7);
         SetSizes(sizeButton, sizeImage);

         // load bitmap now that sizes are known by the toolbar control
         bResult = LoadBitmap(lpszResourceName);
      }

      UnlockResource(hGlobal);
      FreeResource(hGlobal);

      return bResult;
   }*/

   /*bool tool_bar::LoadBitmap(const char * lpszResourceName)
   {
      ASSERT_VALID(this);
      ASSERT(lpszResourceName != NULL);

      // determine location of the bitmap in resource fork
      HINSTANCE hInstImageWell = ::core::FindResourceHandle(lpszResourceName, RT_BITMAP);
      HRSRC hRsrcImageWell = ::FindResource(hInstImageWell, lpszResourceName, RT_BITMAP);
      if (hRsrcImageWell == NULL)
         return FALSE;

      // load the bitmap
      HBITMAP hbmImageWell;
   //   hbmImageWell = ::core::LoadSysColorBitmap(hInstImageWell, hRsrcImageWell);
      ::draw2d::memory_graphics pdc(this);
      hbmImageWell = imaging::LoadSysColorBitmap(pdc, hInstImageWell, hRsrcImageWell);


      // tell common control toolbar about the new bitmap
      if (!AddReplaceBitmap(hbmImageWell))
         return FALSE;

      // remember the resource handles so the bitmap can be recolored if necessary
      m_hInstImageWell = hInstImageWell;
      m_hRsrcImageWell = hRsrcImageWell;
      return TRUE;
   }*/

   bool tool_bar::from(HBITMAP hbmImageWell)
   {
      ASSERT_VALID(this);
      ASSERT(hbmImageWell != NULL);

      // the caller must manage changing system colors
//      m_hInstImageWell = NULL;
  //    m_hRsrcImageWell = NULL;

      // tell common control toolbar about the new bitmap
      return AddReplaceBitmap(hbmImageWell);
   }

   bool tool_bar::AddReplaceBitmap(HBITMAP hbmImageWell)
   {
            bool bResult = false;

      // need complete bitmap size to determine number of images
/*#ifdef WINDOWSEX
      BITMAP bitmap;
      VERIFY(::GetObject(hbmImageWell, sizeof(BITMAP), &bitmap));

      // add the bitmap to the common control toolbar
      if (m_hbmImageWell == NULL)
      {
         TBADDBITMAP addBitmap;
         addBitmap.hInst = NULL; // makes TBADDBITMAP::nID behave a HBITMAP
         addBitmap.nID = (UINT)hbmImageWell;
         bResult =  DefWindowProc(TB_ADDBITMAP,
            bitmap.bmWidth / m_sizeImage.cx, (LPARAM)&addBitmap) == 0;
      }
      else
      {
         TBREPLACEBITMAP replaceBitmap;
         replaceBitmap.hInstOld = NULL;
         replaceBitmap.nIDOld = (UINT)m_hbmImageWell;
         replaceBitmap.hInstNew = NULL;
         replaceBitmap.nIDNew = (UINT)hbmImageWell;
         replaceBitmap.nButtons = bitmap.bmWidth / m_sizeImage.cx;
         bResult = DefWindowProc(TB_REPLACEBITMAP, 0, (LPARAM)&replaceBitmap) != FALSE;
      }
      // remove old bitmap, if present
      if (bResult)
      {
         ::DeleteObject((HGDIOBJ*)&m_hbmImageWell);
         m_hbmImageWell = hbmImageWell;
      }
#else
      throw todo(get_app());
#endif*/
      return bResult;
   }

   bool tool_bar::SetButtons(const UINT* lpIDArray, int32_t nIDCount)
   {
#ifdef WINDOWSEX
      ASSERT_VALID(this);
      ASSERT(nIDCount >= 1);  // must be at least one of them
      ASSERT(lpIDArray == NULL || __is_valid_address(lpIDArray, sizeof(UINT) * nIDCount, FALSE));

      // delete all existing buttons
      int32_t nCount = (int32_t)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
      while (nCount--)
         VERIFY(DefWindowProc(TB_DELETEBUTTON, 0, 0));

      TBBUTTON button; memset(&button, 0, sizeof(TBBUTTON));
      button.iString = -1;
      if (lpIDArray != NULL)
      {
         // add new buttons to the common control
         int32_t iImage = 0;
         for (int32_t i = 0; i < nIDCount; i++)
         {
            button.fsState = TBSTATE_ENABLED;
            if ((button.idCommand = *lpIDArray++) == 0)
            {
               // separator
               button.fsStyle = TBSTYLE_SEP;
               // width of separator includes 8 pixel overlap
               if ((GetStyle() & TBSTYLE_FLAT))
                  button.iBitmap = 6;
               else
                  button.iBitmap = 8;
            }
            else
            {
               // a command button with image
               button.fsStyle = TBSTYLE_BUTTON;
               button.iBitmap = iImage++;
            }
            if (!DefWindowProc(TB_ADDBUTTONS, 1, (LPARAM)&button))
               return FALSE;
         }
      }
      else
      {
         // add 'blank' buttons
         button.fsState = TBSTATE_ENABLED;
         for (int32_t i = 0; i < nIDCount; i++)
         {
            ASSERT(button.fsStyle == TBSTYLE_BUTTON);
            if (!DefWindowProc(TB_ADDBUTTONS, 1, (LPARAM)&button))
               return FALSE;
         }
      }
   //   m_nCount = (int32_t)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
      m_bDelayedButtonLayout = TRUE;
#else
      throw todo(get_app());
#endif
      return TRUE;
   }


   /////////////////////////////////////////////////////////////////////////////
   // tool_bar attribute access
#ifdef WINDOWSEX
   void tool_bar::_GetButton(::index nIndex, TBBUTTON* pButton) const
   {
      tool_bar* pBar = (tool_bar*)this;
      VERIFY(pBar->DefWindowProc(TB_GETBUTTON, nIndex, (LPARAM)pButton));
      // TBSTATE_ENABLED == TBBS_DISABLED so invert it
      pButton->fsState ^= TBSTATE_ENABLED;
   }

   void tool_bar::_SetButton(::index nIndex, TBBUTTON* pButton)
   {
      // get original button state
      TBBUTTON button;
      VERIFY(DefWindowProc(TB_GETBUTTON, nIndex, (LPARAM)&button));

      // prepare for old/new button comparsion
      button.bReserved[0] = 0;
      button.bReserved[1] = 0;
      // TBSTATE_ENABLED == TBBS_DISABLED so invert it
      pButton->fsState ^= TBSTATE_ENABLED;
      pButton->bReserved[0] = 0;
      pButton->bReserved[1] = 0;

      // nothing to do if they are the same
      if (memcmp(pButton, &button, sizeof(TBBUTTON)) != 0)
      {
         // don't redraw everything while setting the button
         uint32_t dwStyle = GetStyle();
         ModifyStyle(WS_VISIBLE, 0);
         VERIFY(DefWindowProc(TB_DELETEBUTTON, nIndex, 0));
         VERIFY(DefWindowProc(TB_INSERTBUTTON, nIndex, (LPARAM)pButton));
         ModifyStyle(0, dwStyle & WS_VISIBLE);

         // invalidate appropriate parts
         if (((pButton->fsStyle ^ button.fsStyle) & TBSTYLE_SEP) ||
            ((pButton->fsStyle & TBSTYLE_SEP) && pButton->iBitmap != button.iBitmap))
         {
            // changing a separator
            Invalidate();
         }
         else
         {
            // invalidate just the button
            rect rect;
            if (DefWindowProc(TB_GETITEMRECT, nIndex, (LPARAM)&rect))
               InvalidateRect(rect);
         }
      }
   }

#endif

   int32_t tool_bar::CommandToIndex(UINT nIDFind)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

#ifdef WINDOWSEX
      tool_bar* pBar = (tool_bar*)this;
      return (int32_t)pBar->DefWindowProc(TB_COMMANDTOINDEX, nIDFind, 0);
#else
      throw todo(get_app());
#endif
   }

   UINT tool_bar::GetItemID(int32_t nIndex)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

#ifdef WINDOWSEX
      TBBUTTON button;
      _GetButton(nIndex, &button);
      return button.idCommand;
#else
      throw todo(get_app());
#endif
   }

   void tool_bar::GetItemRect(int32_t nIndex, LPRECT lpRect)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      // handle any delayed layout
      if (m_bDelayedButtonLayout)
         ((tool_bar*)this)->layout();

      // now it is safe to get the item rectangle
#ifdef WINDOWSEX
      tool_bar* pBar = (tool_bar*)this;
      if (!pBar->DefWindowProc(TB_GETITEMRECT, nIndex, (LPARAM)lpRect))
         ::SetRectEmpty(lpRect);
#else
      throw todo(get_app());
#endif
   }

   void tool_bar::layout()
   {
      ASSERT(m_bDelayedButtonLayout);

      m_bDelayedButtonLayout = FALSE;

      bool bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
      if(m_bSimpleLayout)
         CalcSimpleLayout();
      else if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
         ((tool_bar*)this)->CalcDynamicLayout(0, LM_HORZ | LM_MRUWIDTH | LM_COMMIT);
      else if (bHorz)
         ((tool_bar*)this)->CalcDynamicLayout(0, LM_HORZ | LM_HORZDOCK | LM_COMMIT);
      else
         ((tool_bar*)this)->CalcDynamicLayout(0, LM_VERTDOCK | LM_COMMIT);
   }

   UINT tool_bar::GetButtonStyle(int32_t nIndex)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

#ifdef WINDOWSEX
      TBBUTTON button;
      _GetButton(nIndex, &button);
      return MAKELONG(button.fsStyle, button.fsState);
#else
      throw todo(get_app());
#endif
   }

   void tool_bar::SetButtonStyle(int32_t nIndex, UINT nStyle)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

#ifdef WINDOWSEX
      TBBUTTON button;
      _GetButton(nIndex, &button);
      if (button.fsStyle != (BYTE)LOWORD(nStyle) || button.fsState != (BYTE)HIWORD(nStyle))
      {
         button.fsStyle = (BYTE)LOWORD(nStyle);
         button.fsState = (BYTE)HIWORD(nStyle);
         _SetButton(nIndex, &button);
         m_bDelayedButtonLayout = TRUE;
      }
#else
      throw todo(get_app());
#endif
   }

   #define CX_OVERLAP  0

#ifdef WINDOWSEX
   size tool_bar::CalcSize(TBBUTTON* pData, int32_t nCount)
   {
      ASSERT(pData != NULL && nCount > 0);

      point cur(0,0);
      size sizeResult(0,0);

      uint32_t dwExtendedStyle = (uint32_t) DefWindowProc(TB_GETEXTENDEDSTYLE, 0, 0);

      for (int32_t i = 0; i < nCount; i++)
      {
         //WINBUG: The IE4 version of COMCTL32.DLL calculates the separation
         //  on a TBSTYLE_WRAP button as 100% of the value in iBitmap compared
         //  to the other versions which calculate it at 2/3 of that value.
         //  This is actually a bug which should be fixed in IE 4.01, so we
         //  only do the 100% calculation specifically for IE4.
         int32_t cySep = pData[i].iBitmap;
         if (!(GetStyle() & TBSTYLE_FLAT))
            cySep = cySep * 2 / 3;

         if (pData[i].fsState & TBSTATE_HIDDEN)
            continue;

         int32_t cx = m_sizeButton.cx;
         if (pData[i].fsStyle & TBSTYLE_SEP)
         {
            // a separator represents either a height or width
            if (pData[i].fsState & TBSTATE_WRAP)
               sizeResult.cy = max(cur.y + m_sizeButton.cy + cySep, sizeResult.cy);
            else
               sizeResult.cx = max(cur.x + pData[i].iBitmap, sizeResult.cx);
         }
         else
         {
            // check for dropdown style, but only if the buttons are being drawn
            if ((pData[i].fsStyle & TBSTYLE_DROPDOWN) &&
               (dwExtendedStyle & TBSTYLE_EX_DRAWDDARROWS))
            {
               // add size of drop down
               cx += 2;
            }
            sizeResult.cx = max(cur.x + cx, sizeResult.cx);
            sizeResult.cy = max(cur.y + m_sizeButton.cy, sizeResult.cy);
         }

         if (pData[i].fsStyle & TBSTYLE_SEP)
            cur.x += pData[i].iBitmap;
         else
            cur.x += cx - CX_OVERLAP;

         if (pData[i].fsState & TBSTATE_WRAP)
         {
            cur.x = 0;
            cur.y += m_sizeButton.cy;
            if (pData[i].fsStyle & TBSTYLE_SEP)
               cur.y += cySep;
         }
      }
      return sizeResult;
   }

   int32_t tool_bar::WrapToolBar(TBBUTTON* pData, int32_t nCount, int32_t nWidth)
   {

      ASSERT(pData != NULL && nCount > 0);

      ::draw2d::memory_graphics pdc(allocer());

      int32_t nResult = 0;
      int32_t x = 0;
      string str;
      for (int32_t i = 0; i < nCount; i++)
      {
         pData[i].fsState &= ~TBSTATE_WRAP;

         if (pData[i].fsState & TBSTATE_HIDDEN)
            continue;
         GetButtonText(i, str);
         int32_t dx, dxNext;
         if (pData[i].fsStyle & TBSTYLE_SEP)
         {
            dx = pData[i].iBitmap;
            dxNext = dx;
         }
         else if (!str.is_empty())
         {
            dx = m_sizeButton.cx;
            string str;
            str = ::str::international::utf8_to_unicode(str);
   //         str = (const wchar_t *) pData[i].iString;
            size size;
            ::GetTextExtentPoint32U(
               (HDC)pdc->get_os_data(),
               str,
               (int32_t) str.get_length(),
               &size);
            dx += size.cx;
            dxNext = dx - CX_OVERLAP;
         }
         else
         {
            dx = m_sizeButton.cx;
            dxNext = dx - CX_OVERLAP;
         }

         if (x + dx > nWidth)
         {
            bool bFound = FALSE;
            for (int32_t j = i; j >= 0  &&  !(pData[j].fsState & TBSTATE_WRAP); j--)
            {
               // find last separator that isn't hidden
               // a separator that has a command ID is not
               // a separator, but a custom control.
               if ((pData[j].fsStyle & TBSTYLE_SEP) &&
                  (pData[j].idCommand == 0) &&
                  !(pData[j].fsState & TBSTATE_HIDDEN))
               {
                  bFound = TRUE; i = j; x = 0;
                  pData[j].fsState |= TBSTATE_WRAP;
                  nResult++;
                  break;
               }
            }
            if (!bFound)
            {
               for (int32_t j = i - 1; j >= 0 && !(pData[j].fsState & TBSTATE_WRAP); j--)
               {
                  // Never wrap anything that is hidden,
                  // or any custom controls
                  if ((pData[j].fsState & TBSTATE_HIDDEN) ||
                     ((pData[j].fsStyle & TBSTYLE_SEP) &&
                     (pData[j].idCommand != 0)))
                     continue;

                  bFound = TRUE; i = j; x = 0;
                  pData[j].fsState |= TBSTATE_WRAP;
                  nResult++;
                  break;
               }
               if (!bFound)
                  x += dxNext;
            }
         }
         else
            x += dxNext;
      }

      return nResult + 1;
   }

   void  tool_bar::SizeToolBar(TBBUTTON* pData, int32_t nCount, int32_t nLength, bool bVert)
   {
      ASSERT(pData != NULL && nCount > 0);

      if (!bVert)
      {
         int32_t nMin, nMax, nTarget, nCurrent, nMid;

         // Wrap ToolBar as specified
         nMax = nLength;
         nTarget = WrapToolBar(pData, nCount, nMax);

         // Wrap ToolBar vertically
         nMin = 0;
         nCurrent = WrapToolBar(pData, nCount, nMin);

         if (nCurrent != nTarget)
         {
            while (nMin < nMax)
            {
               nMid = (nMin + nMax) / 2;
               nCurrent = WrapToolBar(pData, nCount, nMid);

               if (nCurrent == nTarget)
                  nMax = nMid;
               else
               {
                  if (nMin == nMid)
                  {
                     WrapToolBar(pData, nCount, nMax);
                     break;
                  }
                  nMin = nMid;
               }
            }
         }
         size size = CalcSize(pData, nCount);
         WrapToolBar(pData, nCount, size.cx);
      }
      else
      {
         size sizeMax, sizeMin, sizeMid;

         // Wrap ToolBar vertically
         WrapToolBar(pData, nCount, 0);
         sizeMin = CalcSize(pData, nCount);

         // Wrap ToolBar horizontally
         WrapToolBar(pData, nCount, 32767);
         sizeMax = CalcSize(pData, nCount);

         while (sizeMin.cx < sizeMax.cx)
         {
            sizeMid.cx = (sizeMin.cx + sizeMax.cx) / 2;
            WrapToolBar(pData, nCount, sizeMid.cx);
            sizeMid = CalcSize(pData, nCount);

            if (nLength < sizeMid.cy)
            {
               if (sizeMin == sizeMid)
               {
                  WrapToolBar(pData, nCount, sizeMax.cx);
                  return;
               }
               sizeMin = sizeMid;
            }
            else if (nLength > sizeMid.cy)
               sizeMax = sizeMid;
            else
               return;
         }
      }
   }
#endif
   struct ___CONTROLPOS
   {
      int32_t nIndex, nID;
      rect rectOldPos;
   };

   size tool_bar::CalcLayout(uint32_t dwMode, int32_t nLength)
   {
#ifdef WINDOWSEX
      ASSERT_VALID(this);
      ASSERT(IsWindow());
      if (dwMode & LM_HORZDOCK)
         ASSERT(dwMode & LM_HORZ);

      int32_t nCount;
      TBBUTTON* pData = NULL;
      size sizeResult(0,0);

      //BLOCK: Load Buttons
      {
         nCount = (int32_t) DefWindowProc(TB_BUTTONCOUNT, 0, 0);
         if (nCount != 0)
         {
            int32_t i;
            pData = new TBBUTTON[nCount];
            for (i = 0; i < nCount; i++)
               _GetButton(i, &pData[i]);
         }
      }

      if (nCount > 0)
      {
         if (!(m_dwStyle & CBRS_SIZE_FIXED))
         {
            bool bDynamic = (m_dwStyle & CBRS_SIZE_DYNAMIC) != 0;

            if (bDynamic && (dwMode & LM_MRUWIDTH))
               SizeToolBar(pData, nCount, m_nMRUWidth);
            else if (bDynamic && (dwMode & LM_HORZDOCK))
               SizeToolBar(pData, nCount, 32767);
            else if (bDynamic && (dwMode & LM_VERTDOCK))
               SizeToolBar(pData, nCount, 0);
            else if (bDynamic && (nLength != -1))
            {
               class rect rect;
               rect.null();
               CalcInsideRect(rect, (dwMode & LM_HORZ) != 0);
               bool bVert = (dwMode & LM_LENGTHY) != 0;
               int32_t nLen = nLength + (bVert ? rect.height() : rect.width());

               SizeToolBar(pData, nCount, nLen, bVert);
            }
            else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
               SizeToolBar(pData, nCount, m_nMRUWidth);
            else
               SizeToolBar(pData, nCount, (dwMode & LM_HORZ) ? 32767 : 0);
         }

         sizeResult = CalcSize(pData, nCount);

         if (dwMode & LM_COMMIT)
         {
            ___CONTROLPOS* pControl = NULL;
            int32_t nControlCount = 0;
            bool bIsDelayed = m_bDelayedButtonLayout;
            m_bDelayedButtonLayout = FALSE;

            int32_t i;
            for (i = 0; i < nCount; i++)
               if ((pData[i].fsStyle & TBSTYLE_SEP) && (pData[i].idCommand != 0))
                  nControlCount++;

            if (nControlCount > 0)
            {
               pControl = new ___CONTROLPOS[nControlCount];
               nControlCount = 0;

               for(int32_t i = 0; i < nCount; i++)
               {
                  if ((pData[i].fsStyle & TBSTYLE_SEP) && (pData[i].idCommand != 0))
                  {
                     pControl[nControlCount].nIndex = i;
                     pControl[nControlCount].nID = pData[i].idCommand;

                     rect rect;
                     GetItemRect(i, &rect);
                     ClientToScreen(&rect);
                     pControl[nControlCount].rectOldPos = rect;

                     nControlCount++;
                  }
               }
            }

               //::draw2d::memory_graphics pdc(this);
            string str;
            if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
               m_nMRUWidth = sizeResult.cx;
            for (i = 0; i < nCount; i++)
            {
               _SetButton(i, &pData[i]);
   //            GetButtonText(i, str);
   //            size size;
   //            if(!str.is_empty())
   //            {
   //               ::GetTextExtentPointW(
   //                  (HDC)pdc->get_os_data(),
   //                  str,
   //                  str.get_length(),
   //                  &size);
   //               size.cx += m_sizeButton.cx;
   //            }
   //            else
   //            {
   //               size = m_sizeImage;
   //            }
   //            TBBUTTONINFOW button;
   //            memset(&button, 0, sizeof(button));
   //            button.cbSize = sizeof(button);
   //            button.dwMask =
   //               TBIF_COMMAND
   //               | TBIF_SIZE  ;
   //            button.cx = size.cx;
   //            button.idCommand = i;
   //            GetToolBarCtrl().SetButtonInfo(i, &button);
            }
            for (i = 0; i < nCount; i++)
            {
               TBBUTTONINFOW buttona;
               memset(&buttona, 0, sizeof(buttona));
               buttona.cbSize = sizeof(buttona);
               buttona.dwMask =
                  TBIF_COMMAND
                  | TBIF_STYLE
                  | TBIF_SIZE;
               UINT uiID = GetItemID(i);
               GetToolBarCtrl().GetButtonInfo(uiID, &buttona);
               TRACE("BUTTON.idCommand = %d\n", buttona.idCommand  );
               TRACE("BUTTON.fsStyle = %d\n", buttona.fsStyle  );
               TRACE("BUTTON.cx = %d\n", buttona.cx );
            }

            if (nControlCount > 0)
            {
               for (int32_t i = 0; i < nControlCount; i++)
               {
                  sp(::user::interaction) pwindow = get_child_by_id(pControl[i].nID);
                  if (pwindow != NULL)
                  {
                     rect rect;
                     pwindow->GetWindowRect(&rect);
                     point pt = rect.top_left() - pControl[i].rectOldPos.top_left();
                     GetItemRect(pControl[i].nIndex, &rect);
                     pt = rect.top_left() + pt;
                     pwindow->SetWindowPos(0, pt.x, pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
                  }
               }
               delete[] pControl;
            }
            m_bDelayedButtonLayout = bIsDelayed;
         }
         delete[] pData;
      }

      //BLOCK: Adjust Margins
      {
         class rect rect;
         rect.null();
         CalcInsideRect(rect, (dwMode & LM_HORZ) != 0);
         sizeResult.cy -= rect.height();
         sizeResult.cx -= rect.width();

         size size = ::user::control_bar::CalcFixedLayout((dwMode & LM_STRETCH) != 0, (dwMode & LM_HORZ) != 0);
         sizeResult.cx = max(sizeResult.cx, size.cx);
         sizeResult.cy = max(sizeResult.cy, size.cy);
      }
      return sizeResult;
#else
throw todo(get_app());
#endif
   }

   size tool_bar::CalcFixedLayout(bool bStretch, bool bHorz)
   {
      uint32_t dwMode = bStretch ? LM_STRETCH : 0;
      dwMode |= bHorz ? LM_HORZ : 0;

      return CalcLayout(dwMode);
   }

   size tool_bar::CalcDynamicLayout(int32_t nLength, uint32_t dwMode)
   {
      if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
         ((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
      {
         return CalcFixedLayout((dwMode & LM_STRETCH) != 0, (dwMode & LM_HORZDOCK) != 0);
      }
      return CalcLayout(dwMode, nLength);
   }

   void tool_bar::GetButtonInfo(int32_t nIndex, UINT& nID, UINT& nStyle, int32_t& iImage)
   {
#ifdef WINDOWSEX
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      TBBUTTON button;
      _GetButton(nIndex, &button);
      nID = button.idCommand;
      nStyle = MAKELONG(button.fsStyle, button.fsState);
      iImage = button.iBitmap;
#else
      throw todo(get_app());
#endif
   }

   void tool_bar::SetButtonInfo(int32_t nIndex, UINT nID, UINT nStyle, int32_t iImage)
   {
      ASSERT_VALID(this);
#ifdef WINDOWSEX
      TBBUTTON button;
      _GetButton(nIndex, &button);
      TBBUTTON save;
      memcpy(&save, &button, sizeof(save));
      button.idCommand = nID;
      button.iBitmap = iImage;
      button.fsStyle = (BYTE)LOWORD(nStyle);
      button.fsState = (BYTE)HIWORD(nStyle);
      if (memcmp(&save, &button, sizeof(save)) != 0)
      {
         _SetButton(nIndex, &button);
         m_bDelayedButtonLayout = TRUE;
      }
#else
      throw todo(get_app());
#endif

   }


   bool tool_bar::SetButtonText(int32_t nIndex, const char * lpszText)
   {
      // attempt to lookup string index in map
      int_ptr nString = -1;
      void * p;
      string wstrText(lpszText);
      if (m_pStringMap != NULL && m_pStringMap->Lookup(wstrText, p))
         nString = (int_ptr)p;

      // add new string if not already in map
      if (nString == -1)
      {
         // initialize map if necessary
         if (m_pStringMap == NULL)
            m_pStringMap = new string_to_ptr;

         string str;
         str = lpszText;
         // add new string to toolbar list
         string strTemp(str, str.get_length());
         throw not_implemented(get_app());
         // xxx nString = (int32_t)DefWindowProc(TB_ADDSTRINGW, 0, (LPARAM)(const char *)(const wchar_t *)strTemp);
         if (nString == -1)
            return FALSE;

         // cache string away in string map
         m_pStringMap->set_at(wstrText, (void *)nString);
         ASSERT(m_pStringMap->Lookup(wstrText, p));
      }

      // change the toolbar button description

   //   TBBUTTONINFOW button;
   //   memset(&button, 0, sizeof(button));
   //   button.cbSize = sizeof(button);
   //   UINT uiID = GetItemID(nIndex);
   //   button.pszText = (wchar_t *) (const wchar_t *) wstrText;
   //   button.cchText = wstrText.get_length();
   //   button.dwMask |= TBIF_TEXT;
   //   GetToolBarCtrl().SetButtonInfo(uiID, &button);

   //   string str;
   //   GetButtonText(nIndex, str);
#ifdef WINDOWSEX
      TBBUTTON button;
      _GetButton(nIndex, &button);
      button.iString = nString;
      _SetButton(nIndex, &button);
      string str;
      GetButtonText(nIndex, str);
#else
      throw todo(get_app());
#endif

      return TRUE;
   }

   string tool_bar::GetButtonText(int32_t nIndex) const
   {
      string strResult;
      GetButtonText(nIndex, strResult);
      return strResult;
   }

   void tool_bar::GetButtonText(int32_t nIndex, string & rWString) const
   {
#ifdef WINDOWSEX
      if (m_pStringMap != NULL)
      {
         // get button information (need button.iString)
         TBBUTTON button;
         _GetButton(nIndex, &button);

         // look in map for matching iString
         POSITION pos = m_pStringMap->get_start_position();
         string str; void * p;
         while (pos)
         {
            m_pStringMap->get_next_assoc(pos, str, p);
            if ((int32_t)p == button.iString)
            {
               rWString = str;
               return;
            }
         }
      }
      rWString.Empty();
#else
      throw todo(get_app());
#endif
   }


   /*
   bool tool_bar::OnEraseBkgnd(::draw2d::graphics *)
   {
      return (bool)Default();
   }
   */

   void tool_bar::_001OnNcHitTest(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
      pbase->set_lresult(HTCLIENT);
      pbase->m_bRet = true;
   }

   void tool_bar::_001OnNcCalcSize(signal_details * pobj)
   {
#ifdef WINDOWSEX
      SCAST_PTR(::message::nc_calc_size, pnccalcsize, pobj)
      // calculate border space (will add to top/bottom, subtract from right/bottom)
      class rect rect;
      rect.null();
      bool bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
      ::user::control_bar::CalcInsideRect(rect, bHorz);

      // adjust non-client area for border space
      pnccalcsize->m_pparams->rgrc[0].left += rect.left;
      pnccalcsize->m_pparams->rgrc[0].top += rect.top;
      // previous versions of COMCTL32.DLL had a built-in 2 pixel border
      pnccalcsize->m_pparams->rgrc[0].right += rect.right;
      pnccalcsize->m_pparams->rgrc[0].bottom += rect.bottom;
#else
      throw todo(get_app());
#endif
   }

   void tool_bar::OnBarStyleChange(uint32_t dwOldStyle, uint32_t dwNewStyle)
   {
      // a dynamically resizeable toolbar can not have the CBRS_FLOAT_MULTI
      ASSERT(!((dwNewStyle & CBRS_SIZE_DYNAMIC) &&
            (m_dwDockStyle & CBRS_FLOAT_MULTI)));

      // a toolbar can not be both dynamic and fixed in size
      ASSERT (!((dwNewStyle & CBRS_SIZE_FIXED) &&
         (dwNewStyle & CBRS_SIZE_DYNAMIC)));

      // CBRS_SIZE_DYNAMIC can not be disabled once it has been enabled
      ASSERT (((dwOldStyle & CBRS_SIZE_DYNAMIC) == 0) ||
         ((dwNewStyle & CBRS_SIZE_DYNAMIC) != 0));

      if (((dwOldStyle & CBRS_BORDER_ANY) != (dwNewStyle & CBRS_BORDER_ANY)))
      {
         // recalc non-client area when border styles change
         SetWindowPos(0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
      }
      m_bDelayedButtonLayout = TRUE;
   }

   /*
   void tool_bar::OnNcPaint()
   {
      return;
      EraseNonClient();
   }
   */

   void tool_bar::_001OnWindowPosChanging(signal_details * pobj)
   {
#ifdef WINDOWSEX
      SCAST_PTR(::message::window_pos, pwindowpos, pobj)
      // not necessary to invalidate the borders
      uint32_t dwStyle = m_dwStyle;
      m_dwStyle &= ~(CBRS_BORDER_ANY);
      //::user::control_bar::OnWindowPosChanging(pwindowpos->m_pwindowpos);
      pobj->previous();
      m_dwStyle = dwStyle;

      // If we can resize while floating
      if (dwStyle & CBRS_SIZE_DYNAMIC)
      {
         // And we are resizing
         if (pwindowpos->m_pwindowpos->flags & SWP_NOSIZE)
            return;

         // Then redraw the buttons
         Invalidate();
      }
#else
      throw todo(get_app());
#endif
   }

   /*
   void tool_bar::OnPaint()
   {
      if (m_bDelayedButtonLayout)
         layout();

      Default();
   }
   */


   void tool_bar::_001OnDraw(::draw2d::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
      if (m_bDelayedButtonLayout)
         layout();

      Default();
   }


   void tool_bar::_001OnSetButtonSize(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
      pbase->set_lresult(OnSetSizeHelper(m_sizeButton, pbase->m_lparam));
   }

   void tool_bar::_001OnSetBitmapSize(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
      pbase->set_lresult(OnSetSizeHelper(m_sizeImage, pbase->m_lparam));
   }

   LRESULT tool_bar::OnSetSizeHelper(size& size, LPARAM lParam)
   {
      //WINBUG: The IE4 version of COMCTL32.DLL supports a zero border, but
      //  only if TBSTYLE_TRANSPARENT is on during the the TB_SETBITMAPSIZE
      //  and/or TB_SETBUTTONSIZE messages.  In order to enable this feature
      //  all the time (so we get consistent border behavior, dependent only
      //  on the version of COMCTL32.DLL) we turn on TBSTYLE_TRANSPARENT
      //  whenever these messages go through.  It would be nice that in a
      //  future version, the system toolbar would just allow you to set
      //  the top and left borders to anything you please.
      LRESULT lResult = 0;

#ifdef WINDOWSEX
      bool bModify = FALSE;
      uint32_t dwStyle = GetStyle();
      bModify = ModifyStyle(0, TBSTYLE_TRANSPARENT|TBSTYLE_FLAT);

      lResult = Default();
      if (lResult)
         size = (uint32_t) lParam;

      if (bModify)
         set_window_long(GWL_STYLE, dwStyle);
#else
      throw todo(get_app());
#endif
      return lResult;
   }

   void tool_bar::_001OnPreserveZeroBorderHelper(signal_details * pobj)
   {
      LRESULT lResult = 0;
      SCAST_PTR(::message::base, pbase, pobj)
#ifdef LRESULT

      bool bModify = FALSE;
      uint32_t dwStyle = 0;
      dwStyle = GetStyle();
      bModify = ModifyStyle(0, TBSTYLE_TRANSPARENT|TBSTYLE_FLAT);

      lResult = Default();

      if (bModify)
         SetWindowLong(GWL_STYLE, dwStyle);
#else
      throw todo(get_app());
#endif

      pbase->set_lresult(lResult);
   }

   void tool_bar::_001OnSysColorChange(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      // re-color bitmap for toolbar
//      if (m_hInstImageWell != NULL && m_hbmImageWell != NULL)
      {
   // trans      HBITMAP hbmNew;
   /*      hbmNew = ::core::LoadSysColorBitmap(m_hInstImageWell, m_hRsrcImageWell);
         if (hbmNew != NULL)
            AddReplaceBitmap(hbmNew);*/
      }
   }

   /*
   void tool_bar::OnUpdateCmdUI(sp(::user::frame_window) pTarget, bool bDisableIfNoHndler)
   {
      tool_cmd_ui state;
      state.m_pOther = this;

      state.m_iCount = (UINT)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
      for (state.m_iIndex = 0; state.m_iIndex < state.m_iCount; state.m_iIndex++)
      {
         // get buttons state
         TBBUTTON button;
         _GetButton(state.m_iIndex, &button);
         state.m_id = button.idCommand;

         // ignore separators
         if (!(button.fsStyle & TBSTYLE_SEP))
         {
            // allow reflections
            if (::user::interaction::on_simple_action(0,
               MAKELONG((int32_t)CN_UPDATE_COMMAND_UI, WM_COMMAND+WM_REFLECT_BASE),
               &state, NULL))
               continue;

            // allow the toolbar itself to have update handlers
            if (::user::interaction::on_simple_action(state.m_nID, CN_UPDATE_COMMAND_UI, &state, NULL))
               continue;

            // allow the owner to process the update
            state.DoUpdate(pTarget, bDisableIfNoHndler);
         }
      }

      // update the dialog controls added to the toolbar
      UpdateDialogControls(pTarget, bDisableIfNoHndler);
   }
   */

   /////////////////////////////////////////////////////////////////////////////
   // tool_bar diagnostics

   #ifdef DEBUG
   void tool_bar::assert_valid() const
   {
      // Note: ::user::control_bar::assert_valid is not called because it checks for
      //  m_nCount and m_pData to be in sync, which they are not in tool_bar.

/*      ASSERT(m_hbmImageWell == NULL ||
         (afxData.bWin95 || ::GetObjectType(m_hbmImageWell) == OBJ_BITMAP));

      if (m_hInstImageWell != NULL && m_hbmImageWell != NULL)
         ASSERT(m_hRsrcImageWell != NULL);*/
   }

   void tool_bar::dump(dump_context & dumpcontext) const
   {
      ::user::control_bar::dump(dumpcontext);

//      dumpcontext << "m_hbmImageWell = " << (UINT)m_hbmImageWell;
//      dumpcontext << "\nm_hInstImageWell = " << (UINT)m_hInstImageWell;
//      dumpcontext << "\nm_hRsrcImageWell = " << (UINT)m_hRsrcImageWell;
      dumpcontext << "\nm_sizeButton = " << m_sizeButton;
      dumpcontext << "\nm_sizeImage = " << m_sizeImage;

      if (dumpcontext.GetDepth() > 0)
      {
#ifdef WINDOWSEX
         tool_bar* pBar = (tool_bar*)this;
         LRESULT nCount = pBar->DefWindowProc(TB_BUTTONCOUNT, 0, 0);
         for (index i = 0; i < nCount; i++)
         {
            TBBUTTON button;
            _GetButton(i, &button);
            dumpcontext << "\ntoolbar button[" << i << "] = {";
            dumpcontext << "\n\tnID = " << button.idCommand;
            dumpcontext << "\n\tnStyle = " << MAKELONG(button.fsStyle, button.fsState);
            if (button.fsStyle & TBSTYLE_SEP)
               dumpcontext << "\n\tiImage (separator width) = " << button.iBitmap;
            else
               dumpcontext <<"\n\tiImage (bitmap image index) = " << button.iBitmap;
            dumpcontext << "\n}";
         }
#else
         throw todo(get_app());

#endif
      }

      dumpcontext << "\n";
   }
   #endif

   // IMPLEMENT_DYNAMIC(tool_bar, ::user::control_bar)

   /////////////////////////////////////////////////////////////////////////////

   size tool_bar::CalcSimpleLayout()
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      size sizeResult(0,0);

#ifdef WINDOWSEX
      int32_t nCount;
      TBBUTTON* pData = NULL;

      //BLOCK: Load Buttons
      {
         nCount =(int32_t)  DefWindowProc(TB_BUTTONCOUNT, 0, 0);
         if (nCount != 0)
         {
            int32_t i;
            pData = new TBBUTTON[nCount];
            for (i = 0; i < nCount; i++)
               _GetButton(i, &pData[i]);
         }
      }
      if (nCount > 0)
      {
         int32_t i;
         for (i = 0; i < nCount; i++)
         {
            pData[i].fsState &= ~TBSTATE_WRAP;
         }
         for (i = 0; i < nCount; i++)
         {
            _SetButton(i, &pData[i]);
         }
            for (i = 0; i < nCount; i++)
               _GetButton(i, &pData[i]);
         for (i = 0; i < nCount; i++)
         {
            if(pData[i].fsState & TBSTATE_WRAP)
               ASSERT(FALSE);
         }
         rect rectItem;
         rect rectSize(0, 0, 0, 0);
         for (i = 0; i < nCount; i++)
         {
            GetItemRect(i, rectItem);
            rectSize.unite(rectSize, rectItem);
         }
         sizeResult = rectSize.size();

         delete[] pData;
      }

      if(GetStyle() & TBSTYLE_FLAT)
      {
         sizeResult.cy += 2;
      }

#else

      throw todo(get_app());

#endif

      return sizeResult;


   }

   size tool_bar::SimpleLayout()
   {
      size size = CalcSimpleLayout();
      SetWindowPos(
         ZORDER_TOP,
         0, 0,
         size.cx, size.cy,
         SWP_SHOWWINDOW
         | SWP_NOMOVE);
      return size;
   }


   ::count tool_bar::_001GetItemCount()
   {
      return -1;
   }

   tool_bar_control& tool_bar::GetToolBarCtrl() const
      { return *(tool_bar_control*)this; }
   /*bool tool_bar::LoadToolBar(UINT nIDResource)
      { return LoadToolBar(MAKEINTRESOURCE(nIDResource)); }
   bool tool_bar::LoadBitmap(UINT nIDResource)
      { return LoadBitmap(MAKEINTRESOURCE(nIDResource)); }*/


} // namespace user
