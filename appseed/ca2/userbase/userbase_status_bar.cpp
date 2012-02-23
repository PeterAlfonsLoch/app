#include "StdAfx.h"

#define SBPF_UPDATE 0x0001  // pending update of text
#define CX_PANE_BORDER 6    // 3 pixels on each side of each pane

namespace userbase
{

   AFX_STATUSPANE* status_bar::_GetPanePtr(int nIndex)
   {
      return &m_panea[nIndex];
   }


   status_bar::status_bar()
   {
      // setup default border/margin depending on type of system
      m_cyTopBorder = 2;
      m_cxLeftBorder = 0;
      m_cxRightBorder = 0;
      m_cyBottomBorder = 0;

      // minimum height set with SB_SETMINHEIGHT is cached
      m_nMinHeight = 0;
   }

   status_bar::~status_bar()
   {
   //   AllocElements(0, 0);    // destroys existing elements
   }

   void status_bar::install_message_handling(::gen::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_NCHITTEST         , pinterface, this, &status_bar::_001OnNcHitTest);
      IGUI_WIN_MSG_LINK(WM_NCCALCSIZE        , pinterface, this, &status_bar::_001OnNcCalcSize);
      IGUI_WIN_MSG_LINK(WM_SIZE              , pinterface, this, &status_bar::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_WINDOWPOSCHANGING , pinterface, this, &status_bar::_001OnWindowPosChanging);
      IGUI_WIN_MSG_LINK(WM_SETTEXT           , pinterface, this, &status_bar::_001OnSetText);
      IGUI_WIN_MSG_LINK(WM_GETTEXT           , pinterface, this, &status_bar::_001OnGetText);
      IGUI_WIN_MSG_LINK(WM_GETTEXTLENGTH     , pinterface, this, &status_bar::_001OnGetTextLength);
      IGUI_WIN_MSG_LINK(SB_SETMINHEIGHT      , pinterface, this, &status_bar::_001OnSetMinHeight);
   }

   BOOL status_bar::create(::user::interaction* pParentWnd, DWORD dwStyle, id strId)
   {
      return CreateEx(pParentWnd, 0, dwStyle, strId);
   }

   BOOL status_bar::CreateEx(::user::interaction* pParentWnd, DWORD dwCtrlStyle, DWORD dwStyle, id strId)
   {
      ASSERT_VALID(pParentWnd);   // must have a parent

      // save the style (some of these style bits are ca2 API specific)
      m_dwStyle = (dwStyle & CBRS_ALL);

      // translate ca2 API style bits to windows style bits
      dwStyle &= ~CBRS_ALL;
      dwStyle |= CCS_NOPARENTALIGN|CCS_NOMOVEY|CCS_NODIVIDER|CCS_NORESIZE;
      if (pParentWnd->GetStyle() & WS_THICKFRAME)
         dwStyle |= SBARS_SIZEGRIP;
      dwStyle |= dwCtrlStyle;

      // initialize common controls
      VERIFY(System.DeferRegisterClass(AFX_WNDCOMMCTL_BAR_REG, NULL));

      // create the HWND
      class rect rect;
      rect.null();
      return ::user::interaction::create(STATUSCLASSNAME, NULL, dwStyle, rect, pParentWnd, strId);
   }

   BOOL status_bar::PreCreateWindow(CREATESTRUCT& cs)
   {
      // in Win4, status bars do not have a border at all, since it is
      //  provided by the client area.
      if ((m_dwStyle & (CBRS_ALIGN_ANY|CBRS_BORDER_ANY)) == CBRS_BOTTOM)
         m_dwStyle &= ~(CBRS_BORDER_ANY|CBRS_BORDER_3D);

      return ::userbase::control_bar::PreCreateWindow(cs);
   }

   BOOL status_bar::SetIndicators(stringa & stra)
   {
      ASSERT_VALID(this);
      ASSERT(stra.get_count() >= 1);  // must be at least one of them
      //ASSERT(lpIDArray == NULL ||
   //      fx_is_valid_address(lpIDArray, sizeof(UINT) * nIDCount, FALSE));
      ASSERT(IsWindow());

      // first allocate base_array for panes and copy initial data
   //   if (!AllocElements(nIDCount, sizeof(AFX_STATUSPANE)))
   //      return FALSE;
   //   ASSERT(nIDCount == m_panea.get_count());

      // copy initial data from indicator base_array
      BOOL bResult = TRUE;
      //if (lpIDArray != NULL)
      //{
         HFONT hFont = (HFONT)SendMessage(WM_GETFONT);
         ::ca::graphics_sp spgraphicsScreen(get_app());
         HGDIOBJ hOldFont = NULL;
         if (hFont != NULL)
            hOldFont = spgraphicsScreen->SelectObject(hFont);

         AFX_STATUSPANE* pSBP = _GetPanePtr(0);
         for (int i = 0; i < stra.get_count(); i++)
         {
            pSBP->id = stra[i];
            pSBP->nFlags |= SBPF_UPDATE;
            if (pSBP->id.has_char())
            {
   /* xxx            if (!pSBP->strText.load_string(pSBP->strId))
               {
                  TRACE(::radix::trace::category_AppMsg, 0, "Warning: failed to load indicator string 0x%04X.\n",
                     pSBP->strId);
                  bResult = FALSE;
                  break;
               } */
               pSBP->cxText = spgraphicsScreen->GetTextExtent(pSBP->strText).cx;
               ASSERT(pSBP->cxText >= 0);
               if (!SetPaneText(i, pSBP->strText, FALSE))
               {
                  bResult = FALSE;
                  break;
               }
            }
            else
            {
               // no indicator (must access via index)
               // default to 1/4 the screen width (first pane is stretchy)
               pSBP->cxText = ::GetSystemMetrics(SM_CXSCREEN)/4;
               if (i == 0)
                  pSBP->nStyle |= (SBPS_STRETCH | SBPS_NOBORDERS);
            }
            ++pSBP;
         }
         if (hOldFont != NULL)
            spgraphicsScreen->SelectObject(hOldFont);
      //}
      UpdateAllPanes(TRUE, TRUE);

      return bResult;
   }

   /*
   BOOL status_bar::AllocElements(int nElements, int cbElement)
   {
      int i;

      // destruct old elements
      //AFX_STATUSPANE* pSBP = _GetPanePtr(0);
      //for (i = 0; i < m_panea.get_count(); i++)
      //{
      //   pSBP->strText.~string();
      //   ++pSBP;
      //}

      // allocate new elements
      //if (!::userbase::control_bar::AllocElements(nElements, cbElement))
      //   return FALSE;

      // construct new elements
   /*   pSBP = _GetPanePtr(0);
      for (i = 0; i < m_panea.get_count(); i++)
      {
   #pragma push_macro("new")
   #undef new
         new( &pSBP->strText ) string;
   #pragma pop_macro("new")
         ++pSBP;
      }*/
   /*   return TRUE;
   }
   */

   void status_bar::CalcInsideRect(rect& rect, BOOL bHorz)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());
      ASSERT(bHorz);  // vertical status bar not supported

      // subtract standard ::userbase::control_bar borders
      ::userbase::control_bar::CalcInsideRect(rect, bHorz);

      // subtract size grip if present
      if ((GetStyle() & SBARS_SIZEGRIP) && !GetParent()->IsZoomed())
      {
         // get border metrics from common control
         int rgBorders[3];
         status_bar* pBar = (status_bar*)this;
         pBar->DefWindowProc(SB_GETBORDERS, 0, (LPARAM)&rgBorders);

         // size grip uses a border + size of scrollbar + cx border
         rect.right -= rgBorders[0] + ::GetSystemMetrics(SM_CXVSCROLL) +
            ::GetSystemMetrics(SM_CXBORDER) * 2;
      }
   }

   void status_bar::UpdateAllPanes(BOOL bUpdateRects, BOOL bUpdateText)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      int i;

      // update the status pane locations
      if (bUpdateRects)
      {

         // get border information and client work area
         rect rect; GetWindowRect(rect);
         rect.offset(-rect.left, -rect.top);
         CalcInsideRect(rect, TRUE);
         int rgBorders[3];
         VERIFY((BOOL)DefWindowProc(SB_GETBORDERS, 0, (LPARAM)&rgBorders));

         // determine extra space for stretchy pane
         int cxExtra = rect.width() + rgBorders[2];
         int nStretchyCount = 0;
         //AFX_STATUSPANE* pSBP = _GetPanePtr(0);
         for (i = 0; i < m_panea.get_count(); i++)
         {
            AFX_STATUSPANE* pSBP = _GetPanePtr(i);
            if (pSBP->nStyle & SBPS_STRETCH)
               ++nStretchyCount;
            cxExtra -= (pSBP->cxText+CX_PANE_BORDER + rgBorders[2]);
            //++pSBP;
         }

         // determine right edge of each pane
         int* rgRights = (int*)_alloca(m_panea.get_count() * sizeof(int));
         int right = rgBorders[0];
   //      pSBP = _GetPanePtr(0);
         for (i = 0; i < m_panea.get_count(); i++)
         {
            AFX_STATUSPANE* pSBP = _GetPanePtr(i);
            // determine size of the pane
            ASSERT(pSBP->cxText >= 0);
            right += pSBP->cxText+CX_PANE_BORDER;
            if ((pSBP->nStyle & SBPS_STRETCH) && cxExtra > 0)
            {
               ASSERT(nStretchyCount != 0);
               int cxAddExtra = cxExtra / nStretchyCount;
               right += cxAddExtra;
               --nStretchyCount;
               cxExtra -= cxAddExtra;
            }
            rgRights[i] = right;

            // next pane
            ++pSBP;
            right += rgBorders[2];
         }

         // set new right edges for all panes
         DefWindowProc(SB_SETPARTS, m_panea.get_count(), (LPARAM)rgRights);
      }

      // update text in the status panes if specified
      if (bUpdateText)
      {
         for (i = 0; i < m_panea.get_count(); i++)
         {
            AFX_STATUSPANE* pSBP = _GetPanePtr(i);
            if (pSBP->nFlags & SBPF_UPDATE)
               SetPaneText(i, pSBP->strText);
            ++pSBP;
         }
      }
   }

   #ifdef AFX_CORE3_SEG
   #pragma code_seg(AFX_CORE3_SEG)
   #endif

   /////////////////////////////////////////////////////////////////////////////
   // status_bar attribute access

   int status_bar::CommandToIndex(id id)
   {
      ASSERT_VALID(this);

      if (m_panea.get_count() <= 0)
         return -1;

      for (int i = 0; i < m_panea.get_count(); i++)
      {
         AFX_STATUSPANE* pSBP = _GetPanePtr(i);
         if (pSBP->id == id)
            return i;
      }

      return -1;
   }

   id status_bar::GetItemId(int nIndex)
   {
      ASSERT_VALID(this);
      return _GetPanePtr(nIndex)->id;
   }

   void status_bar::GetItemRect(int nIndex, LPRECT lpRect)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      status_bar* pBar = (status_bar*)this;
      if (!pBar->DefWindowProc(SB_GETRECT, nIndex, (LPARAM)lpRect))
         ::SetRectEmpty(lpRect);
   }

   UINT status_bar::GetPaneStyle(int nIndex)
   {
      return _GetPanePtr(nIndex)->nStyle;
   }

   void status_bar::SetPaneStyle(int nIndex, UINT nStyle)
   {
      AFX_STATUSPANE* pSBP = _GetPanePtr(nIndex);
      if (pSBP->nStyle != nStyle)
      {
         // if the pane is changing SBPS_STRETCH, then...
         if ((pSBP->nStyle ^ nStyle) & SBPS_STRETCH)
         {
            // ... we need to re-layout the panes
            pSBP->nStyle = nStyle;
            UpdateAllPanes(TRUE, FALSE);
         }

         // use SetPaneText, since it updates the style and text
         pSBP->nStyle = nStyle;
         pSBP->nFlags |= SBPF_UPDATE;
         SetPaneText(nIndex, pSBP->strText);
      }
   }

   void status_bar::GetPaneInfo(int nIndex, id & id, UINT& nStyle,
      int& cxWidth)
   {
      ASSERT_VALID(this);

      AFX_STATUSPANE* pSBP = _GetPanePtr(nIndex);
      id = pSBP->id;
      nStyle = pSBP->nStyle;
      cxWidth = pSBP->cxText;
   }

   void status_bar::SetPaneInfo(int nIndex, id id, UINT nStyle, int cxWidth)
   {
      ASSERT_VALID(this);

      BOOL bChanged = FALSE;
      AFX_STATUSPANE* pSBP = _GetPanePtr(nIndex);
      pSBP->id = id;
      if (pSBP->nStyle != nStyle)
      {
         if ((pSBP->nStyle ^ nStyle) & SBPS_STRETCH)
            bChanged = TRUE;
         else
         {
            pSBP->nStyle = nStyle;
            pSBP->nFlags |= SBPF_UPDATE;
            SetPaneText(nIndex, pSBP->strText);
         }
         pSBP->nStyle = nStyle;
      }
      if (cxWidth != pSBP->cxText)
      {
         // change width of one pane -> invalidate the entire status bar
         pSBP->cxText = cxWidth;
         bChanged = TRUE;
      }
      if (bChanged)
         UpdateAllPanes(TRUE, FALSE);
   }

   void status_bar::GetPaneText(int nIndex, string & s)
   {
      ASSERT_VALID(this);

      AFX_STATUSPANE* pSBP = _GetPanePtr(nIndex);
      s = pSBP->strText;
   }

   string status_bar::GetPaneText(int nIndex)
   {
      ASSERT_VALID(this);

      AFX_STATUSPANE* pSBP = _GetPanePtr(nIndex);
      return pSBP->strText;
   }

   BOOL status_bar::SetPaneText(int nIndex, const char * lpszNewText, BOOL bUpdate)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      AFX_STATUSPANE* pSBP = _GetPanePtr(nIndex);

      if (!(pSBP->nFlags & SBPF_UPDATE) &&
         ((lpszNewText == NULL && pSBP->strText.is_empty()) ||
          (lpszNewText != NULL && pSBP->strText.Compare(lpszNewText) == 0)))
      {
         // nothing to change
         return TRUE;
      }

      try
      {
         if (lpszNewText != NULL)
            pSBP->strText = lpszNewText;
         else
            pSBP->strText.Empty();
      }
      catch(base_exception *)
      {
         // Note: DELETE_EXCEPTION(e) not required
         return FALSE;
      }


      if (!bUpdate)
      {
         // can't update now, wait until later
         pSBP->nFlags |= SBPF_UPDATE;
         return TRUE;
      }

      pSBP->nFlags &= ~SBPF_UPDATE;
      DefWindowProc(SB_SETTEXT, ((WORD)pSBP->nStyle)|nIndex,
         (pSBP->nStyle & SBPS_DISABLED) ? NULL :
         (LPARAM)(const char *)pSBP->strText);

      return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // status_bar implementation

   size status_bar::CalcFixedLayout(BOOL, BOOL bHorz)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      // determinme size of font being used by the status bar
      TEXTMETRIC tm;
      {
         // os independence
         throw not_implemented_exception();
   /*      CClientDC spgraphics(NULL);
         HFONT hFont = (HFONT)SendMessage(WM_GETFONT);
         HGDIOBJ hOldFont = NULL;
         if (hFont != NULL)
            hOldFont = spgraphics->SelectObject(hFont);
         VERIFY(spgraphics->GetTextMetrics(&tm));
         if (hOldFont != NULL)
            spgraphics->SelectObject(hOldFont);*/
      }

      // get border information
      class rect rect;
      rect.null();
      CalcInsideRect(rect, bHorz);
      int rgBorders[3];
      DefWindowProc(SB_GETBORDERS, 0, (LPARAM)&rgBorders);

      // determine size, including borders
      size size;
      size.cx = 32767;
      size.cy = tm.tmHeight - tm.tmInternalLeading - 1
         + rgBorders[1] * 2 + ::GetSystemMetrics(SM_CYBORDER) * 2
         - rect.height();
      if (size.cy < m_nMinHeight)
         size.cy = m_nMinHeight;

      return size;
   }


   void status_bar::_001OnNcHitTest(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::nchittest, pnchittest, pobj)
      UINT nResult = (UINT)Default();
      if (nResult == HTBOTTOMRIGHT)
      {
         pnchittest->set_lresult(HTBOTTOMRIGHT);
      }
      else
      {
         pnchittest->set_lresult(HTCLIENT);
      }
   }

   void status_bar::_001OnNcCalcSize(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::nc_calc_size, pnccalcsize, pobj)
      // calculate border space (will add to top/bottom, subtract from right/bottom)
      class rect rect;
      rect.null();
      ::userbase::control_bar::CalcInsideRect(rect, TRUE);
      ASSERT(rect.top >= 2);

      // adjust non-client area for border space
      pnccalcsize->m_pparams->rgrc[0].left += rect.left;
      pnccalcsize->m_pparams->rgrc[0].top += rect.top - 2;
      pnccalcsize->m_pparams->rgrc[0].right += rect.right;
      pnccalcsize->m_pparams->rgrc[0].bottom += rect.bottom;
   }

   void status_bar::OnBarStyleChange(DWORD dwOldStyle, DWORD dwNewStyle)
   {
      if (((dwOldStyle & CBRS_BORDER_ANY) != (dwNewStyle & CBRS_BORDER_ANY)))
      {
         // recalc non-client area when border styles change
         SetWindowPos(NULL, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
      }
   }

   /*void status_bar::OnNcPaint()
   {
      EraseNonClient();
   }*/

   // Derived class is responsible for implementing all of these handlers
   //  for owner/self draw controls.
   void status_bar::DrawItem(LPDRAWITEMSTRUCT)
   {
      ASSERT(FALSE);
   }

   BOOL status_bar::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wParam);
   // trans   if (message != WM_DRAWITEM)
   //      return ::user::interaction::OnChildNotify(message, wParam, lParam, pResult);

      ASSERT(pResult == NULL);
      UNUSED(pResult); // unused in release builds
      DrawItem((LPDRAWITEMSTRUCT)lParam);
      return TRUE;
   }

   /*void status_bar::OnPaint()
   {
      UpdateAllPanes(FALSE, TRUE);

      Default();
   }
   */

   void status_bar::_001OnDraw(::ca::graphics * pdc)
   {

      UNREFERENCED_PARAMETER(pdc);
      UpdateAllPanes(FALSE, TRUE);

      Default();
   }


   void status_bar::_001OnSize(gen::signal_object * pobj)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      pobj->previous();

      // need to adjust pane right edges (because of stretchy pane)
      UpdateAllPanes(TRUE, FALSE);
   }

   void status_bar::_001OnWindowPosChanging(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::window_pos, pwindowpos, pobj)
      // not necessary to invalidate the borders
      DWORD dwStyle = m_dwStyle;
      m_dwStyle &= ~(CBRS_BORDER_ANY);
   // trans   ::userbase::control_bar::OnWindowPosChanging(pwindowpos->m_pwindowpos);
      pwindowpos->previous();
      m_dwStyle = dwStyle;
   }

   void status_bar::_001OnSetText(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::base, pbase, pobj)
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      int nIndex = CommandToIndex(0);
      if (nIndex < 0)
      {
         pbase->set_lresult(-1);
         pbase->m_bRet = true;
         return;
      }
      pbase->set_lresult(SetPaneText(nIndex, (const char *)pbase->m_lparam) ? 0 : -1);
      pbase->m_bRet = true;
   }

   void status_bar::_001OnGetText(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::base, pbase, pobj)
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      int nMaxLen = (int)pbase->m_wparam;
      if (nMaxLen == 0)
      {
         // nothing copied
         pbase->set_lresult(0);
         pbase->m_bRet = true;
         return;
      }
      LPTSTR lpszDest = (LPTSTR)pbase->m_lparam;

      INT_PTR nLen = 0;
      int nIndex = CommandToIndex(0); // use pane with ID zero
      if (nIndex >= 0)
      {
         AFX_STATUSPANE* pSBP = _GetPanePtr(nIndex);
         nLen = pSBP->strText.get_length();
         if (nLen > nMaxLen)
            nLen = nMaxLen - 1; // number of characters to copy (less term.)
         memcpy(lpszDest, (const char *)pSBP->strText, nLen*sizeof(char));
      }
      lpszDest[nLen] = '\0';
      pbase->set_lresult(nLen+1);      // number of bytes copied
      pbase->m_bRet = true;
   }

   void status_bar::_001OnGetTextLength(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::base, pbase, pobj)

      ASSERT_VALID(this);
      ASSERT(IsWindow());

      INT_PTR nLen = 0;
      int nIndex = CommandToIndex(0); // use pane with ID zero
      if (nIndex >= 0)
      {
         AFX_STATUSPANE* pSBP = _GetPanePtr(nIndex);
         nLen = pSBP->strText.get_length();
      }
      pbase->set_lresult(nLen);
      pbase->m_bRet = true;
   }

   void status_bar::_001OnSetMinHeight(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::base, pbase, pobj)
      LRESULT lResult = Default();
      m_nMinHeight = (int)pbase->m_wparam;
      pbase->set_lresult(lResult);
   }

   /////////////////////////////////////////////////////////////////////////////
   // status_bar idle update through CStatusCmdUI class

   class CStatusCmdUI : public cmd_ui      // class private to this file!
   {
   public: // re-implementations only

      CStatusCmdUI(::ca::application *papp);
      virtual void Enable(BOOL bOn);
      virtual void SetCheck(check::e_check echeck = check::checked);
      virtual void SetText(const char * lpszText);
   };

   CStatusCmdUI::CStatusCmdUI(::ca::application *papp) :
   ca(papp),
      cmd_ui(papp)


   {
   }

   void CStatusCmdUI::Enable(BOOL bOn)
   {
      m_bEnableChanged = TRUE;
      status_bar* pStatusBar = dynamic_cast < status_bar * > (m_pOther);
      ASSERT(pStatusBar != NULL);
      ASSERT_KINDOF(status_bar, pStatusBar);
      ASSERT(m_iIndex < m_iCount);

      UINT nNewStyle = pStatusBar->GetPaneStyle((int) m_iIndex) & ~SBPS_DISABLED;
      if (!bOn)
         nNewStyle |= SBPS_DISABLED;
      pStatusBar->SetPaneStyle((int) m_iIndex, nNewStyle);
   }

   void CStatusCmdUI::SetCheck(check::e_check echeck) // "checking" will pop out the text
   {
      status_bar* pStatusBar = dynamic_cast < status_bar * > (m_pOther);
      ASSERT(pStatusBar != NULL);
      ASSERT_KINDOF(status_bar, pStatusBar);
      ASSERT(m_iIndex < m_iCount);

      UINT nNewStyle = pStatusBar->GetPaneStyle((int) m_iIndex) & ~SBPS_POPOUT;
      if (echeck != check::unchecked)
         nNewStyle |= SBPS_POPOUT;
      pStatusBar->SetPaneStyle((int) m_iIndex, nNewStyle);
   }

   void CStatusCmdUI::SetText(const char * lpszText)
   {
      status_bar* pStatusBar = dynamic_cast < status_bar * > (m_pOther);
      ASSERT(pStatusBar != NULL);
      ASSERT_KINDOF(status_bar, pStatusBar);
      ASSERT(m_iIndex < m_iCount);

      pStatusBar->SetPaneText((int) m_iIndex, lpszText);
   }


   void status_bar::OnUpdateCmdUI(userbase::frame_window* pTarget, BOOL bDisableIfNoHndler)
   {
      CStatusCmdUI state(get_app());
      state.m_pOther = this;
      state.m_iCount = (UINT)m_panea.get_count();
      for (state.m_iIndex = 0; state.m_iIndex < state.m_iCount;
         state.m_iIndex++)
      {
         state.m_id = _GetPanePtr((int) state.m_iIndex)->id;

         // allow the statusbar itself to have update handlers
         if (::user::interaction::_001OnUpdateCmdUi(&state))
            continue;

         // allow target (owner) to handle the remaining updates
         state.DoUpdate(pTarget, FALSE);
      }

      // update the dialog controls added to the status bar
      UpdateDialogControls(pTarget, bDisableIfNoHndler);
   }


   /////////////////////////////////////////////////////////////////////////////
   // status_bar diagnostics

   #ifdef _DEBUG
   void status_bar::assert_valid() const
   {
      ::userbase::control_bar::assert_valid();
   }

   void status_bar::dump(dump_context & dumpcontext) const
   {
      ::userbase::control_bar::dump(dumpcontext);

      if (dumpcontext.GetDepth() > 0)
      {
         for (int i = 0; i < m_panea.get_count(); i++)
         {
            AFX_STATUSPANE * ppane = ((status_bar *) this)->_GetPanePtr(i);
            dumpcontext << "\nstatus pane[" << i << "] = {";
            dumpcontext << "\n\tnID = " << (const char *) ppane->id;
            dumpcontext << "\n\tnStyle = " << ppane->nStyle;
            dumpcontext << "\n\tcxText = " << ppane->cxText;
            dumpcontext << "\n\tstrText = " << ppane->strText;
            dumpcontext << "\n\t}";
         }
      }
      dumpcontext << "\n";
   }
   #endif //_DEBUG

   #ifdef AFX_INIT_SEG
   #pragma code_seg(AFX_INIT_SEG)
   #endif

   // IMPLEMENT_DYNAMIC(status_bar, ::userbase::control_bar)

   /////////////////////////////////////////////////////////////////////////////


   AFX_STATUSPANE & AFX_STATUSPANE::operator = (const AFX_STATUSPANE & pane)
   {
      if(&pane == this)
         return *this;
      id = pane.id;        // IDC of indicator: 0 => normal text area
      cxText = pane.cxText;     // width of string area in pixels
                     //   on both sides there is a 3 pixel gap and
                     //   a one pixel border, making a pane 6 pixels wider
      nStyle = pane.nStyle;     // style flags (SBPS_*)
      nFlags = pane.nFlags;     // state flags (SBPF_*)
      strText = pane.strText;    // text in the pane

      return *this;
   }

   AFX_STATUSPANE::AFX_STATUSPANE()
   {
   }

   AFX_STATUSPANE::AFX_STATUSPANE(const AFX_STATUSPANE & pane)
   {
      operator =(pane);
   }


   void status_bar::SetPaneInfo(int nIndex, int iId, UINT nStyle, int cxWidth)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(iId);
      UNREFERENCED_PARAMETER(nStyle);
      UNREFERENCED_PARAMETER(cxWidth);
      //SetPaneInfo(nIndex, iId, nStyle, cxWidth);
   }

   void status_bar::SetPaneInfo(int nIndex, const char * pszId, UINT nStyle, int cxWidth)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(pszId);
      UNREFERENCED_PARAMETER(nStyle);
      UNREFERENCED_PARAMETER(cxWidth);
      //SetPaneInfo(nIndex, pszId, nStyle, cxWidth);
   }

} // namespace userbase
