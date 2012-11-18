#include "framework.h"

namespace userbase
{

   tool_bar_control::~tool_bar_control()
   {
      DestroyWindow();
   }

   bool tool_bar_control::create(DWORD dwStyle, const RECT& rect, ::user::interaction* pParentWnd,
      UINT nID)
   {
#ifdef WINDOWSEX
      // initialize common controls
      VERIFY(System.DeferRegisterClass(__WNDCOMMCTL_BAR_REG, NULL));
#else
      throw todo(get_app());
#endif

#ifdef WINDOWSEX
      ::user::interaction* pWnd = this;
      return pWnd->create(TOOLBARCLASSNAME, NULL, dwStyle, rect, pParentWnd, nID);
#else
      throw todo(get_app());
#endif
   }

   int tool_bar_control::AddBitmap(int nNumButtons, ::ca::bitmap* pBitmap)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow());
      TBADDBITMAP tbab;
      tbab.hInst = NULL;
      tbab.nID = (UINT)pBitmap->get_os_data();
      return (int) send_message( TB_ADDBITMAP, (WPARAM)nNumButtons,
         (LPARAM)&tbab);
#else
      throw todo(get_app());
#endif
   }

#ifdef WINDOWSEX
   void tool_bar_control::SaveState(HKEY hKeyRoot, const char * lpszSubKey,
      const char * lpszValueName)
   {
      ASSERT(IsWindow());
      TBSAVEPARAMS tbs;
      tbs.hkr = hKeyRoot;
      tbs.pszSubKey = lpszSubKey;
      tbs.pszValueName = lpszValueName;
      send_message( TB_SAVERESTORE, (WPARAM)TRUE, (LPARAM)&tbs);
   }

   void tool_bar_control::RestoreState(HKEY hKeyRoot, const char * lpszSubKey,
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


   int tool_bar_control::OnCreate(LPCREATESTRUCT lpcs)
   {
      UNREFERENCED_PARAMETER(lpcs);
      // trans   if (::user::interaction::OnCreate(lpcs) == -1)
      // return -1;
#ifdef WINDOWSEX
      SetButtonStructSize(sizeof(TBBUTTON));
#else
      throw todo(get_app());
#endif
      return 0;
   }

   HRESULT tool_bar_control::GetDropTarget(IDropTarget** ppDropTarget)
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

   /*bool tool_bar_control::LoadToolBar(const char * lpszResourceName)
   {
   ASSERT_VALID(this);
   ASSERT(lpszResourceName != NULL);

   // determine location of the bitmap in resource fork
   HINSTANCE hInst = gen::FindResourceHandle(lpszResourceName, RT_TOOLBAR);
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
   for (int i = 0; i < pData->wItemCount; i++)
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
   LoadImages((int)(WORD) (long *)lpszResourceName, __get_resource_handle());
   }

   UnlockResource(hGlobal);
   FreeResource(hGlobal);

   return bResult;
   }*/

   bool tool_bar_control::SetButtons(const UINT* lpIDArray, int nIDCount)
   {
      ASSERT_VALID(this);
      ASSERT(nIDCount >= 1);  // must be at least one of them
      ASSERT(lpIDArray == NULL ||
         __is_valid_address(lpIDArray, sizeof(UINT) * nIDCount, FALSE));

      // delete all existing buttons
      /* linux int nCount = (int)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
      while (nCount--)
      VERIFY(DefWindowProc(TB_DELETEBUTTON, 0, 0));

      TBBUTTON button; memset(&button, 0, sizeof(TBBUTTON));
      button.iString = -1;
      if (lpIDArray != NULL)
      {
      // add new buttons to the common control
      int iImage = 0;
      for (int i = 0; i < nIDCount; i++)
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
      for (int i = 0; i < nIDCount; i++)
      {
      ASSERT(button.fsStyle == TBSTYLE_BUTTON);
      if (!DefWindowProc(TB_ADDBUTTONSW, 1, (LPARAM)&button))
      return FALSE;
      }
      }
      //   m_nCount = (int)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
      //   m_bDelayedButtonLayout = TRUE; */

      return TRUE;
   }

   int tool_bar_control::GetButtonText(UINT uiID, string &str)
   {
#ifdef WINDOWSEX
      UNREFERENCED_PARAMETER(uiID);
      UNREFERENCED_PARAMETER(str);
      TBBUTTONINFOW tbbi;
      tbbi.cbSize = sizeof(tbbi);
      tbbi.dwMask = TBIF_TEXT;

      //      int nSize = 256;
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

   tool_bar_control::tool_bar_control()
   { }
   bool tool_bar_control::EnableButton(int nID, bool bEnable)
   { 
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_ENABLEBUTTON, nID, MAKELPARAM(bEnable, 0)) != FALSE; 
#else
      throw todo(get_app());
#endif

   }
   bool tool_bar_control::CheckButton(int nID, bool bCheck)
   { 
#ifdef WINDOWSEX   
      ASSERT(IsWindow()); return send_message( TB_CHECKBUTTON, nID, MAKELPARAM(bCheck, 0)) != FALSE; 
#else
      throw todo(get_app());
#endif

   }
   bool tool_bar_control::PressButton(int nID, bool bPress)
   { 
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_PRESSBUTTON, nID, MAKELPARAM(bPress, 0)) != FALSE; 
#else
      throw todo(get_app());
#endif
   }


   bool tool_bar_control::HideButton(int nID, bool bHide)
   {

#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_HIDEBUTTON, nID, MAKELPARAM(bHide, 0)) != FALSE; 
#else
      throw todo(get_app());
#endif
   }


   bool tool_bar_control::Indeterminate(int nID, bool bIndeterminate)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_INDETERMINATE, nID, MAKELPARAM(bIndeterminate, 0)) != FALSE; 
#else
      throw todo(get_app());
#endif
   }


   bool tool_bar_control::IsButtonEnabled(int nID)
   {
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_ISBUTTONENABLED, nID, 0) != FALSE; 
#else
      throw todo(get_app());
#endif
   }



   bool tool_bar_control::IsButtonChecked(int nID)
   { 
#ifdef WINDOWSEX
      ASSERT(IsWindow()); return send_message( TB_ISBUTTONCHECKED, nID, 0) != FALSE;
#else
      throw todo(get_app());
#endif
   }


   bool tool_bar_control::IsButtonPressed(int nID)
   {
#ifdef WINDOWSEX 
      ASSERT(IsWindow()); return send_message( TB_ISBUTTONPRESSED, nID, 0) != FALSE; 
#else
      throw todo(get_app());
#endif
   }


   bool tool_bar_control::IsButtonHidden(int nID)
   { 
#ifdef WINDOWSEX 
      ASSERT(IsWindow()); return send_message( TB_ISBUTTONHIDDEN, nID, 0) != FALSE; 
#else
      throw todo(get_app());
#endif
   }


   bool tool_bar_control::IsButtonIndeterminate(int nID)
   { 
#ifdef WINDOWSEX 
      ASSERT(IsWindow()); return send_message( TB_ISBUTTONINDETERMINATE, nID, 0) != FALSE; 
#else
      throw todo(get_app());
#endif
   }


   bool tool_bar_control::SetState(int nID, UINT nState)
   {
#ifdef WINDOWSEX 
      ASSERT(IsWindow()); return send_message( TB_SETSTATE, nID, MAKELPARAM(nState, 0)) != FALSE; 
#else
      throw todo(get_app());
#endif
   }


   int tool_bar_control::GetState(int nID)
   { 
#ifdef WINDOWSEX 
      ASSERT(IsWindow()); return (int) send_message( TB_GETSTATE, nID, 0L); 
#else
      throw todo(get_app());
#endif
   }


#ifndef METROWIN
   bool tool_bar_control::AddButtons(int nNumButtons, LPTBBUTTON lpButtons)
   {
#ifdef WINDOWSEX 
      ASSERT(IsWindow()); return send_message( TB_ADDBUTTONSW, nNumButtons, (LPARAM)lpButtons) != FALSE; 
#else
      throw todo(get_app());
#endif
   }
   bool tool_bar_control::InsertButton(int nIndex, LPTBBUTTON lpButton)
   {
#ifdef WINDOWSEX 
      ASSERT(IsWindow()); return send_message( TB_INSERTBUTTON, nIndex, (LPARAM)lpButton) != FALSE; 
#else
      throw todo(get_app());
#endif
   }
#endif


   bool tool_bar_control::DeleteButton(int nIndex)
   {
#ifdef WINDOWSEX 
      ASSERT(IsWindow()); return send_message( TB_DELETEBUTTON, nIndex, 0) != FALSE; 
#else
      throw todo(get_app());
#endif
   }



#ifndef METROWIN
   bool tool_bar_control::GetButton(int nIndex, LPTBBUTTON lpButton)
   { 
#ifdef WINDOWSEX 
      ASSERT(IsWindow()); return send_message( TB_GETBUTTON, nIndex, (LPARAM)lpButton) != FALSE;
#else
      throw todo(get_app());
#endif
   }
#endif




   int tool_bar_control::GetButtonCount()
   { 
#ifdef WINDOWSEX 
      ASSERT(IsWindow()); return (int) send_message( TB_BUTTONCOUNT, 0, 0L); 

#else

      throw todo(get_app());

#endif
   }
   UINT tool_bar_control::CommandToIndex(UINT nID)
   {

#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return (UINT) send_message( TB_COMMANDTOINDEX, nID, 0L); 

#else

      throw todo(get_app());

#endif

   }
    
   void tool_bar_control::Customize()
   { 

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); send_message( TB_CUSTOMIZE, 0, 0L); 

#else

      throw todo(get_app());

#endif

   }

   // lpszStrings are separated by zeroes, last one is marked by two zeroes
   int tool_bar_control::AddStrings(const char * lpszStrings)
   {

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return (int) send_message( TB_ADDSTRING, 0, (LPARAM)lpszStrings); 

#else

      throw todo(get_app());

#endif

   }

   bool tool_bar_control::GetItemRect(int nIndex, LPRECT lpRect)
   { 

#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return send_message( TB_GETITEMRECT, nIndex, (LPARAM)lpRect) != FALSE;

#else

      throw todo(get_app());

#endif

   }

   void tool_bar_control::SetButtonStructSize(int nSize)
   {

#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); send_message( TB_BUTTONSTRUCTSIZE, nSize, 0L); 

#else

      throw todo(get_app());

#endif

   }

   bool tool_bar_control::SetButtonSize(size size)
   {

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return send_message( TB_SETBUTTONSIZE, 0, MAKELPARAM(size.cx, size.cy)) != FALSE;

#else

      throw todo(get_app());

#endif

   }

   bool tool_bar_control::SetBitmapSize(size size)
   {

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return send_message( TB_SETBITMAPSIZE, 0, MAKELPARAM(size.cx, size.cy)) != FALSE; 

#else

      throw todo(get_app());

#endif

   }


   void tool_bar_control::AutoSize()
   {

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); send_message( TB_AUTOSIZE, 0, 0L);

#else

      throw todo(get_app());

#endif

   }


   void tool_bar_control::set_owner(::user::interaction* pWnd)
   {

#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); send_message( TB_SETPARENT, (WPARAM)pWnd, 0L); 

#else

      throw todo(get_app());

#endif

   }


   void tool_bar_control::SetRows(int nRows, bool bLarger, LPRECT lpRect)
   { 

#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); send_message( TB_SETROWS, MAKELPARAM(nRows, bLarger), (LPARAM)lpRect);

#else

      throw todo(get_app());

#endif

   }


   int tool_bar_control::GetRows()
   { 

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return (int) send_message( TB_GETROWS, 0, 0L); 

#else

      throw todo(get_app());

#endif

   }


   bool tool_bar_control::SetCmdID(int nIndex, UINT nID)
   { 

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return send_message( TB_SETCMDID, nIndex, nID) != FALSE;

#else

      throw todo(get_app());

#endif

   }


   UINT tool_bar_control::GetBitmapFlags()
   { 

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return (UINT) send_message( TB_GETBITMAPFLAGS, 0, 0L); 

#else

      throw todo(get_app());

#endif

   }


   int tool_bar_control::hit_test(LPPOINT ppt)
   { 

#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return (int) send_message( TB_HITTEST, 0, (LPARAM)ppt);

#else

      throw todo(get_app());

#endif

   }


   DWORD tool_bar_control::GetExtendedStyle()
   { 

#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return (DWORD) send_message( TB_GETEXTENDEDSTYLE, 0, 0L);

#else

      throw todo(get_app());

#endif

   }


   DWORD tool_bar_control::SetExtendedStyle(DWORD dwExStyle)
   { 

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return (DWORD) send_message( TB_SETEXTENDEDSTYLE, 0, dwExStyle);

#else

      throw todo(get_app());

#endif

   }


   COLORREF tool_bar_control::GetInsertMarkColor()
   { 

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return (COLORREF) send_message( TB_GETINSERTMARKCOLOR, 0, 0);

#else

      throw todo(get_app());

#endif

   }


   COLORREF tool_bar_control::SetInsertMarkColor(COLORREF clrNew)
   {

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return (COLORREF) send_message( TB_SETINSERTMARKCOLOR, 0, (LPARAM) clrNew);

#else

      throw todo(get_app());

#endif

   }

   /////////////////////////////////////////////////////////////////////////////

   DWORD tool_bar_control::GetButtonSize()
   {

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return (DWORD) send_message( TB_GETBUTTONSIZE, 0, 0L); 

#else

      throw todo(get_app());

#endif

   }


   image_list* tool_bar_control::GetDisabledImageList()
   { 

#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return NULL;

#else

      throw todo(get_app());

#endif

   }


   image_list* tool_bar_control::GetHotImageList()
   {

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return NULL;

#else

      throw todo(get_app());

#endif

   }


   image_list* tool_bar_control::GetImageList()
   { 

#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return NULL;

#else

      throw todo(get_app());

#endif

   }


   DWORD tool_bar_control::GetStyle()
   {

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return (DWORD) send_message( TB_GETSTYLE, 0, 0L); 

#else

      throw todo(get_app());

#endif

   }


   INT tool_bar_control::GetMaxTextRows()
   { 

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return (INT) send_message( TB_GETTEXTROWS, 0, 0L); 

#else

      throw todo(get_app());

#endif

   }


   bool tool_bar_control::GetRect(int nID, LPRECT lpRect)
   { 

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return send_message( TB_GETRECT, nID, (LPARAM)lpRect) != FALSE; 

#else

      throw todo(get_app());

#endif

   }


   bool tool_bar_control::IsButtonHighlighted(int nID)
   { 

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return send_message( TB_ISBUTTONHIGHLIGHTED, nID, 0) != FALSE; 

#else

      throw todo(get_app());

#endif

   }


   void tool_bar_control::LoadImages(int iBitmapID, HINSTANCE hinst)
   { 

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); send_message( TB_LOADIMAGES, iBitmapID, (LPARAM)hinst);

#else

      throw todo(get_app());

#endif

   }


   bool tool_bar_control::SetButtonWidth(int cxMin, int cxMax)
   { 

#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return send_message( TB_SETBUTTONWIDTH, 0, MAKELPARAM(cxMin, cxMax)) != FALSE; 

#else

      throw todo(get_app());

#endif

   }


   image_list* tool_bar_control::SetDisabledImageList(image_list* pImageList)
   {
      UNREFERENCED_PARAMETER(pImageList);
#ifdef WINDOWSEX 
      
      ASSERT(IsWindow()); 
      return NULL; 

#else

      throw todo(get_app());

#endif

   }


   image_list* tool_bar_control::SetHotImageList(image_list* pImageList)
   {
      UNREFERENCED_PARAMETER(pImageList);
#ifdef WINDOWSEX 
      
      ASSERT(IsWindow()); 
      return NULL; 

#else

      throw todo(get_app());

#endif

   }


   image_list* tool_bar_control::SetImageList(image_list* pImageList)
   { 

      UNREFERENCED_PARAMETER(pImageList);

#ifdef WINDOWSEX 
      
      ASSERT(IsWindow()); 
      return NULL; 

#else

      throw todo(get_app());

#endif

   }


   bool tool_bar_control::SetIndent(int iIndent)
   {
#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return send_message( TB_SETINDENT, iIndent, 0L) != FALSE; 

#else

      throw todo(get_app());

#endif

   }
   bool tool_bar_control::SetMaxTextRows(int iMaxRows)
   {
#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return send_message( TB_SETMAXTEXTROWS, iMaxRows, 0L) != FALSE;

#else

      throw todo(get_app());

#endif

   }
   void tool_bar_control::SetStyle(DWORD dwStyle)
   { 
#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); send_message( TB_SETSTYLE, 0, dwStyle);

#else

      throw todo(get_app());

#endif

   }

#ifndef METROWIN
   bool tool_bar_control::GetButtonInfo(int nID, TBBUTTONINFO* ptbbi)
   { 
#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return send_message( TB_GETBUTTONINFO, nID, (LPARAM)ptbbi) != FALSE;

#else

      throw todo(get_app());

#endif

   }

   bool tool_bar_control::GetButtonInfo(int nID, TBBUTTONINFOW* ptbbi)
   { 
#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return send_message( TB_GETBUTTONINFOW, nID, (LPARAM)ptbbi) != FALSE;

#else

      throw todo(get_app());

#endif

   }
   bool tool_bar_control::SetButtonInfo(int nID, TBBUTTONINFO* ptbbi)
   {
#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return send_message( TB_SETBUTTONINFO, nID, (LPARAM)ptbbi) != FALSE;

#else

      throw todo(get_app());

#endif

   }
   bool tool_bar_control::SetButtonInfo(int nID, TBBUTTONINFOW* ptbbi)
   {
#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return send_message( TB_SETBUTTONINFOW, nID, (LPARAM)ptbbi) != FALSE;

#else

      throw todo(get_app());

#endif

   }

#endif // !defined(METROWIN)

   DWORD tool_bar_control::SetDrawTextFlags(DWORD dwMask, DWORD dwDTFlags)
   {
#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return (DWORD) send_message( TB_SETDRAWTEXTFLAGS, dwMask, dwDTFlags); 

#else

      throw todo(get_app());

#endif

   }
   bool tool_bar_control::GetAnchorHighlight()
   {
#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return send_message( TB_GETANCHORHIGHLIGHT, 0, 0) != FALSE;

#else

      throw todo(get_app());

#endif

   }
   bool tool_bar_control::SetAnchorHighlight(bool fAnchor)
   {
#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return send_message( TB_SETANCHORHIGHLIGHT, fAnchor, 0) != FALSE; 

#else

      throw todo(get_app());

#endif

   }
   int tool_bar_control::GetHotItem()
   {
#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return (int) send_message( TB_GETHOTITEM, 0, 0); 

#else

      throw todo(get_app());

#endif

   }
   int tool_bar_control::SetHotItem(int nHot)
   { 
#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return (int) send_message( TB_SETHOTITEM, nHot, 0); 

#else

      throw todo(get_app());

#endif

   }

#ifndef METROWIN

   void tool_bar_control::GetInsertMark(TBINSERTMARK* ptbim)
   {
#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); send_message( TB_GETINSERTMARK, 0, (LPARAM)ptbim); 

#else

      throw todo(get_app());

#endif

   }
   void tool_bar_control::SetInsertMark(TBINSERTMARK* ptbim)
   { 
#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); send_message( TB_SETINSERTMARK, 0, (LPARAM)ptbim); 

#else

      throw todo(get_app());

#endif

   }


#endif // !defined(METROWIN)


   bool tool_bar_control::GetMaxSize(LPSIZE pSize)
   { 
#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return send_message( TB_GETMAXSIZE, 0, (LPARAM)pSize) != FALSE; 

#else

      throw todo(get_app());

#endif

   }

#ifndef METROWIN

   bool tool_bar_control::InsertMarkHitTest(LPPOINT ppt, LPTBINSERTMARK ptbim)
   {
#ifdef WINDOWSEX 
   
   ASSERT(IsWindow()); return send_message( TB_INSERTMARKHITTEST, (WPARAM)ppt, (LPARAM)ptbim) != FALSE;

#else

      throw todo(get_app());

#endif

   }


#endif // !defined(METROWIN)


   bool tool_bar_control::MapAccelerator(char chAccel, UINT* pIDBtn)
   { 
#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return send_message( TB_MAPACCELERATOR, (WPARAM)chAccel, (LPARAM)pIDBtn) != FALSE; 

#else

      throw todo(get_app());

#endif

   }
   bool tool_bar_control::MarkButton(int nID, bool bHighlight)
   {
#ifdef WINDOWSEX
   
   ASSERT(IsWindow()); return send_message( TB_MARKBUTTON, nID, MAKELPARAM(bHighlight, 0)) != FALSE;

#else

      throw todo(get_app());

#endif

   }
   bool tool_bar_control::MoveButton(UINT nOldPos, UINT nNewPos)
   { 
      
#ifdef WINDOWSEX
      
      ASSERT(IsWindow()); return send_message( TB_MOVEBUTTON, nOldPos, nNewPos) != FALSE; 

#else

      throw todo(get_app());

#endif

   }


} // namespace userbase