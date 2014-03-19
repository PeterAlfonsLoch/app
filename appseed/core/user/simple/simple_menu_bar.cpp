#include "framework.h"

#define TIMER_HOVER 321654

#define ITEMCHECKEDCX 3
#define ITEMCHECKEDCY 2
#define ITEMCHECKEDPADLEFT 2
#define ITEMCHECKEDPADTOP 2
#define ITEMCHECKEDPADRIGHT 2
#define ITEMCHECKEDPADBOTTOM 2

simple_menu_bar::simple_menu_bar(sp(base_application) papp) :
   element(papp),
   simple_toolbar(papp),
   m_menu(papp)
{
   m_bTracking = false;
   m_iTopMenuCount = 0;
   m_iTracking = -1;

   IGUI_WIN_MSG_LINK(application::APPM_LANGUAGE, this, this, &simple_menu_bar::_001OnAppLanguage);

}

simple_menu_bar::~simple_menu_bar()
{
}

void simple_menu_bar::install_message_handling(::message::dispatch * pdispatch)
{
   simple_toolbar::install_message_handling(pdispatch);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE      , pdispatch, this, &simple_menu_bar::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_NCMOUSEMOVE    , pdispatch, this, &simple_menu_bar::_001OnNcMouseMove);
   IGUI_WIN_MSG_LINK(WM_CREATE         , pdispatch, this, &simple_menu_bar::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN        , pdispatch, this, &simple_menu_bar::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_DESTROY        , pdispatch, this, &simple_menu_bar::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_MENUCHAR       , pdispatch, this, &simple_menu_bar::_001OnMenuChar);
   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN    , pdispatch, this, &simple_menu_bar::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_TIMER          , pdispatch, this, &simple_menu_bar::_001OnTimer);
   //IGUI_WIN_MSG_LINK(WM_ERASEBKGND     , pdispatch, this, *simple_menu_bar::_001On);
}


/////////////////////////////////////////////////////////////////////////////
// simple_menu_bar message handlers

bool simple_menu_bar::LoadMenuBar(UINT nIDResource)
{

   m_uiResourceID = nIDResource;

/*    m_menu.Initialize(
      m_pimagelist,
      m_pimagelistDisabled,
      m_prel,
      &m_font);

   m_menu.LoadMenu(m_uiResourceID);*/


#ifdef WINDOWSEX
   send_message(TB_SETUNICODEFORMAT, 1);
   string str;

   TBBUTTON tbb;
   memset(&tbb, 0, sizeof(tbb));
   tbb.iBitmap = 0;
   tbb.fsState = TBSTATE_ENABLED;
   tbb.fsStyle = TBSTYLE_BUTTON;
   tbb.dwData = 0;
   tbb.iString = 0;

   TBBUTTONINFOW tbbi;
   tbbi.cbSize = sizeof(tbbi);
   tbbi.dwMask = TBIF_STYLE | TBIF_TEXT ;

/*   m_buttona.set_size(mda.get_size());
   for(i = 0; i < mda.get_size(); i++)
   {
      m_buttona[i].m_wstr = mda.element_at(i).m_wstr;
   }*/
#endif

   m_bDelayedButtonLayout = true;
   //_001Layout();

   {
//      smart_pointer_array <SimpleMenu , SimpleMenu &> * psma = NULL;
   }

   return true;
}

void simple_menu_bar::SetMenuID(UINT uiResourceID)
{
   m_uiResourceID = uiResourceID;
}

bool simple_menu_bar::pre_create_window(CREATESTRUCT& cs)
{
   return simple_toolbar::pre_create_window(cs);
}


/*void simple_menu_bar::OnDropDown(NMHDR * pNotifyStruct, LRESULT* result )
{
    LPNMTOOLBAR lpnmtb = (LPNMTOOLBAR) pNotifyStruct;

//    m_pwthreadTracking = (CMenuTrackingThreadV033*) __begin_thread(System.type_info < CMenuTrackingThreadV033 > ());
  //  m_pwthreadTracking->m_evInitialized.lock();
    //m_pwthreadTracking->GetMainWnd()->SendMessage(WM_USER, 3, (LPARAM) this);
    //m_pwthreadTracking->GetMainWnd()->SendMessage(WM_USER, 4, lpnmtb->iItem);
    TRACE("MenuBarV033::OnDropDown simple_menu_bar::_TrackPopupMenu % d\n", lpnmtb->iItem);
    _TrackPopupMenu(lpnmtb->iItem);

    *result = TBDDRET_DEFAULT;
}*/

/*bool simple_menu_bar::GetMenu(SimpleMenu **ppmenu)
{
    *ppmenu = m_pmenu;
    return ;
}*/


bool simple_menu_bar::_001OnCmdMsg(base_cmd_msg * pcmdmsg)
{
   // TODO: add your specialized code here and/or call the base class

   return simple_toolbar::_001OnCmdMsg(pcmdmsg);
}


void simple_menu_bar::_001OnMouseMove(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj)
   _001Hover(pmouse->m_pt);
   pobj->previous();
}


bool simple_menu_bar::_TrackPopupMenu(int32_t iItem)
{
    TRACE("simple_menu_bar::_TrackPopupMenu % d\n", iItem);
    m_iTracking = iItem;
    m_iButtonPressItem = iItem;
    _001RedrawWindow();
    rect rect;
    _001GetItemRect(iItem, rect, ElementItem);
    ClientToScreen(rect);

#ifdef WINDOWSEX
    TPMPARAMS tpm;
    tpm.cbSize = sizeof(TPMPARAMS);
    tpm.rcExclude.top    = rect.top;
    tpm.rcExclude.left   = rect.left;
    tpm.rcExclude.bottom = rect.bottom;
    tpm.rcExclude.right  = rect.right;
#endif
//    smart_pointer_array <SimpleMenu , SimpleMenu &> * psma = NULL;



//    oswindow oswindowOld = __get_thread_state()->m_hTrackingWindow;
//    m_oswindowFilter = NULL;
    return true;

}

void simple_menu_bar::_001OnNcMouseMove(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj)
   _001Hover(pmouse->m_pt);
// trans   simple_toolbar::OnNcMouseMove(pmouse->m_nFlags, pmouse->m_pt);
}

void simple_menu_bar::pre_translate_message(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   if(pbase->m_uiMessage == WM_USER && pbase->m_pwnd == this)
   {
      if(pbase->m_wparam == 33)
      {
         _TrackPopupMenu((int32_t) pbase->m_lparam);
      }
   }
   TRACE("simple_menu_bar::pre_translate_message messageID=%d wParam=%d lParam=%d\n", pbase->m_uiMessage, pbase->m_wparam, pbase->m_lparam);
   return simple_toolbar::pre_translate_message(pobj);
}

void simple_menu_bar::_001OnCreate(signal_details * pobj)
{
//   SCAST_PTR(::message::create, pcreate, pobj)
   if(pobj->previous())
      return;

/*   MessageFilterHookManager * lpmfmh = NULL;
   if(!MessageFilterHookManager::AppGetMessageFilterHookManager(&lpmfmh))
   {
      pcreate->set_lresult(-1);
      pcreate->m_bRet = true;
      return;
   }

   ASSERT(lpmfmh != NULL);
   lpmfmh->MessageFilterHook(this);*/

   //m_menuhook.Install((sp(::user::frame_window)) (sp(::user::interaction))this);

   SetFont(System.visual().font_central().GetMenuFont());

   UpdateWindow();
}

LRESULT CALLBACK simple_menu_bar::MessageProc(
  int32_t code,       // hook code
  WPARAM wParam,  // undefined
  LPARAM lParam   // address of structure with message data
)
{
   UNREFERENCED_PARAMETER(wParam);
    LPMESSAGE pmsg = (LPMESSAGE) lParam;

    if(code == MSGF_MENU)
    {
/*        ASSERT(pmsg->oswindow == m_oswindowFilter);*/

        if(pmsg->message == WM_MOUSEMOVE)
        {
            uint32_t fwKeys = (uint32_t) pmsg->wParam;        // key flags
            int32_t xPos = LOWORD(pmsg->lParam);  // horizontal position of cursor
            int32_t yPos = HIWORD(pmsg->lParam);
            TRACE("simple_menu_bar::MessageProc %d %d %d \n", fwKeys, xPos, yPos);
            point pt(xPos, yPos);
            ScreenToClient(&pt);
            _TrackPopupMenu(pt);

        }
    }

    return 0;
}


bool simple_menu_bar::_TrackPopupMenu(point point)
{
   if(m_bTracking)
   {
      int32_t iItem = _001HitTest(point);
      if(iItem >= 0 &&
         iItem < m_iTopMenuCount &&
         iItem != m_iTracking)
      {
         TRACE("simple_menu_bar::OnMouseMove simple_menu_bar::_TrackPopupMenu % d\n", iItem);
         //            SendMessage(WM_KEYDOWN, VK_ESCAPE);
         //            if(m_iTracking >= 0)
         //          {
                send_message(WM_CANCELMODE);
    //        }
            send_message(WM_USER, 33, iItem);
            //return _TrackPopupMenu(iItem);
        }
    }

    return true;

}

void simple_menu_bar::_001OnKeyDown(signal_details * pobj)
{
   // TODO: add your message handler code here and/or call default

   pobj->previous();
}



/*bool simple_menu_bar::CalcSize(::user::tool_bar_control & tbc, size & size)
{
    rect rectItem;
    rect rectSize(0, 0, 0, 0);

    for(int32_t i = 0; i < tbc.GetButtonCount(); i++)
    {
        tbc.GetItemRect(i, rectItem);
        rectSize.union(rectSize, rectItem);
    }
    size = rectSize.size();
    return ;
}

bool simple_menu_bar::CalcSize(CToolBarCtrl & tbc, size & size)
{
    rect rectItem;
    rect rectSize(0, 0, 0, 0);

    for(int32_t i = 0; i < tbc.GetButtonCount(); i++)
    {
        tbc.GetItemRect(i, rectItem);
        rectSize.union(rectSize, rectItem);
    }
    size = rectSize.size();
    return ;
}*/



void simple_menu_bar::_001OnDestroy(signal_details * pobj)
{
   pobj->previous();

/*   MessageFilterHookManager * lpmfmh = NULL;
   if(MessageFilterHookManager::AppGetMessageFilterHookManager(&lpmfmh)
      && lpmfmh != NULL)
   {
      lpmfmh->MessageFilterUnhook(this);
   }*/
}

bool simple_menu_bar::Initialize(
   sp(image_list)   pimagelist,
   sp(image_list)   pimagelistDisabled,
   int_int_spreadset * prel,
   ::draw2d::font *        pfont)
{

//   m_menuhook.Initialize(
  //    pimagelist,
      //pimagelistDisabled,
      //prel,
      //pfont);

   m_pimagelist            = pimagelist;
   m_pimagelistDisabled    = pimagelistDisabled;
   m_prel                  = prel;

   m_font->operator=(*pfont);

   return true;
}

void simple_menu_bar::RemoveAllButtons()
{
   m_itema.remove_all();
}

void simple_menu_bar::_001OnMenuChar(signal_details * pobj)
{
   pobj->previous();
}

void simple_menu_bar::OnUpdateCmdUI(sp(::user::frame_window)pTarget, bool bDisableIfNoHndler)
{
   UNREFERENCED_PARAMETER(pTarget);
   UNREFERENCED_PARAMETER(bDisableIfNoHndler);
   return;
/*   tool_cmd_ui state;
   state.m_pOther = this;

   state.m_nIndexMax = (UINT)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
   for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax; state.m_nIndex++)
   {
      // get buttons state
      TBBUTTON button;
      _GetButton(state.m_nIndex, &button);
      state.m_nID = button.idCommand;

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
   UpdateDialogControls(pTarget, bDisableIfNoHndler);*/
}


int32_t simple_menu_bar::OnMessage(MPARAM mparam, NPARAM nparam, OPARAM oparam)
{
   UNREFERENCED_PARAMETER(nparam);
   UNREFERENCED_PARAMETER(oparam);
   if(mparam == MX_APPLANGUAGE)
   {
      ReloadMenuBar();
   }
   return 0;
}

bool simple_menu_bar::ReloadMenuBar()
{
   if(!LoadMenuBar(m_uiResourceID))
      return false;

   return true;
}

/*void simple_menu_bar::_001OnDraw(::draw2d::graphics *pdc)
{
   rect rectClient;
   GetClientRect(rectClient);
   class imaging & imaging = System.visual().imaging();
   if(m_iHover >= -1)
   {
      imaging.color_blend(
         pdc,
         rectClient.left,
         rectClient.top,
         rectClient.width(),
         rectClient.height(),
         RGB(255, 255, 250),
         128);
   }
   else
   {
      imaging.color_blend(
         pdc,
         rectClient.left,
         rectClient.top,
         rectClient.width(),
         rectClient.height(),
         RGB(230, 230, 225),
         56);
   }

   pdc->SelectObject(System.visual().font_central().GetMenuFont());
   pdc->SetBkMode(TRANSPARENT);
   for(int32_t iItem = 0; iItem < m_buttona.get_size(); iItem++)
   {
      _001DrawItem(pdc, iItem);
   }

}
*/
/*bool simple_menu_bar::_001GetItemRect(int32_t iItem, LPRECT lprect, EElement eelement)
{
   if(iItem < 0 ||
      iItem >= m_buttona.get_size())
      return false;

   switch(eelement)
   {
   case ElementItem:
      lprect->left   = m_buttona[iItem].m_rect.left + ITEMCHECKEDCX;
      lprect->right  = m_buttona[iItem].m_rect.right + ITEMCHECKEDPADRIGHT;
      lprect->top    = m_buttona[iItem].m_rect.top + ITEMCHECKEDCY;
      lprect->bottom = m_buttona[iItem].m_rect.bottom;
      break;
   case ElementItemHover:
      lprect->left   = m_buttona[iItem].m_rect.left - ITEMCHECKEDPADLEFT;
      lprect->right  = m_buttona[iItem].m_rect.right - ITEMCHECKEDCX + ITEMCHECKEDPADRIGHT;
      lprect->top    = m_buttona[iItem].m_rect.top;
      lprect->bottom = m_buttona[iItem].m_rect.bottom - ITEMCHECKEDCY;
      break;
   case ElementText:
      lprect->left   = m_buttona[iItem].m_rect.left + ITEMCHECKEDCX;
      lprect->right  = m_buttona[iItem].m_rect.right;
      lprect->top    = m_buttona[iItem].m_rect.top + ITEMCHECKEDCY;
      lprect->bottom = m_buttona[iItem].m_rect.bottom;
      break;
   case ElementTextHover:
      lprect->left   = m_buttona[iItem].m_rect.left + ITEMCHECKEDPADLEFT;
      lprect->right  = m_buttona[iItem].m_rect.right - ITEMCHECKEDPADRIGHT - ITEMCHECKEDCX;
      lprect->top    = m_buttona[iItem].m_rect.top + ITEMCHECKEDPADTOP;
      lprect->bottom = m_buttona[iItem].m_rect.bottom - ITEMCHECKEDPADBOTTOM - ITEMCHECKEDCY;
      break;
   default:
      break;
   }
   return true;
}*/

/*bool simple_menu_bar::_001CheckItem(int32_t iItem, bool bCheck)
{
   if(iItem < 0 ||
      iItem >= m_buttona.get_size())
      return false;
//   m_buttona[iItem].m_bCheck = bCheck;
   return true;
}

int32_t simple_menu_bar::_001HitTest(const POINT *lppoint)
{
   for(int32_t iItem = 0; iItem < m_buttona.get_size(); iItem++)
   {
      if(m_buttona[iItem].m_rect.contains(*lppoint))
         return iItem;
   }
   rect rectClient;
   GetClientRect(rectClient);
   if(rectClient.contains(*lppoint))
      return -1;
   else
      return 0x80000000;
}*/

/*void simple_menu_bar::_001Layout()
{
   ::draw2d::memory_graphics pdc(this);;
   pdc->SelectObject(System.visual().font_central().GetMenuFont());

   size size;
   int32_t ix = ITEMCHECKEDPADLEFT;
   int32_t iy = 0;
   for(int32_t iItem = 0; iItem < m_buttona.get_size(); iItem++)
   {
      ::GetTextExtentPoint32W(
         (HDC)pdc->get_os_data(),
         m_buttona[iItem].m_wstr,
         m_buttona[iItem].m_wstr.get_length(),
         &size);
      m_buttona[iItem].m_rect.left  = ix ;
      ix += size.cx + ITEMCHECKEDCX + ITEMCHECKEDPADLEFT + ITEMCHECKEDPADRIGHT;
      m_buttona[iItem].m_rect.right = ix;
      m_buttona[iItem].m_rect.top   = 0;
      iy = max(iy, size.cy);
   }
   for(iItem = 0; iItem < m_buttona.get_size(); iItem++)
   {
      m_buttona[iItem].m_rect.bottom = iy + ITEMCHECKEDCX + ITEMCHECKEDPADTOP + ITEMCHECKEDPADBOTTOM;
   }


}*/


bool simple_menu_bar::create(sp(::user::interaction) pParentWnd, uint32_t dwStyle, UINT nID)
{
   return CreateEx(pParentWnd, 0, dwStyle,
      rect(m_cxLeftBorder, m_cyTopBorder, m_cxRightBorder, m_cyBottomBorder), nID);
}

bool simple_menu_bar::CreateEx(sp(::user::interaction) pParentWnd, uint32_t dwCtrlStyle, uint32_t dwStyle, rect rcBorders, UINT nID)
{
   ASSERT_VALID(pParentWnd);   // must have a parent
   ASSERT (!((dwStyle & CBRS_SIZE_FIXED) && (dwStyle & CBRS_SIZE_DYNAMIC)));

   SetBorders(rcBorders);

   // save the style
   m_dwStyle = (dwStyle & CBRS_ALL);
   if (nID == __IDW_TOOLBAR)
      m_dwStyle |= CBRS_HIDE_INPLACE;

   dwStyle &= ~CBRS_ALL;
#ifdef WINDOWSEX
   dwStyle |= CCS_NOPARENTALIGN|CCS_NOMOVEY|CCS_NODIVIDER|CCS_NORESIZE;
#endif
   dwStyle |= dwCtrlStyle;

//   ASSERT(gen_ComCtlVersion != -1);
//   _::core::GetDropDownWidth();
//   ASSERT(gen_DropDownWidth != -1);

   // create the oswindow
   if (!::user::interaction::create(NULL, NULL, dwStyle, ::null_rect(), pParentWnd, nID))
      return FALSE;

   // sync up the sizes
//   SetSizes(m_sizeButton, m_sizeImage);

   // Note: Parent must resize itself for control bar to be resized

   return TRUE;
}

void simple_menu_bar::_001OnLButtonDown(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj)
   int32_t iItem = _001HitTest(pmouse->m_pt);
   if(iItem >= 0)
   {
      _001OnDropDown(iItem);
   }
   else
   {
    // trans  simple_toolbar::OnLButtonDown(pmouse->m_nFlags, pmouse->m_pt);
   }
}

/*size simple_menu_bar::CalcDynamicLayout(int32_t nLength, uint32_t dwMode)
{
    if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
      ((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
   {
      return CalcFixedLayout(dwMode & LM_STRETCH, dwMode & LM_HORZDOCK);
   }
   return CalcLayout(dwMode, nLength);

}
size simple_menu_bar::CalcLayout(uint32_t dwMode, int32_t nLength)
{
   _001Layout();
   size sizeResult;
   sizeResult.cx = 0;
   sizeResult.cy = 0;

   if(m_buttona.get_size() > 0)
   {
      sizeResult.cx = m_buttona[m_buttona.get_size() - 1].m_rect.right + ITEMCHECKEDPADRIGHT;
      sizeResult.cy = m_buttona[m_buttona.get_size() - 1].m_rect.bottom;
   }

   return sizeResult;
}

size simple_menu_bar::CalcFixedLayout(bool bStretch, bool bHorz)
{
   uint32_t dwMode = bStretch ? LM_STRETCH : 0;
   dwMode |= bHorz ? LM_HORZ : 0;

   return CalcLayout(dwMode, -1);
}
*/

/*void simple_menu_bar::_001DrawItem(::draw2d::graphics *pdc, int32_t iItem)
{
   rect rectItem;
   rect rectText;

   SimpleMenuBarButton & button = m_buttona[iItem];


   EElement eelement = ElementItem;
   EElement eelementText = ElementText;
   if(m_iTracking >= 0)
   {
      if(iItem == m_iTracking)
      {
         eelement = ElementItemHover;
         eelementText = ElementTextHover;
      }
   }
   else
   {
      if(iItem == m_iHover)
      {
         eelement = ElementItemHover;
         eelementText = ElementTextHover;
      }
   }

   _001GetItemRect(iItem, rectItem, eelement);
   _001GetItemRect(iItem, rectText, eelementText);

   if(eelement == ElementItemHover)
   {
      rect rectShadow;
      _001GetItemRect(iItem, rectShadow, ElementItem);

      ::draw2d::pen_sp penShadow(get_app(), PS_SOLID, 1, RGB(127, 127, 127));
      ::draw2d::brush_sp brushShadow(get_app(), RGB(127, 127, 127));
      ::draw2d::pen * ppenOld = pdc->SelectObject(penShadow);
      ::draw2d::brush * pbrushOld = pdc->SelectObject(brushShadow);
      pdc->Rectangle(rectShadow);

      ::draw2d::pen_sp pen(get_app(), PS_SOLID, 1, RGB(92, 92, 92));
      ::draw2d::brush_sp brush(get_app(), RGB(255, 255, 255));
      pdc->SelectObject(pen);
      pdc->SelectObject(brush);
      pdc->Rectangle(rectItem);
      pdc->SelectObject(ppenOld);
      pdc->SelectObject(pbrushOld);

      rect rect;
      _001GetItemRect(iItem, rect, ElementText);
      pdc->set_text_color(RGB(192, 192, 192));
      visual::graphics_extension::_DrawText(pdc,
         button.m_wstr,
         rect,
         DT_VCENTER | DT_LEFT);
   }

   pdc->set_text_color(RGB(0, 0, 0));
   visual::graphics_extension::_DrawText(pdc,
      button.m_wstr,
      rectText,
      DT_VCENTER | DT_LEFT);


}
*/

/*SimpleMenuBarButton::SimpleMenuBarButton()
{
//   m_bCheck = false;
}*/

/*void simple_menu_bar::_001Hover(point pt)
{
   _TrackPopupMenu(pt);
   int32_t iHover = -1;
   if(m_iTracking >= 0)
   {
      iHover   = m_iTracking;
      m_iHover = iHover;
   }
   else
   {
      iHover = _001HitTest(&pt);
   }
   if(m_iHover != iHover)
   {
      m_iHover = iHover;
      if(m_iHover < -1 && m_iTracking < 0)
      {
         KillTimer(TIMER_HOVER);
      }
      else
      {
         SetTimer(TIMER_HOVER, 50, NULL);
      }
      _001RedrawWindow();
   }
}

void simple_menu_bar::_001Hover()
{
   point pt;
   GetCursorPos(&pt);
   ScreenToClient(&pt);
   _001Hover(pt);
}*/

void simple_menu_bar::_001OnTimer(signal_details * pobj)
{
   SCAST_PTR(::message::timer, ptimer, pobj)
   if(ptimer->m_nIDEvent == TIMER_HOVER)
   {
      _001Hover();
   }

   pobj->previous();
}

/*
bool simple_menu_bar::OnEraseBkgnd(::draw2d::graphics * pgraphics)
{
   return TRUE;
}
*/

/*int32_t simple_menu_bar::_001GetHoverItem()
{
   return m_iHover;
}*/

void simple_menu_bar::_001OnDropDown(int32_t iItem)
{
   _TrackPopupMenu(iItem);
}

void simple_menu_bar::_001OnClick(int32_t iItem)
{
   UNREFERENCED_PARAMETER(iItem);
}


void simple_menu_bar::OnUpdateHover()
{
   if(m_iHover >= 0)
   {
      //_TrackPopupMenu(m_iHover);
   }
}

int32_t simple_menu_bar::_001GetHoverItem()
{
   if(m_iTracking >= 0)
   {
      return m_iTracking;
   }
   else
   {
      return simple_toolbar::_001GetHoverItem();
   }
}

void simple_menu_bar::_001OnAppLanguage(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj)
   send_message(WM_CANCELMODE);
   LoadMenuBar(m_uiResourceID);
   _001RedrawWindow();
   pbase->m_bRet = false;
}
