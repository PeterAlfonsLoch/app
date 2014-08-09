#include "framework.h"

namespace user
{

   toolbar_control::~toolbar_control()
   {
      DestroyWindow();
   }

   bool toolbar_control::create_window(uint32_t dwStyle,const RECT & rect,sp(::user::interaction) pParentWnd,
      UINT nID)
   {

      return create_window(TOOLBARCLASSNAME, NULL, dwStyle, rect, pParentWnd, nID);
   }

   int32_t toolbar_control::AddBitmap(int32_t nNumButtons, ::draw2d::bitmap* pBitmap)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow());
      TBADDBITMAP tbab;
      tbab.hInst = NULL;
      tbab.nID = (UINT)pBitmap->get_os_data();
      return (int32_t) send_message( TB_ADDBITMAP, (WPARAM)nNumButtons,
         (LPARAM)&tbab);
#else
      throw todo(get_app());
#endif
   }

#ifdef WINDOWSEX
   void toolbar_control::SaveState(HKEY hKeyRoot, const char * lpszSubKey,
      const char * lpszValueName)
   {
      ASSERT(IsWindow());
      TBSAVEPARAMS tbs;
      tbs.hkr = hKeyRoot;
      tbs.pszSubKey = lpszSubKey;
      tbs.pszValueName = lpszValueName;
      send_message( TB_SAVERESTORE, (WPARAM)TRUE, (LPARAM)&tbs);
   }

   void toolbar_control::RestoreState(HKEY hKeyRoot, const char * lpszSubKey,
      const char * lpszValueName)
   {
      ASSERT(IsWindow());
      TBSAVEPARAMS tbs;
      tbs.hkr = hKeyRoot;
      tbs.pszSubKey = lpszSubKey;
      tbs.pszValueName = lpszValueName;
      send_message( TB_SAVERESTORE, (WPARAM)FALSE, (LPARAM)&tbs);
   }
#endif


   void toolbar_control::_001OnCreate(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

#ifdef WINDOWSEX
      SetButtonStructSize(sizeof(TBBUTTON));
#else
      throw todo(get_app());
#endif

   }


   HRESULT toolbar_control::GetDropTarget(IDropTarget** ppDropTarget)
   {
      ASSERT(IsWindow());
      ASSERT(ppDropTarget);
#ifdef WINDOWSEX
      return (HRESULT) send_message( TB_GETOBJECT, (WPARAM)&IID_IDropTarget, (LPARAM)ppDropTarget);
#else
      throw todo(get_app());
#endif
   }

   struct CToolBarCtrlData
   {
      WORD wVersion;
      WORD wWidth;
      WORD wHeight;
      WORD wItemCount;
      //WORD aItems[wItemCount]

      WORD* items()
      { return (WORD*)(this+1); }
   };

   /*bool toolbar_control::LoadToolBar(const char * lpszResourceName)
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

   CToolBarCtrlData* pData = (CToolBarCtrlData*)LockResource(hGlobal);
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
   //      SetSizes(sizeButton, sizeImage);

   // load bitmap now that sizes are known by the toolbar control
   LoadImages((int32_t)(WORD) (long *)lpszResourceName, __get_resource_handle());
   }

   UnlockResource(hGlobal);
   FreeResource(hGlobal);

   return bResult;
   }*/

   bool toolbar_control::SetButtons(const UINT* lpIDArray, int32_t nIDCount)
   {
      ASSERT_VALID(this);
      ASSERT(nIDCount >= 1);  // must be at least one of them
      ASSERT(lpIDArray == NULL ||
         __is_valid_address(lpIDArray, sizeof(UINT) * nIDCount, FALSE));

      // delete all existing buttons
      /* linux int32_t nCount = (int32_t)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
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
      ASSERT(gen_ComCtlVersion != -1);
      if ((GetStyle() & TBSTYLE_FLAT) || gen_ComCtlVersion == VERSION_IE4)
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
      if (!DefWindowProc(TB_ADDBUTTONSW, 1, (LPARAM)&button))
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
      if (!DefWindowProc(TB_ADDBUTTONSW, 1, (LPARAM)&button))
      return FALSE;
      }
      }
      //   m_nCount = (int32_t)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
      //   m_bDelayedButtonLayout = TRUE; */

      return TRUE;
   }

   int32_t toolbar_control::GetButtonText(UINT uiID, string &str)
   {
#ifdef WINDOWSEX
      UNREFERENCED_PARAMETER(uiID);
      UNREFERENCED_PARAMETER(str);
      TBBUTTONINFOW tbbi;
      tbbi.cbSize = sizeof(tbbi);
      tbbi.dwMask = TBIF_TEXT;

      //      int32_t nSize = 256;
      while(true)
      {
         /*         tbbi.pszText = str.GetBuffer(nSize);
         if(!tbbi.pszText)
         return 0;
         tbbi.cchText = nSize;
         if(GetButtonInfo(uiID, &tbbi) != -1)
         {
         str.ReleaseBuffer();
         return 1;
         }
         nSize += 256;*/
      }
#else
      throw todo(get_app());
#endif
   }

   /////////////////////////////////////////////////////////////////////////////

   toolbar_control::toolbar_control()
   { }
   bool toolbar_control::EnableButton(int32_t nID, bool bEnable)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_ENABLEBUTTON, nID, MAKELPARAM(bEnable, 0)) != FALSE;
#else
      throw todo(get_app());
#endif

   }
   bool toolbar_control::CheckButton(int32_t nID, bool bCheck)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_CHECKBUTTON, nID, MAKELPARAM(bCheck, 0)) != FALSE;
#else
      throw todo(get_app());
#endif

   }
   bool toolbar_control::PressButton(int32_t nID, bool bPress)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_PRESSBUTTON, nID, MAKELPARAM(bPress, 0)) != FALSE;
#else
      throw todo(get_app());
#endif
   }


   bool toolbar_control::HideButton(int32_t nID, bool bHide)
   {

#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_HIDEBUTTON, nID, MAKELPARAM(bHide, 0)) != FALSE;
#else
      throw todo(get_app());
#endif
   }


   bool toolbar_control::Indeterminate(int32_t nID, bool bIndeterminate)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_INDETERMINATE, nID, MAKELPARAM(bIndeterminate, 0)) != FALSE;
#else
      throw todo(get_app());
#endif
   }


   bool toolbar_control::IsButtonEnabled(int32_t nID)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_ISBUTTONENABLED, nID) != FALSE;
#else
      throw todo(get_app());
#endif
   }



   bool toolbar_control::IsButtonChecked(int32_t nID)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_ISBUTTONCHECKED, nID) != FALSE;
#else
      throw todo(get_app());
#endif
   }


   bool toolbar_control::IsButtonPressed(int32_t nID)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_ISBUTTONPRESSED, nID) != FALSE;
#else
      throw todo(get_app());
#endif
   }


   bool toolbar_control::IsButtonHidden(int32_t nID)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_ISBUTTONHIDDEN, nID) != FALSE;
#else
      throw todo(get_app());
#endif
   }


   bool toolbar_control::IsButtonIndeterminate(int32_t nID)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_ISBUTTONINDETERMINATE, nID) != FALSE;
#else
      throw todo(get_app());
#endif
   }


   bool toolbar_control::SetState(int32_t nID, UINT nState)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); 
      return send_message( TB_SETSTATE, nID, (LPARAM) nState) != FALSE;
#else
      throw todo(get_app());
#endif
   }


   int32_t toolbar_control::GetState(int32_t nID)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return (int32_t) send_message( TB_GETSTATE, nID);
#else
      throw todo(get_app());
#endif
   }


#ifdef WINDOWSEX
   bool toolbar_control::AddButtons(int32_t nNumButtons, LPTBBUTTON lpButtons)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_ADDBUTTONSW, nNumButtons, (LPARAM)lpButtons) != FALSE;
#else
      throw todo(get_app());
#endif
   }
   bool toolbar_control::InsertButton(int32_t nIndex, LPTBBUTTON lpButton)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_INSERTBUTTON, nIndex, (LPARAM)lpButton) != FALSE;
#else
      throw todo(get_app());
#endif
   }
#endif


   bool toolbar_control::DeleteButton(int32_t nIndex)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_DELETEBUTTON, nIndex) != FALSE;
#else
      throw todo(get_app());
#endif
   }



#ifdef WINDOWSEX

   bool toolbar_control::GetButton(int32_t nIndex, LPTBBUTTON lpButton)
   {

      ASSERT(IsWindow()); return send_message( TB_GETBUTTON, nIndex, (LPARAM)lpButton) != FALSE;

   }

#endif




   int32_t toolbar_control::GetButtonCount()
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return (int32_t) send_message( TB_BUTTONCOUNT);

#else

      throw todo(get_app());

#endif
   }
   UINT toolbar_control::CommandToIndex(UINT nID)
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return (UINT) send_message( TB_COMMANDTOINDEX, nID);

#else

      throw todo(get_app());

#endif

   }

   void toolbar_control::Customize()
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); send_message( TB_CUSTOMIZE);

#else

      throw todo(get_app());

#endif

   }

   // lpszStrings are separated by zeroes, last one is marked by two zeroes
   int32_t toolbar_control::AddStrings(const char * lpszStrings)
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return (int32_t) send_message( TB_ADDSTRING, 0, (LPARAM)lpszStrings);

#else

      throw todo(get_app());

#endif

   }

   bool toolbar_control::GetItemRect(int32_t nIndex, LPRECT lpRect)
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return send_message( TB_GETITEMRECT, nIndex, (LPARAM)lpRect) != FALSE;

#else

      throw todo(get_app());

#endif

   }

   void toolbar_control::SetButtonStructSize(int32_t nSize)
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); send_message( TB_BUTTONSTRUCTSIZE, nSize);

#else

      throw todo(get_app());

#endif

   }

   bool toolbar_control::SetButtonSize(size size)
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return send_message( TB_SETBUTTONSIZE, 0, MAKELPARAM(size.cx, size.cy)) != FALSE;

#else

      throw todo(get_app());

#endif

   }

   bool toolbar_control::SetBitmapSize(size size)
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return send_message( TB_SETBITMAPSIZE, 0, MAKELPARAM(size.cx, size.cy)) != FALSE;

#else

      throw todo(get_app());

#endif

   }


   void toolbar_control::AutoSize()
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); send_message( TB_AUTOSIZE);

#else

      throw todo(get_app());

#endif

   }


   sp(::user::interaction)  toolbar_control::SetOwner(sp(::user::interaction) pwindow)
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); send_message( TB_SETPARENT, (WPARAM)pwindow.m_p);

#else

      throw todo(get_app());

#endif
      return pwindow;

   }


   void toolbar_control::SetRows(int32_t nRows, bool bLarger, LPRECT lpRect)
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); send_message( TB_SETROWS, MAKELPARAM(nRows, bLarger), (LPARAM)lpRect);

#else

      throw todo(get_app());

#endif

   }


   int32_t toolbar_control::GetRows()
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return (int32_t) send_message( TB_GETROWS);

#else

      throw todo(get_app());

#endif

   }


   bool toolbar_control::SetCmdID(int32_t nIndex, UINT nID)
   {

#ifdef WINDOWSEX

      ASSERT(IsWindow()); return send_message(TB_SETCMDID, nIndex, (LPARAM) nID) != FALSE;

#else

      throw todo(get_app());

#endif

   }


   UINT toolbar_control::GetBitmapFlags()
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return (UINT) send_message( TB_GETBITMAPFLAGS);

#else

      throw todo(get_app());

#endif

   }


   int32_t toolbar_control::hit_test(LPPOINT ppt)
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return (int32_t) send_message( TB_HITTEST, 0, (LPARAM)ppt);

#else

      throw todo(get_app());

#endif

   }


   uint32_t toolbar_control::GetExtendedStyle()
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return (uint32_t) send_message( TB_GETEXTENDEDSTYLE);

#else

      throw todo(get_app());

#endif

   }


   uint32_t toolbar_control::SetExtendedStyle(uint32_t dwExStyle)
   {

#ifdef WINDOWSEX

      ASSERT(IsWindow()); return (uint32_t) send_message( TB_SETEXTENDEDSTYLE, 0, (LPARAM) dwExStyle);

#else

      throw todo(get_app());

#endif

   }


   COLORREF toolbar_control::GetInsertMarkColor()
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return (COLORREF) send_message( TB_GETINSERTMARKCOLOR);

#else

      throw todo(get_app());

#endif

   }


   COLORREF toolbar_control::SetInsertMarkColor(COLORREF clrNew)
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return (COLORREF) send_message( TB_SETINSERTMARKCOLOR, 0, (LPARAM) clrNew);

#else

      throw todo(get_app());

#endif

   }

   /////////////////////////////////////////////////////////////////////////////

   uint32_t toolbar_control::get_button_size()
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return (uint32_t) send_message( TB_GETBUTTONSIZE);

#else

      throw todo(get_app());

#endif

   }


   image_list* toolbar_control::GetDisabledImageList()
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return NULL;

#else

      throw todo(get_app());

#endif

   }


   image_list* toolbar_control::GetHotImageList()
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return NULL;

#else

      throw todo(get_app());

#endif

   }


   image_list* toolbar_control::GetImageList()
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return NULL;

#else

      throw todo(get_app());

#endif

   }


   uint32_t toolbar_control::GetStyle()
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return (uint32_t) send_message( TB_GETSTYLE);

#else

      throw todo(get_app());

#endif

   }


   INT toolbar_control::GetMaxTextRows()
   {

#ifdef WINDOWSEX

      ASSERT(IsWindow()); 
      
      return (INT) send_message(TB_GETTEXTROWS);

#else

      throw todo(get_app());

#endif

   }


   bool toolbar_control::GetRect(int32_t nID, LPRECT lpRect)
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return send_message( TB_GETRECT, nID, (LPARAM)lpRect) != FALSE;

#else

      throw todo(get_app());

#endif

   }


   bool toolbar_control::IsButtonHighlighted(int32_t nID)
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return send_message( TB_ISBUTTONHIGHLIGHTED, nID) != FALSE;

#else

      throw todo(get_app());

#endif

   }


   void toolbar_control::LoadImages(int32_t iBitmapID, HINSTANCE hinst)
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); send_message( TB_LOADIMAGES, iBitmapID, (LPARAM)hinst);

#else

      throw todo(get_app());

#endif

   }


   bool toolbar_control::SetButtonWidth(int32_t cxMin, int32_t cxMax)
   {

#ifdef WINDOWSEX

   ASSERT(IsWindow()); return send_message( TB_SETBUTTONWIDTH, 0, MAKELPARAM(cxMin, cxMax)) != FALSE;

#else

      throw todo(get_app());

#endif

   }


   image_list* toolbar_control::SetDisabledImageList(image_list* pImageList)
   {
      UNREFERENCED_PARAMETER(pImageList);
#ifdef WINDOWSEX

      ASSERT(IsWindow());
      return NULL;

#else

      throw todo(get_app());

#endif

   }


   image_list* toolbar_control::SetHotImageList(image_list* pImageList)
   {
      UNREFERENCED_PARAMETER(pImageList);
#ifdef WINDOWSEX

      ASSERT(IsWindow());
      return NULL;

#else

      throw todo(get_app());

#endif

   }


   image_list* toolbar_control::SetImageList(image_list* pImageList)
   {

      UNREFERENCED_PARAMETER(pImageList);

#ifdef WINDOWSEX

      ASSERT(IsWindow());
      return NULL;

#else

      throw todo(get_app());

#endif

   }


   bool toolbar_control::SetIndent(int32_t iIndent)
   {
#ifdef WINDOWSEX

   ASSERT(IsWindow()); return send_message( TB_SETINDENT, iIndent) != FALSE;

#else

      throw todo(get_app());

#endif

   }
   bool toolbar_control::SetMaxTextRows(int32_t iMaxRows)
   {
#ifdef WINDOWSEX

   ASSERT(IsWindow()); return send_message( TB_SETMAXTEXTROWS, iMaxRows) != FALSE;

#else

      throw todo(get_app());

#endif

   }
   void toolbar_control::SetStyle(uint32_t dwStyle)
   {
#ifdef WINDOWSEX

      ASSERT(IsWindow()); send_message( TB_SETSTYLE, 0, (LPARAM) dwStyle);

#else

      throw todo(get_app());

#endif

   }

#ifdef WINDOWSEX

   bool toolbar_control::GetButtonInfo(int32_t nID, TBBUTTONINFO* ptbbi)
   {

      ASSERT(IsWindow()); return send_message( TB_GETBUTTONINFO, nID, (LPARAM)ptbbi) != FALSE;

   }

#endif


#ifdef WINDOWSEX

   bool toolbar_control::GetButtonInfo(int32_t nID, TBBUTTONINFOW* ptbbi)
   {

      ASSERT(IsWindow()); return send_message( TB_GETBUTTONINFOW, nID, (LPARAM)ptbbi) != FALSE;

   }

#endif


#ifdef WINDOWSEX

   bool toolbar_control::SetButtonInfo(int32_t nID, TBBUTTONINFO* ptbbi)
   {

      ASSERT(IsWindow()); return send_message( TB_SETBUTTONINFO, nID, (LPARAM)ptbbi) != FALSE;

   }

#endif


#ifdef WINDOWSEX

   bool toolbar_control::SetButtonInfo(int32_t nID, TBBUTTONINFOW* ptbbi)
   {

      ASSERT(IsWindow()); return send_message( TB_SETBUTTONINFOW, nID, (LPARAM)ptbbi) != FALSE;


   }

#endif


   uint32_t toolbar_control::SetDrawTextFlags(uint32_t dwMask, uint32_t dwDTFlags)
   {

#ifdef WINDOWSEX

      ASSERT(IsWindow()); return (uint32_t) send_message( TB_SETDRAWTEXTFLAGS, dwMask, (LPARAM) dwDTFlags);

#else

      throw todo(get_app());

#endif

   }
   bool toolbar_control::GetAnchorHighlight()
   {
#ifdef WINDOWSEX

   ASSERT(IsWindow()); return send_message( TB_GETANCHORHIGHLIGHT) != FALSE;

#else

      throw todo(get_app());

#endif

   }
   bool toolbar_control::SetAnchorHighlight(bool fAnchor)
   {
#ifdef WINDOWSEX

   ASSERT(IsWindow()); return send_message( TB_SETANCHORHIGHLIGHT, fAnchor) != FALSE;

#else

      throw todo(get_app());

#endif

   }
   int32_t toolbar_control::GetHotItem()
   {
#ifdef WINDOWSEX

   ASSERT(IsWindow()); return (int32_t) send_message( TB_GETHOTITEM);

#else

      throw todo(get_app());

#endif

   }
   int32_t toolbar_control::SetHotItem(int32_t nHot)
   {
#ifdef WINDOWSEX

   ASSERT(IsWindow()); return (int32_t) send_message( TB_SETHOTITEM, nHot);

#else

      throw todo(get_app());

#endif

   }

#ifdef WINDOWSEX

   void toolbar_control::GetInsertMark(TBINSERTMARK* ptbim)
   {


      ASSERT(IsWindow());

      send_message( TB_GETINSERTMARK, 0, (LPARAM)ptbim);

   }


   void toolbar_control::SetInsertMark(TBINSERTMARK* ptbim)
   {

      ASSERT(IsWindow());

      send_message( TB_SETINSERTMARK, 0, (LPARAM)ptbim);

   }


#endif


   bool toolbar_control::GetMaxSize(LPSIZE pSize)
   {
#ifdef WINDOWSEX

   ASSERT(IsWindow()); return send_message( TB_GETMAXSIZE, 0, (LPARAM)pSize) != FALSE;

#else

      throw todo(get_app());

#endif

   }


#ifdef WINDOWSEX

   bool toolbar_control::InsertMarkHitTest(LPPOINT ppt, LPTBINSERTMARK ptbim)
   {

   ASSERT(IsWindow()); return send_message( TB_INSERTMARKHITTEST, (WPARAM)ppt, (LPARAM)ptbim) != FALSE;

   }

#endif


   bool toolbar_control::MapAccelerator(char chAccel, UINT* pIDBtn)
   {
#ifdef WINDOWSEX

   ASSERT(IsWindow()); return send_message( TB_MAPACCELERATOR, (WPARAM)chAccel, (LPARAM)pIDBtn) != FALSE;

#else

      throw todo(get_app());

#endif

   }
   bool toolbar_control::MarkButton(int32_t nID, bool bHighlight)
   {
#ifdef WINDOWSEX

   ASSERT(IsWindow()); return send_message( TB_MARKBUTTON, nID, MAKELPARAM(bHighlight, 0)) != FALSE;

#else

      throw todo(get_app());

#endif

   }
   bool toolbar_control::MoveButton(UINT nOldPos, UINT nNewPos)
   {

#ifdef WINDOWSEX

      ASSERT(IsWindow()); return send_message( TB_MOVEBUTTON, nOldPos, (LPARAM) nNewPos) != FALSE;

#else

      throw todo(get_app());

#endif

   }


} // namespace user
