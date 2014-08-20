#include "framework.h"

#define SBPF_UPDATE 0x0001  // pending update of text
#define CX_PANE_BORDER 6    // 3 pixels on each side of each pane

namespace user
{

   __STATUSPANE* status_bar::_GetPanePtr(int32_t nIndex)
   {
      return m_panea(nIndex);
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

   void status_bar::install_message_handling(::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_NCHITTEST         , pinterface, this, &status_bar::_001OnNcHitTest);
      IGUI_WIN_MSG_LINK(WM_NCCALCSIZE        , pinterface, this, &status_bar::_001OnNcCalcSize);
      IGUI_WIN_MSG_LINK(WM_SIZE              , pinterface, this, &status_bar::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_WINDOWPOSCHANGING , pinterface, this, &status_bar::_001OnWindowPosChanging);
      IGUI_WIN_MSG_LINK(WM_SETTEXT           , pinterface, this, &status_bar::_001OnSetText);
      IGUI_WIN_MSG_LINK(WM_GETTEXT           , pinterface, this, &status_bar::_001OnGetText);
      IGUI_WIN_MSG_LINK(WM_GETTEXTLENGTH     , pinterface, this, &status_bar::_001OnGetTextLength);
#ifdef WINDOWSEX
      IGUI_WIN_MSG_LINK(SB_SETMINHEIGHT      , pinterface, this, &status_bar::_001OnSetMinHeight);
#endif
   }


   bool status_bar::create_window(sp(::user::interaction) pParentWnd, uint32_t dwStyle, id strId)
   {

      return create_window_ex(pParentWnd, 0, dwStyle, null_rect(), strId);

   }

   bool status_bar::create_window_ex(sp(::user::interaction) pParentWnd,uint32_t dwCtrlStyle,uint32_t dwStyle,const RECT & rect, id strId)
   {

      ASSERT_VALID(pParentWnd);   // must have a parent

      // save the style (some of these style bits are core API specific)
      m_dwStyle = (dwStyle & CBRS_ALL);

      // translate core API style bits to windows style bits
      dwStyle &= ~CBRS_ALL;
      dwStyle |= CCS_NOPARENTALIGN|CCS_NOMOVEY|CCS_NODIVIDER|CCS_NORESIZE;
      if (pParentWnd->GetStyle() & WS_THICKFRAME)
         dwStyle |= SBARS_SIZEGRIP;
      
      return ::user::interaction::create_window(STATUSCLASSNAME, NULL, dwStyle, rect, pParentWnd, strId);

   }

   bool status_bar::pre_create_window(::user::create_struct& cs)
   {
      // in Win4, status bars do not have a border at all, since it is
      //  provided by the client area.
      if ((m_dwStyle & (CBRS_ALIGN_ANY|CBRS_BORDER_ANY)) == CBRS_BOTTOM)
         m_dwStyle &= ~(CBRS_BORDER_ANY|CBRS_BORDER_3D);

      return ::user::control_bar::pre_create_window(cs);
   }

   bool status_bar::SetIndicators(stringa & stra)
   {
      ASSERT_VALID(this);
      ASSERT(stra.get_count() >= 1);  // must be at least one of them
      //ASSERT(lpIDArray == NULL ||
   //      __is_valid_address(lpIDArray, sizeof(UINT) * nIDCount, FALSE));
      ASSERT(IsWindow());

      // first allocate array for panes and copy initial data
   //   if (!AllocElements(nIDCount, sizeof(__STATUSPANE)))
   //      return FALSE;
   //   ASSERT(nIDCount == m_panea.get_count());

      // copy initial data from indicator array
      bool bResult = TRUE;
      //if (lpIDArray != NULL)
      //{
//         HFONT hFont = (HFONT)send_message(WM_GETFONT);
         ::draw2d::graphics_sp spgraphicsScreen(allocer());

         throw todo(get_app());
/*         HGDIOBJ hOldFont = NULL;
         if (hFont != NULL)
            hOldFont = spgraphicsScreen->SelectObject(hFont);*/

         __STATUSPANE* pSBP = _GetPanePtr(0);
         for (int32_t i = 0; i < stra.get_count(); i++)
         {
            pSBP->m_id = stra[i];
            pSBP->nFlags |= SBPF_UPDATE;
            if (pSBP->m_id.has_char())
            {
   /* xxx            if (!pSBP->strText.load_string(pSBP->strId))
               {
                  TRACE(::axis::trace::category_AppMsg, 0, "Warning: failed to load indicator string 0x%04X.\n",
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
#ifdef WINDOWSEX
               pSBP->cxText = ::GetSystemMetrics(SM_CXSCREEN)/4;
               if (i == 0)
                  pSBP->nStyle |= (SBPS_STRETCH | SBPS_NOBORDERS);
#else
               throw todo(get_app());
#endif
            }
            ++pSBP;
         }
//         if (hOldFont != NULL)
  //          spgraphicsScreen->SelectObject(hOldFont);
      //}
      UpdateAllPanes(TRUE, TRUE);

      return bResult;
   }

   /*
   bool status_bar::AllocElements(int32_t nElements, int32_t cbElement)
   {
      int32_t i;

      // destruct old elements
      //__STATUSPANE* pSBP = _GetPanePtr(0);
      //for (i = 0; i < m_panea.get_count(); i++)
      //{
      //   pSBP->strText.~string();
      //   ++pSBP;
      //}

      // allocate new elements
      //if (!::user::control_bar::AllocElements(nElements, cbElement))
      //   return FALSE;

      // construct new elements
      pSBP = _GetPanePtr(0);
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

   void status_bar::CalcInsideRect(rect& rect, bool bHorz)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());
      ASSERT(bHorz);  // vertical status bar not supported

      // subtract standard ::user::control_bar borders
      ::user::control_bar::CalcInsideRect(rect, bHorz);
#ifdef WINDOWSEX
      // subtract size grip if present
      if ((GetStyle() & SBARS_SIZEGRIP) && !GetParent()->WfiIsZoomed())
      {
         // get border metrics from common control
         int32_t rgBorders[3];
         status_bar* pBar = (status_bar*)this;
         pBar->DefWindowProc(SB_GETBORDERS, 0, (LPARAM)&rgBorders);

         // size grip uses a border + size of scrollbar + cx border
         rect.right -= rgBorders[0] + ::GetSystemMetrics(SM_CXVSCROLL) +
            ::GetSystemMetrics(SM_CXBORDER) * 2;
      }
#else
      throw todo(get_app());
#endif
   }

   void status_bar::UpdateAllPanes(bool bUpdateRects, bool bUpdateText)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

#ifdef WINDOWSEX

      int32_t i;

      // update the status pane locations
      if (bUpdateRects)
      {

         // get border information and client work area
         rect rect; GetWindowRect(rect);
         rect.offset(-rect.left, -rect.top);
         CalcInsideRect(rect, TRUE);
         int32_t rgBorders[3];
         VERIFY(DefWindowProc(SB_GETBORDERS, 0, (LPARAM)&rgBorders) != FALSE);

         // determine extra space for stretchy pane
         int32_t cxExtra = rect.width() + rgBorders[2];
         int32_t nStretchyCount = 0;
         //__STATUSPANE* pSBP = _GetPanePtr(0);
         for (i = 0; i < m_panea.get_count(); i++)
         {
            __STATUSPANE* pSBP = _GetPanePtr(i);
            if (pSBP->nStyle & SBPS_STRETCH)
               ++nStretchyCount;
            cxExtra -= (pSBP->cxText+CX_PANE_BORDER + rgBorders[2]);
            //++pSBP;
         }

         // determine right edge of each pane
         int32_t* rgRights = (int32_t*)_alloca(m_panea.get_count() * sizeof(int32_t));
         int32_t right = rgBorders[0];
   //      pSBP = _GetPanePtr(0);
         for (i = 0; i < m_panea.get_count(); i++)
         {
            __STATUSPANE* pSBP = _GetPanePtr(i);
            // determine size of the pane
            ASSERT(pSBP->cxText >= 0);
            right += pSBP->cxText+CX_PANE_BORDER;
            if ((pSBP->nStyle & SBPS_STRETCH) && cxExtra > 0)
            {
               ASSERT(nStretchyCount != 0);
               int32_t cxAddExtra = cxExtra / nStretchyCount;
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
            __STATUSPANE* pSBP = _GetPanePtr(i);
            if (pSBP->nFlags & SBPF_UPDATE)
               SetPaneText(i, pSBP->strText);
            ++pSBP;
         }
      }
#else
      throw todo(get_app());
#endif
   }

   #ifdef __CORE3_SEG
   #pragma code_seg(__CORE3_SEG)
   #endif

   /////////////////////////////////////////////////////////////////////////////
   // status_bar attribute access

   int32_t status_bar::CommandToIndex(id id)
   {
      ASSERT_VALID(this);

      if (m_panea.get_count() <= 0)
         return -1;

      for (int32_t i = 0; i < m_panea.get_count(); i++)
      {
         __STATUSPANE* pSBP = _GetPanePtr(i);
         if (pSBP->m_id == id)
            return i;
      }

      return -1;
   }

   id status_bar::GetItemId(int32_t nIndex)
   {
      ASSERT_VALID(this);
      return _GetPanePtr(nIndex)->m_id;
   }

   void status_bar::GetItemRect(int32_t nIndex, LPRECT lpRect)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

#ifdef WINDOWSEX
      status_bar* pBar = (status_bar*)this;
      if (!pBar->DefWindowProc(SB_GETRECT, nIndex, (LPARAM)lpRect))
         ::SetRectEmpty(lpRect);
#else
      throw todo(get_app());
#endif
   }

   UINT status_bar::GetPaneStyle(int32_t nIndex)
   {
      return _GetPanePtr(nIndex)->nStyle;
   }

   void status_bar::SetPaneStyle(int32_t nIndex, UINT nStyle)
   {
      __STATUSPANE* pSBP = _GetPanePtr(nIndex);
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

   void status_bar::GetPaneInfo(int32_t nIndex, id & id, UINT& nStyle,
      int32_t& cxWidth)
   {
      ASSERT_VALID(this);

      __STATUSPANE* pSBP = _GetPanePtr(nIndex);
      id = pSBP->m_id;
      nStyle = pSBP->nStyle;
      cxWidth = pSBP->cxText;
   }

   void status_bar::SetPaneInfo(int32_t nIndex, id id, UINT nStyle, int32_t cxWidth)
   {
      ASSERT_VALID(this);

      bool bChanged = FALSE;
      __STATUSPANE* pSBP = _GetPanePtr(nIndex);
      pSBP->m_id = id;
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

   void status_bar::GetPaneText(int32_t nIndex, string & s)
   {
      ASSERT_VALID(this);

      __STATUSPANE* pSBP = _GetPanePtr(nIndex);
      s = pSBP->strText;
   }

   string status_bar::GetPaneText(int32_t nIndex)
   {
      ASSERT_VALID(this);

      __STATUSPANE* pSBP = _GetPanePtr(nIndex);
      return pSBP->strText;
   }

   bool status_bar::SetPaneText(int32_t nIndex, const char * lpszNewText, bool bUpdate)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      __STATUSPANE* pSBP = _GetPanePtr(nIndex);

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
      catch(::exception::base *)
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
#ifdef WINDOWSEX
      DefWindowProc(SB_SETTEXT, ((WORD)pSBP->nStyle)|nIndex,
         (pSBP->nStyle & SBPS_DISABLED) ? 0 :
         (LPARAM)(const char *)pSBP->strText);
#endif

      return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // status_bar implementation

   size status_bar::CalcFixedLayout(bool, bool bHorz)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      // determinme size of font being used by the status bar
//      TEXTMETRICW tm;
      {
         // os independence
         throw not_implemented(get_app());
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
      size size;
      size.cx =0;
      size.cy =0;

#ifdef WINDOWSEX
      int32_t rgBorders[3];
      TEXTMETRICW tm;
      DefWindowProc(SB_GETBORDERS, 0, (LPARAM)&rgBorders);

      // determine size, including borders
      size.cx = 32767;
      size.cy = tm.tmHeight - tm.tmInternalLeading - 1
         + rgBorders[1] * 2 + ::GetSystemMetrics(SM_CYBORDER) * 2
         - rect.height();
      if (size.cy < m_nMinHeight)
         size.cy = m_nMinHeight;
#endif

      return size;
   }


   void status_bar::_001OnNcHitTest(signal_details * pobj)
   {
      SCAST_PTR(::message::nchittest, pnchittest, pobj)
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

   void status_bar::_001OnNcCalcSize(signal_details * pobj)
   {
#ifdef WINDOWSEX
      SCAST_PTR(::message::nc_calc_size, pnccalcsize, pobj)
      // calculate border space (will add to top/bottom, subtract from right/bottom)
      class rect rect;
      rect.null();
      ::user::control_bar::CalcInsideRect(rect, TRUE);
      ASSERT(rect.top >= 2);

      // adjust non-client area for border space
      pnccalcsize->m_pparams->rgrc[0].left += rect.left;
      pnccalcsize->m_pparams->rgrc[0].top += rect.top - 2;
      pnccalcsize->m_pparams->rgrc[0].right += rect.right;
      pnccalcsize->m_pparams->rgrc[0].bottom += rect.bottom;
#else
      throw todo(get_app());
#endif
   }

   void status_bar::OnBarStyleChange(uint32_t dwOldStyle, uint32_t dwNewStyle)
   {

      if (((dwOldStyle & CBRS_BORDER_ANY) != (dwNewStyle & CBRS_BORDER_ANY)))
      {

         // recalc non-client area when border styles change
         SetWindowPos(0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);

      }

   }

   /*void status_bar::OnNcPaint()
   {
      EraseNonClient();
   }*/

   // Derived class is responsible for implementing all of these handlers
   //  for owner/self draw controls.
#ifdef WINDOWSEX
   void status_bar::DrawItem(LPDRAWITEMSTRUCT)
   {
      ASSERT(FALSE);
   }
#endif


   bool status_bar::OnChildNotify(::message::base * pbase)
   {

      if (pbase->m_uiMessage != WM_DRAWITEM)
         return ::user::interaction::OnChildNotify(pbase);

#ifdef WINDOWSEX
      DrawItem((LPDRAWITEMSTRUCT)pbase->m_lparam);
#endif

      return true;

   }


   /*void status_bar::OnPaint()
   {
      UpdateAllPanes(FALSE, TRUE);

      Default();
   }
   */

   void status_bar::_001OnDraw(::draw2d::graphics * pdc)
   {

      UNREFERENCED_PARAMETER(pdc);
      UpdateAllPanes(FALSE, TRUE);

      Default();
   }


   void status_bar::_001OnSize(signal_details * pobj)
   {
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      pobj->previous();

      // need to adjust pane right edges (because of stretchy pane)
      UpdateAllPanes(TRUE, FALSE);
   }

   void status_bar::_001OnWindowPosChanging(signal_details * pobj)
   {
#ifdef WINDOWSEX
      SCAST_PTR(::message::window_pos, pwindowpos, pobj)
      // not necessary to invalidate the borders
      uint32_t dwStyle = m_dwStyle;
      m_dwStyle &= ~(CBRS_BORDER_ANY);
   // trans   ::user::control_bar::OnWindowPosChanging(pwindowpos->m_pwindowpos);
      pwindowpos->previous();
      m_dwStyle = dwStyle;
#else
      throw todo(get_app());
#endif
   }

   void status_bar::_001OnSetText(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      int32_t nIndex = CommandToIndex(0);
      if (nIndex < 0)
      {
         pbase->set_lresult(-1);
         pbase->m_bRet = true;
         return;
      }
      pbase->set_lresult(SetPaneText(nIndex, (const char *)pbase->m_lparam.m_lparam) ? 0 : -1);
      pbase->m_bRet = true;
   }

   void status_bar::_001OnGetText(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
      ASSERT_VALID(this);
      ASSERT(IsWindow());

      int32_t nMaxLen = (int32_t)pbase->m_wparam;
      if (nMaxLen == 0)
      {
         // nothing copied
         pbase->set_lresult(0);
         pbase->m_bRet = true;
         return;
      }
      LPTSTR lpszDest = (LPTSTR) pbase->m_lparam.m_lparam;

      int_ptr nLen = 0;
      int32_t nIndex = CommandToIndex(0); // use pane with ID zero
      if (nIndex >= 0)
      {
         __STATUSPANE* pSBP = _GetPanePtr(nIndex);
         nLen = pSBP->strText.get_length();
         if (nLen > nMaxLen)
            nLen = nMaxLen - 1; // number of characters to copy (less term.)
         memcpy(lpszDest, (const char *)pSBP->strText, nLen*sizeof(char));
      }
      lpszDest[nLen] = '\0';
      pbase->set_lresult(nLen+1);      // number of bytes copied
      pbase->m_bRet = true;
   }

   void status_bar::_001OnGetTextLength(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)

      ASSERT_VALID(this);
      ASSERT(IsWindow());

      int_ptr nLen = 0;
      int32_t nIndex = CommandToIndex(0); // use pane with ID zero
      if (nIndex >= 0)
      {
         __STATUSPANE* pSBP = _GetPanePtr(nIndex);
         nLen = pSBP->strText.get_length();
      }
      pbase->set_lresult(nLen);
      pbase->m_bRet = true;
   }

   void status_bar::_001OnSetMinHeight(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
      LRESULT lResult = Default();
      m_nMinHeight = (int32_t)pbase->m_wparam;
      pbase->set_lresult(lResult);
   }

   /////////////////////////////////////////////////////////////////////////////
   // status_bar idle update through CStatusCmdUI class

   class CStatusCmdUI : public cmd_ui      // class private to this file!
   {
   public: // re-implementations only

      CStatusCmdUI(sp(::axis::application) papp);
      virtual void Enable(bool bOn);
      virtual void SetCheck(check::e_check echeck = check::checked);
      virtual void SetText(const char * lpszText);
   };

   CStatusCmdUI::CStatusCmdUI(sp(::axis::application) papp) :
   element(papp),
      cmd_ui(papp)


   {
   }

   void CStatusCmdUI::Enable(bool bOn)
   {
      m_bEnableChanged = TRUE;
      status_bar* pStatusBar = dynamic_cast < status_bar * > (m_pOther.m_p);
      ASSERT(pStatusBar != NULL);
      ASSERT_KINDOF(status_bar, pStatusBar);
      ASSERT(m_iIndex < m_iCount);

      UINT nNewStyle = pStatusBar->GetPaneStyle((int32_t) m_iIndex) & ~SBPS_DISABLED;
      if (!bOn)
         nNewStyle |= SBPS_DISABLED;
      pStatusBar->SetPaneStyle((int32_t) m_iIndex, nNewStyle);
   }

   void CStatusCmdUI::SetCheck(check::e_check echeck) // "checking" will pop out the text
   {
      status_bar* pStatusBar = dynamic_cast < status_bar * > (m_pOther.m_p);
      ASSERT(pStatusBar != NULL);
      ASSERT_KINDOF(status_bar, pStatusBar);
      ASSERT(m_iIndex < m_iCount);

#ifdef WINDOWSEX
      UINT nNewStyle = pStatusBar->GetPaneStyle((int32_t) m_iIndex) & ~SBPS_POPOUT;
      if (echeck != check::unchecked)
         nNewStyle |= SBPS_POPOUT;
      pStatusBar->SetPaneStyle((int32_t) m_iIndex, nNewStyle);
#else
      throw todo(get_app());
#endif

   }

   void CStatusCmdUI::SetText(const char * lpszText)
   {
      status_bar* pStatusBar = dynamic_cast < status_bar * > (m_pOther.m_p);
      ASSERT(pStatusBar != NULL);
      ASSERT_KINDOF(status_bar, pStatusBar);
      ASSERT(m_iIndex < m_iCount);

      pStatusBar->SetPaneText((int32_t) m_iIndex, lpszText);
   }


   void status_bar::OnUpdateCmdUI(sp(::user::frame_window) pTarget, bool bDisableIfNoHndler)
   {
      CStatusCmdUI state(get_app());
      state.m_pOther = this;
      state.m_iCount = (UINT)m_panea.get_count();
      for (state.m_iIndex = 0; state.m_iIndex < state.m_iCount; state.m_iIndex++)
      {
         state.m_id = _GetPanePtr((int32_t) state.m_iIndex)->m_id;

         // allow the statusbar itself to have update handlers
         if (::user::interaction::on_simple_update(&state))
            continue;

         // allow target (owner) to handle the remaining updates
         state.DoUpdate(pTarget, FALSE);
      }

      // update the dialog controls added to the status bar
      UpdateDialogControls(pTarget, bDisableIfNoHndler);
   }


   /////////////////////////////////////////////////////////////////////////////
   // status_bar diagnostics

   #ifdef DEBUG
   void status_bar::assert_valid() const
   {
      ::user::control_bar::assert_valid();
   }

   void status_bar::dump(dump_context & dumpcontext) const
   {
      ::user::control_bar::dump(dumpcontext);

      if (dumpcontext.GetDepth() > 0)
      {
         for (int32_t i = 0; i < m_panea.get_count(); i++)
         {
            __STATUSPANE * ppane = ((status_bar *) this)->_GetPanePtr(i);
            dumpcontext << "\nstatus pane[" << i << "] = {";
            dumpcontext << "\n\tnID = " << (const char *) ppane->m_id;
            dumpcontext << "\n\tnStyle = " << ppane->nStyle;
            dumpcontext << "\n\tcxText = " << ppane->cxText;
            dumpcontext << "\n\tstrText = " << ppane->strText;
            dumpcontext << "\n\t}";
         }
      }
      dumpcontext << "\n";
   }
   #endif //DEBUG

   #ifdef __INIT_SEG
   #pragma code_seg(__INIT_SEG)
   #endif

   // IMPLEMENT_DYNAMIC(status_bar, ::user::control_bar)

   /////////////////////////////////////////////////////////////////////////////


   __STATUSPANE & __STATUSPANE::operator = (const __STATUSPANE & pane)
   {
      if(&pane == this)
         return *this;
      m_id = pane.m_id;        // IDC of indicator: 0 => normal text area
      cxText = pane.cxText;     // width of string area in pixels
                     //   on both sides there is a 3 pixel gap and
                     //   a one pixel border, making a pane 6 pixels wider
      nStyle = pane.nStyle;     // style flags (SBPS_*)
      nFlags = pane.nFlags;     // state flags (SBPF_*)
      strText = pane.strText;    // text in the pane

      return *this;
   }

   __STATUSPANE::__STATUSPANE()
   {
   }

   __STATUSPANE::__STATUSPANE(const __STATUSPANE & pane)
   {
      operator =(pane);
   }


   void status_bar::SetPaneInfo(int32_t nIndex, int32_t iId, UINT nStyle, int32_t cxWidth)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(iId);
      UNREFERENCED_PARAMETER(nStyle);
      UNREFERENCED_PARAMETER(cxWidth);
      //SetPaneInfo(nIndex, iId, nStyle, cxWidth);
   }

   void status_bar::SetPaneInfo(int32_t nIndex, const char * pszId, UINT nStyle, int32_t cxWidth)
   {
      UNREFERENCED_PARAMETER(nIndex);
      UNREFERENCED_PARAMETER(pszId);
      UNREFERENCED_PARAMETER(nStyle);
      UNREFERENCED_PARAMETER(cxWidth);
      //SetPaneInfo(nIndex, pszId, nStyle, cxWidth);
   }

} // namespace user
