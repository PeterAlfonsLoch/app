#include "framework.h"

#define TIMER_HOVER 321654

class SimpleToolCmdUI : public cmd_ui        // class private to this file !
{
public: // re-implementations only

   SimpleToolCmdUI(sp(::base::application) papp);
   virtual void Enable(bool bOn = TRUE, ::action::context actioncontext = ::action::source_system);
//   virtual void _001SetCheck(bool bCheck, ::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
   virtual void _001SetCheck(check::e_check echeck, ::action::context = ::action::source_system);   // 0, 1 or 2 (indeterminate)
//   virtual void SetRadio(bool bOn = TRUE, ::action::context actioncontext = ::action::source_system);
   virtual void SetText(const char * lpszText, ::action::context actioncontext = ::action::source_system);
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define ITEMHOVERCX 0
#define ITEMHOVERCY 0
/*#define ITEMHOVERPADLEFT 2
#define ITEMHOVERPADTOP 2
#define ITEMHOVERPADRIGHT 2
#define ITEMHOVERPADBOTTOM 2*/
#define ITEMPRESSCX 4
#define ITEMPRESSCY 3
/*#define ITEMPRESSPADLEFT 2
#define ITEMPRESSPADTOP 2
#define ITEMPRESSPADRIGHT 2
#define ITEMPRESSPADBOTTOM 2*/
#define ITEMCX 3
#define ITEMCY 2
#define ITEMPADLEFT     3
#define ITEMPADTOP      3
#define ITEMPADRIGHT    3
#define ITEMPADBOTTOM   4


simple_toolbar::simple_toolbar(sp(::base::application) papp) :
element(papp),
   m_dibDraft(allocer())
{
   m_iHover = 0x80000000;



   m_etranslucency = TranslucencyPresent;

   m_iButtonPressItem      = -1;
   //m_pimagelist            = NULL;
   //m_pimagelistHue         = NULL;
   //m_pimagelistBlend       = NULL;
   //m_pimagelistHueLight    = NULL;
   //   m_bInternalImageList    = true;

   m_bTransparentBackground = true;
   // default image sizes
   m_sizeImage.cx = 16;
   m_sizeImage.cy = 15;

   // default button sizes
   m_sizeButton.cx = 23;
   m_sizeButton.cy = 22;

   m_bDelayedButtonLayout = true;
}

simple_toolbar::~simple_toolbar()
{

}

void simple_toolbar::install_message_handling(::message::dispatch * pdispatch)
{
   ::user::control_bar::install_message_handling(pdispatch);
   //IGUI_WIN_MSG_LINK(WM_ERASEBKGND()
   IGUI_WIN_MSG_LINK(WM_CREATE         , pdispatch, this, &simple_toolbar::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE      , pdispatch, this, &simple_toolbar::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN    , pdispatch, this, &simple_toolbar::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_TIMER          , pdispatch, this, &simple_toolbar::_001OnTimer);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP      , pdispatch, this, &simple_toolbar::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_NCCALCSIZE     , pdispatch, this, &simple_toolbar::_001OnNcCalcSize);
   IGUI_WIN_MSG_LINK(WM_NCHITTEST      , pdispatch, this, &simple_toolbar::_001OnNcHitTest);
   IGUI_WIN_MSG_LINK(WM_MOVE           , pdispatch, this, &simple_toolbar::_001OnMove);
   IGUI_WIN_MSG_LINK(WM_MOUSELEAVE     , pdispatch, this, &simple_toolbar::_001OnMouseLeave);
}

// IMPLEMENT_DYNAMIC(simple_toolbar, ::user::control_bar)


bool simple_toolbar::create(sp(::user::interaction) pParentWnd, uint32_t dwStyle, id nID)
{
   return CreateEx(pParentWnd, 0, dwStyle,
      rect(m_cxLeftBorder, m_cyTopBorder, m_cxRightBorder, m_cyBottomBorder), nID);
}

bool simple_toolbar::CreateEx(sp(::user::interaction) pParentWnd, uint32_t dwCtrlStyle, uint32_t dwStyle, rect rcBorders, id nID)
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
#else
//   throw todo(get_app());
#endif
   dwStyle |= dwCtrlStyle & 0xffff;

#ifdef WINDOWSEX
   m_dwCtrlStyle = dwCtrlStyle & (0xffff0000 | TBSTYLE_FLAT);
#else
  // throw todo(get_app());
#endif


   if (!::user::interaction::create(NULL, NULL, dwStyle, ::null_rect(), pParentWnd, nID))
      return FALSE;

   // sync up the sizes
   SetSizes(m_sizeButton, m_sizeImage);

   // Note: Parent must resize itself for control bar to be resized

   return TRUE;
}


size simple_toolbar::CalcFixedLayout(bool bStretch, bool bHorz)
{
   uint32_t dwMode = bStretch ? LM_STRETCH : 0;
   dwMode |= bHorz ? LM_HORZ : 0;

   return CalcLayout(dwMode);

   /*   size size;
   if(m_bSimpleLayout)
   {
   CalcSize(size, bHorz != 0);
   return size;
   }
   else
   {
   return ::user::control_bar::CalcFixedLayout(bStretch, bHorz);
   }*/
}



size simple_toolbar::CalcSimpleLayout()
{
   ASSERT_VALID(this);
   ASSERT(IsWindow());


   ::count nCount;
   size sizeResult(0,0);

   //BLOCK: Load Buttons
   nCount = m_itema.get_count();
   if (nCount > 0)
   {
      /*      int32_t i;
      for (i = 0; i < nCount; i++)
      {
      m_itema[i].fsState &= ~TBSTATE_WRAP;
      }
      for (i = 0; i < nCount; i++)
      {
      _SetButton(i, &m_itema[i]);
      }
      for (i = 0; i < nCount; i++)
      _GetButton(i, &m_itema[i]);
      for (i = 0; i < nCount; i++)
      {
      if(m_itema[i].fsState & TBSTATE_WRAP)
      ASSERT(FALSE);
      }*/
      rect rectItem;
      rect rectSize(0, 0, 0, 0);
      for (int32_t i = 0; i < nCount; i++)
      {
         _001GetItemRect(i, rectItem);
         rectSize.unite(rectSize, rectItem);
      }
      sizeResult = rectSize.size();

      //delete[] m_itema;
   }
#ifdef WINDOWSEX
   if(GetStyle() & TBSTYLE_FLAT)
   {
      sizeResult.cy += 2;
   }
#else
   throw todo(get_app());
#endif
   return sizeResult;
}

void simple_toolbar::_001OnDraw(::draw2d::graphics *pdc)
{

   if(m_bDelayedButtonLayout)
      layout();

   //DoPaint(pdc);

   pdc->SelectObject(System.visual().font_central().GetMenuFont());
//   pdc->SetBkMode(TRANSPARENT);
   for(int32_t iItem = 0; iItem < m_itema.get_size(); iItem++)
   {
      _001DrawItem(pdc, iItem);
   }

}

/*
bool simple_toolbar::OnEraseBkgnd(::draw2d::graphics * pgraphics)
{
return true;
}
*/


void simple_toolbar::SetTransparentBackground(bool bSet)
{
   m_bTransparentBackground = bSet;
}

void simple_toolbar::TransparentEraseNonClient(::draw2d::graphics * pdc)
{

   m_dibDraft->get_graphics()->BitBlt(0, 0, 7, 7, pdc, 0, 0, SRCCOPY);

   rect rectWindow;
   GetWindowRect(rectWindow);
   rectWindow.offset(-rectWindow.top_left());
   if(m_bTransparentBackground)
   {
      class imaging & imaging = System.visual().imaging();
      if(m_iHover >= -1)
      {
         imaging.color_blend(
            pdc,
            rectWindow.left,
            rectWindow.top,
            rectWindow.width(),
            rectWindow.height(),
            RGB(215, 215, 210),
            220);
      }
      else
      {
         imaging.color_blend(
            pdc,
            rectWindow.left,
            rectWindow.top,
            rectWindow.width(),
            rectWindow.height(),
            RGB(215, 215, 210),
            180);
      }
   }
   else
   {
#ifdef WINDOWSEX
      pdc->FillSolidRect(rectWindow, BaseSession.get_default_color(COLOR_3DFACE));
#else
      pdc->FillSolidRect(rectWindow, ARGB(255, 184, 184, 177));
#endif
   }

   // Desenha chanfro
   COLORREF cr = m_dibDraft->GetPixel(0, 0);
   pdc->SetPixel(0, 0, cr);
   pdc->SetPixel(0, 1, m_dibDraft->GetPixel(0, 1));
   pdc->SetPixel(0, 2, m_dibDraft->GetPixel(0, 2));
   pdc->SetPixel(0, 3, m_dibDraft->GetPixel(0, 3));
   pdc->SetPixel(0, 4, m_dibDraft->GetPixel(0, 4));
   pdc->SetPixel(0, 5, m_dibDraft->GetPixel(0, 5));
   pdc->SetPixel(0, 6, m_dibDraft->GetPixel(0, 6));
   pdc->SetPixel(1, 0, m_dibDraft->GetPixel(1, 0));
   pdc->SetPixel(1, 1, m_dibDraft->GetPixel(1, 1));
   pdc->SetPixel(1, 2, m_dibDraft->GetPixel(1, 2));
   pdc->SetPixel(1, 3, m_dibDraft->GetPixel(1, 3));
   pdc->SetPixel(1, 4, m_dibDraft->GetPixel(1, 4));
   pdc->SetPixel(1, 5, m_dibDraft->GetPixel(1, 5));
   pdc->SetPixel(2, 0, m_dibDraft->GetPixel(2, 0));
   pdc->SetPixel(2, 1, m_dibDraft->GetPixel(2, 1));
   pdc->SetPixel(2, 2, m_dibDraft->GetPixel(2, 2));
   pdc->SetPixel(2, 3, m_dibDraft->GetPixel(2, 3));
   pdc->SetPixel(2, 4, m_dibDraft->GetPixel(2, 4));
   pdc->SetPixel(3, 0, m_dibDraft->GetPixel(3, 0));
   pdc->SetPixel(3, 1, m_dibDraft->GetPixel(3, 1));
   pdc->SetPixel(3, 2, m_dibDraft->GetPixel(3, 2));
   pdc->SetPixel(3, 3, m_dibDraft->GetPixel(3, 3));
   pdc->SetPixel(4, 0, m_dibDraft->GetPixel(4, 0));
   pdc->SetPixel(4, 1, m_dibDraft->GetPixel(4, 1));
   pdc->SetPixel(4, 2, m_dibDraft->GetPixel(4, 2));
   pdc->SetPixel(5, 0, m_dibDraft->GetPixel(5, 0));
   pdc->SetPixel(5, 1, m_dibDraft->GetPixel(5, 1));
   pdc->SetPixel(6, 0, m_dibDraft->GetPixel(6, 0));


   //pdc->BitBlt(0, 0, 7, 7, &m_dcDraft, 0, 0, SRCCOPY);

   //

   // draw borders in non-client area
   DrawBorders(pdc, rectWindow);
   /*   pdc->FillSolidRect(
   rectWindow.left + 7, rectWindow.top,
   rectWindow.right, rectWindow.top + 1,
   RGB(128, 128, 123));*/

   // erase parts not drawn
   //pdc->IntersectClipRect(rectWindow);
   //SendMessage(WM_ERASEBKGND, (WPARAM)pdc->get_handle1());

   // draw gripper in non-client area
   DrawGripper(pdc, rectWindow);

   //pdc->SetViewportOrg(ptViewport);
}


void simple_toolbar::_001OnCreate(signal_details * pobj)
{
   if(pobj->previous())
      return;

   m_dibDraft->create(20, 20);
}


void simple_toolbar::OnUpdateCmdUI(sp(::user::frame_window) pTarget, bool bDisableIfNoHndler)
{

   SimpleToolCmdUI state(get_app());

   state.m_pOther =  (this);

   state.m_iCount = _001GetItemCount();

   for (state.m_iIndex = 0; state.m_iIndex < state.m_iCount; state.m_iIndex++)
   {

      // ignore separators
      if(m_itema[state.m_iIndex].m_id != "separator")
      {

         state.m_id = m_itema[state.m_iIndex].m_id;

         state.m_bEnableIfHasCommandHandler = m_itema[state.m_iIndex].m_bEnableIfHasCommandHandler;

         // allow reflections
         //if (::user::interaction::on_simple_action(0,
         //   MAKELONG((int32_t)CN_UPDATE_COMMAND_UI, WM_COMMAND+WM_REFLECT_BASE),
         //   &state, NULL))
         //   continue;

         // allow the toolbar itself to have update handlers
         if(_001SendUpdateCmdUi(&state))
            continue;

         // allow the owner to process the update
         state.DoUpdate(pTarget, bDisableIfNoHndler);
      }

   }

   // update the dialog controls added to the toolbar
   UpdateDialogControls(pTarget, bDisableIfNoHndler);

}

#define CX_OVERLAP 0

size simple_toolbar::CalcSize(int32_t nCount)
{
   ASSERT(nCount > 0);

   point cur(0,0);
   size sizeResult(0,0);

   //   uint32_t dwExtendedStyle = DefWindowProc(TB_GETEXTENDEDSTYLE, 0, 0);
#if defined(WINDOWSEX) || defined(LINUX) || defined(METROWIN) || defined(APPLEOS)

   int32_t buttonx, buttony;

   for (int32_t i = 0; i < nCount; i++)
   {
      //WINBUG: The IE4 version of COMCTL32.DLL calculates the separation
      //  on a TBSTYLE_WRAP button as 100% of the value in iBitmap compared
      //  to the other versions which calculate it at 2/3 of that value.
      //  This is actually a bug which should be fixed in IE 4.01, so we
      //  only do the 100% calculation specifically for IE4.
      simple_toolbar_item & item = m_itema[i];
      int32_t cySep = item.m_iImage;
      //      ASSERT(gen_ComCtlVersion != -1);
      /*      if (!(GetStyle() & TBSTYLE_FLAT) && gen_ComCtlVersion != VERSION_IE4)
      cySep = cySep * 2 / 3;*/
      if (item.m_spdib.is_set())
      {
         buttonx =  item.m_spdib->m_size.cx
            + max(ITEMCX, max(ITEMHOVERCX, ITEMPRESSCX))
            - min(ITEMCX, min(ITEMHOVERCX, ITEMPRESSCX))
            + ITEMPADLEFT + ITEMPADRIGHT;
         buttony = item.m_spdib->m_size.cy
            + max(ITEMCY, max(ITEMHOVERCY, ITEMPRESSCY))
            - min(ITEMCY, min(ITEMHOVERCY, ITEMPRESSCY))
            + ITEMPADTOP + ITEMPADBOTTOM;
      }
      else
      {
         buttonx = m_sizeImage.cx
            + max(ITEMCX, max(ITEMHOVERCX, ITEMPRESSCX))
            - min(ITEMCX, min(ITEMHOVERCX, ITEMPRESSCX))
            + ITEMPADLEFT + ITEMPADRIGHT;
         buttony = m_sizeImage.cy
            + max(ITEMCY, max(ITEMHOVERCY, ITEMPRESSCY))
            - min(ITEMCY, min(ITEMHOVERCY, ITEMPRESSCY))
            + ITEMPADTOP + ITEMPADBOTTOM;
      }


      if (m_itema[i].m_fsState & TBSTATE_HIDDEN)
         continue;

      //int32_t cx = m_sizeButton.cx;
      int32_t cx = buttonx;
      if (m_itema[i].m_fsStyle & TBSTYLE_SEP)
      {
         // a separator represents either a height or width
         if (m_itema[i].m_fsState & TBSTATE_WRAP)
            sizeResult.cy = max(cur.y + m_sizeButton.cy + cySep, sizeResult.cy);
         else
            sizeResult.cx = max(cur.x + m_itema[i].m_iImage, sizeResult.cx);
      }
      else
      {
         // check for dropdown style, but only if the buttons are being drawn
         /*         if ((m_itema[i].m_fsStyle & TBSTYLE_DROPDOWN) &&
         (dwExtendedStyle & TBSTYLE_EX_DRAWDDARROWS))
         {
         // add size of drop down
         ASSERT(gen_DropDownWidth != -1);
         cx += gen_DropDownWidth;
         }*/
         sizeResult.cx = max(cur.x + cx, sizeResult.cx);
         //sizeResult.cy = max(cur.y + m_sizeButton.cy, sizeResult.cy);
         sizeResult.cy = max(cur.y + buttony, sizeResult.cy);
      }

      if (m_itema[i].m_fsStyle & TBSTYLE_SEP)
         cur.x += m_itema[i].m_iImage;
      else
         cur.x += cx - CX_OVERLAP;

      if (m_itema[i].m_fsState & TBSTATE_WRAP)
      {
         cur.x = 0;
         //         cur.y += m_sizeButton.cy;
         cur.y += buttony;
         if (m_itema[i].m_fsStyle & TBSTYLE_SEP)
            cur.y += cySep;
      }
   }
#else
      throw todo(get_app());
#endif
   return sizeResult;
}
/*bool simple_toolbar::CalcSize(size & size, bool bHorz)
{

  _001Layout();
rect rectItem;
rect rectSize(0, 0, 0, 0);
size.cx = 0;
size.cy = 0;
for(int32_t i = 0; i < _001GetItemCount(); i++)
{
_001GetItemRect(i, rectItem);
if(bHorz)
{
size.cx += rectItem.width();
size.cy = max(size.cy, rectItem.height());
}
else
{
size.cx = max(size.cx, rectItem.width());
size.cy += rectItem.height();
}
}
return true;
}*/

int32_t simple_toolbar::_001GetItemCount()
{
   return (int32_t) m_itema.get_size();
}


simple_toolbar_item::simple_toolbar_item()
{


   m_iIndex                      = -1;
   m_iImage                      = -1;
   m_fsState                     = 0;
   m_fsStyle                     = 0;
   m_bEnableIfHasCommandHandler  = true;


}


bool simple_toolbar::_001GetItem(int32_t iItem, simple_toolbar_item *pitem)
{
   if(iItem >= 0
      && iItem < m_itema.get_size())
   {
      *pitem = m_itema[iItem];
      return true;
   }
   else
   {
      return false;
   }
}

bool simple_toolbar::_001SetItem(int32_t iItem, simple_toolbar_item *pitem)
{
   if(iItem >= 0
      && iItem < m_itema.get_size())
   {
      m_itema[iItem] = *pitem;
      return true;
   }
   else
   {
      return false;
   }

}


void simple_toolbar::_001DrawItem(::draw2d::graphics * pdc, int32_t iItem)
{
   rect rectItem;
   rect rectImage;

   pdc->SelectObject(System.visual().font_central().GetMenuFont());

#if defined(WINDOWSEX) || defined(LINUX) || defined(METROWIN) || defined(APPLEOS) || defined(SOLARIS)

   simple_toolbar_item & item = m_itema[iItem];


   UINT nStyle = GetButtonStyle(iItem);

   bool bHover = iItem == _001GetHoverItem();

   BaseMenuCentral * pmenucentral = BaseMenuCentral::GetMenuCentral(get_app());

   UINT uiImage = pmenucentral->CommandToImage(item.m_id);

   EElement eelement = ElementItem;
   EElement eelementImage = ElementImage;
   EElement eelementText = ElementText;
   if((nStyle & TBBS_SEPARATOR) == 0)
   {
      if((nStyle & TBBS_DISABLED) == 0)
      {
         // item is enabled
         if(m_iButtonPressItem >= 0)
         {
            if(iItem == m_iButtonPressItem)
            {
               if(bHover)
               {
                  eelement       = ElementItemPress;
                  eelementImage  = ElementImagePress;
                  eelementText   = ElementTextPress;
               }
               else
               {
                  eelement       = ElementItemHover;
                  eelementImage  = ElementImageHover;
                  eelementText   = ElementTextHover;
               }
            }
         }
         else if(bHover)
         {
            eelement       = ElementItemHover;
            eelementImage  = ElementImageHover;
            eelementText   = ElementTextHover;
         }
      }
      else
      {
         // item is disabled
         eelement       = ElementItem;
         eelementImage  = ElementImage;
         eelementText   = ElementText;
      }
   }
   else
   {
      eelement       = ElementItem;
      eelementImage  = ElementImage;
      eelementText   = ElementText;
   }


   _001GetItemRect(iItem, rectItem, eelement);
   _001GetItemRect(iItem, rectImage, eelementImage);

   if((nStyle & TBBS_SEPARATOR) != 0)
   {
      rect rectSeparator;
      rectSeparator.left = (rectImage.left + rectImage.right) / 2 - 1;
      rectSeparator.right = rectSeparator.left + 2;
      rectSeparator.top = rectImage.top;
      rectSeparator.bottom = rectImage.bottom;
      pdc->Draw3dRect(rectSeparator, ARGB(255, 92, 92, 92), ARGB(255, 255, 255, 255));
   }
   else
   {
      if(eelement == ElementItemHover)
      {
         if((nStyle & TBBS_CHECKED) != 0)
         {
            _001GetItemRect(iItem, rectItem, ElementItem);
            _001GetItemRect(iItem, rectImage, ElementImage);
            if((m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {
               System.visual().imaging().color_blend(
                  pdc,
                  rectItem.left,
                  rectItem.top,
                  rectItem.width(),
                  rectItem.height(),
                  RGB(255, 255, 250), 208);

               pdc->Draw3dRect(rectItem,
                  ARGB(255, 127, 127, 127),
                  ARGB(255, 255, 255, 255));
            }
            if(uiImage != 0xffffffffu)
            {
               if((nStyle & TBBS_DISABLED) == 0)
               {
                  // button is enabled
                  pmenucentral->MenuV033GetImageListBlend()->draw(
                     pdc, uiImage, rectImage.top_left(), 0);
               }
               else
               {
                  // button is disabled
                  pmenucentral->MenuV033GetImageListHueLight()->draw(
                     pdc, uiImage, rectImage.top_left(), 0);
               }
            }
         }
         else
         {
            rect rectShadow;
            _001GetItemRect(iItem, rectShadow, ElementItem);
            if((m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
            {

               ::draw2d::pen_sp penShadow(pdc, 1, ARGB(255, 127, 127, 127));
               ::draw2d::brush_sp brushShadow(allocer(), ARGB(255, 127, 127, 127));
               ::draw2d::pen * ppenOld = pdc->SelectObject(penShadow);
               ::draw2d::brush * pbrushOld = pdc->SelectObject(brushShadow);
               pdc->Rectangle(rectShadow);

               ::draw2d::pen_sp pen(pdc, 1, ARGB(255, 92, 92, 92));
               ::draw2d::brush_sp brush(allocer(), ARGB(255, 255, 255, 255));
               pdc->SelectObject(pen);
               pdc->SelectObject(brush);
               pdc->Rectangle(rectItem);
               pdc->SelectObject(ppenOld);
               pdc->SelectObject(pbrushOld);
            }

            if(item.m_spdib.is_set())
            {
               rect rect;
               _001GetItemRect(iItem, rect, ElementImageHover);
               System.visual().imaging().color_blend(pdc, rect.top_left(), rect.size(), item.m_spdib->get_graphics(), null_point(), 0.84);
            }
            else if(uiImage != 0xffffffffu)
            {
               rect rect;
               _001GetItemRect(iItem, rect, ElementImage);
               pmenucentral->MenuV033GetImageListHue()->draw(
                  pdc, uiImage, rect.top_left(), 0);

               pmenucentral->MenuV033GetImageList()->draw(
                  pdc, uiImage, rectImage.top_left(), 0);
            }
         }
      }
      else if(eelement == ElementItemPress)
      {

         if((m_dwCtrlStyle & TBSTYLE_FLAT) == TBSTYLE_FLAT)
         {

            ::draw2d::pen_sp pen(pdc, 1, ARGB(255, 92, 92, 92));
            ::draw2d::brush_sp brush(allocer(), ARGB(255, 255, 255, 255));
            ::draw2d::pen * ppenOld = pdc->SelectObject(pen);
            ::draw2d::brush * pbrushOld = pdc->SelectObject(brush);
            pdc->Rectangle(rectItem);
            pdc->SelectObject(ppenOld);
            pdc->SelectObject(pbrushOld);

         }

         //      rect rect;
         //    _001GetItemRect(iItem, rect, ElementImage);
         //  m_pimagelistHue->draw(pdc, uiImage, rect.top_left(), 0);
         if(item.m_spdib.is_set())
         {
            rect rect;
            _001GetItemRect(iItem, rect, ElementImagePress);
            System.visual().imaging().color_blend(pdc, rect.top_left(), rect.size(), item.m_spdib->get_graphics(), null_point(), 1.0);
         }
         else if(uiImage != 0xffffffff)
         {
            pmenucentral->MenuV033GetImageList()->draw(pdc, uiImage, rectImage.top_left(), 0);
         }

      }
      else
      {
         if((nStyle & TBBS_CHECKED) != 0)
         {
            pdc->Draw3dRect(rectItem, ARGB(255, 127, 127, 127), ARGB(255, 255, 255, 255));
         }

         if(item.m_spdib.is_set())
         {
            rect rect;
            _001GetItemRect(iItem, rect, ElementImage);
            System.visual().imaging().color_blend(pdc, rect.top_left(), rect.size(), item.m_spdib->get_graphics(), null_point(), 0.23);
         }
         else if(uiImage != 0xffffffff)
         {
            if((nStyle & TBBS_DISABLED) == 0)
            {
               // button is enabled
               pmenucentral->MenuV033GetImageListBlend()->draw(pdc, uiImage, rectImage.top_left(), 0);
            }
            else
            {
               // button is disabled
               pmenucentral->MenuV033GetImageListHueLight()->draw(pdc, uiImage, rectImage.top_left(), 0);
            }
         }
      }
   }

   if(item.m_str.has_char())
   {
      rect rectText;
         ::draw2d::brush_sp brushText(allocer(), ARGB(255, 0, 0, 0));
         
         pdc->SelectObject(brushText);

      if(_001GetItemRect(iItem, rectText, ElementText) && rectText.right > 0)
      {
         pdc->_DrawText(item.m_str, item.m_str.get_length(), rectText, DT_BOTTOM | DT_LEFT);
      }
   }

#else

   throw todo(get_app());

#endif

}

/*
bool simple_toolbar::LoadToolBar(const char * lpszResourceName)
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

tool_bar_data* m_itema = (tool_bar_data*)LockResource(hGlobal);
if (m_itema == NULL)
return FALSE;
ASSERT(m_itema->wVersion == 1);

UINT* pItems = new UINT[m_itema->wItemCount];
for (int32_t i = 0; i < m_itema->wItemCount; i++)
pItems[i] = m_itema->items()[i];
bool bResult = SetButtons(pItems, m_itema->wItemCount);
delete[] pItems;


if (bResult)
{

// set new sizes of the buttons
size sizeImage(m_itema->wWidth, m_itema->wHeight);
size sizeButton(m_itema->wWidth + 7, m_itema->wHeight + 7);
SetSizes(sizeButton, sizeImage);

// load bitmap now that sizes are known by the toolbar control
bResult = LoadBitmap(lpszResourceName);

_001Layout();
}

UnlockResource(hGlobal);
FreeResource(hGlobal);


return bResult;
}
*/

bool simple_toolbar::LoadXmlToolBar(const char * lpszXml)
{

   m_itema.remove_all();

   xml::document doc(get_app());

   if(!doc.load(lpszXml))
      return FALSE;

   xml::node::array childs(get_app());

   childs = doc.get_root()->children();

   //   sp(::base::application) papp = (get_app());

#if defined(WINDOWSEX) || defined(LINUX) || defined(METROWIN) || defined(APPLEOS)

   simple_toolbar_item item;

   for(int32_t i = 0; i < childs.get_size(); i++)
   {
      sp(::xml::node) pchild = childs(i);
      if(pchild->get_name() == "button")
      {
         xml::attr * pattr = pchild->find_attr("id");
         item.m_id = pattr->get_string();
         item.m_str = pchild->get_value();
         if(pchild->attr("image").get_string().has_char())
         {
            item.m_spdib.create(allocer());
            item.m_spdib.load_from_file(pchild->attr("image"));
         }
         if(pchild->attr("enable_if_has_command_handler").get_string().has_char())
         {
            item.m_bEnableIfHasCommandHandler = pchild->attr("enable_if_has_command_handler").get_string().CompareNoCase("true") == 0;
         }
         item.m_fsStyle &= ~TBBS_SEPARATOR;
         m_itema.add(new simple_toolbar_item(item));
      }
      else if(pchild->get_name() == "separator")
      {
         item.m_id = "separator";
         item.m_str = "";
         item.m_fsStyle |= TBBS_SEPARATOR;
         m_itema.add(new simple_toolbar_item(item));
      }
   }

#else

   throw todo(get_app());

#endif

   return TRUE;

}

bool simple_toolbar::_001GetItemRect(int32_t iItem, LPRECT lprect)
{
   // handle any delayed layout
   if (m_bDelayedButtonLayout)
      layout();

   if(iItem >= 0
      && iItem < m_itema.get_size())
   {
      *lprect = m_itema[iItem].m_rect;
      return true;
   }
   else
   {
      return false;
   }
}

bool simple_toolbar::_001GetItemRect(int32_t iItem, LPRECT lprect, EElement eelement)
{
   if(iItem < 0 ||
      iItem >= m_itema.get_size())
      return false;

   rect rect;

#if defined(WINDOWSEX) || defined(LINUX) || defined(METROWIN) || defined(APPLEOS) || defined(SOLARIS)

   simple_toolbar_item & item = m_itema[iItem];

   BaseMenuCentral * pmenucentral = BaseMenuCentral::GetMenuCentral(get_app());

   UINT uiImage = pmenucentral->CommandToImage(item.m_id);

   if((item.m_fsStyle & TBSTYLE_SEP) != 0)
   {
      rect.left   = item.m_rect.left + ITEMCX;
      rect.top    = item.m_rect.top + ITEMCY + ITEMPADTOP;
      rect.right  = rect.left + item.m_iImage;
      rect.bottom = rect.top +  m_sizeImage.cy;
   }
   else
   {
      switch(eelement)
      {
      case ElementItem:
      case ElementItemHover:
      case ElementItemPress:
         rect.left   = item.m_rect.left;
         rect.top    = item.m_rect.top;
         rect.right  = rect.left + item.m_rect.width();
         if(item.m_spdib.is_set())
         {
            rect.bottom = rect.top + item.m_spdib->m_size.cy + ITEMPADTOP + ITEMPADBOTTOM;
         }
         else if(uiImage != 0xffffffff)
         {
            rect.bottom = rect.top + m_sizeImage.cy + ITEMPADTOP + ITEMPADBOTTOM;
         }
         else
         {
            rect.bottom = rect.top + m_sizeImage.cy + ITEMPADTOP + ITEMPADBOTTOM;
         }
         break;
      case ElementImage:
      case ElementImageHover:
      case ElementImagePress:
         if(item.m_spdib.is_set())
         {
            rect.left   = item.m_rect.left + ITEMPADLEFT;
            rect.top    = item.m_rect.top + ITEMPADTOP;
            rect.right  = rect.left + item.m_spdib->m_size.cx;
            rect.bottom = rect.top + item.m_spdib->m_size.cy;
            break;
         }
         if(uiImage == 0xffffffff)
         {
            rect.left   = 0;
            rect.top    = 0;
            rect.right  = 0;
            rect.bottom = 0;
            break;
         }
         rect.left   = item.m_rect.left + ITEMPADLEFT;
         rect.top    = item.m_rect.top + ITEMPADTOP;
         rect.right  = rect.left + m_sizeImage.cx;
         rect.bottom = rect.top + m_sizeImage.cy;
         break;
      case ElementText:
      case ElementTextHover:
      case ElementTextPress:
         {
            rect.left   = item.m_rect.left;
            if(item.m_spdib.is_set())
            {
               rect.left   += ITEMPADLEFT + item.m_spdib->m_size.cx;
            }
            else if(uiImage != 0xffffffff)
            {
               rect.left   += ITEMPADLEFT + m_sizeImage.cx;
            }
            rect.left  += ITEMPADLEFT;
            rect.top    = item.m_rect.top + ITEMPADTOP;
            rect.right  = item.m_rect.left + item.m_rect.width();
            rect.bottom = item.m_rect.top + m_sizeImage.cy;
         }
      }
      switch(eelement)
      {
      case ElementItem:
      case ElementImage:
      case ElementText:
         rect.offset(ITEMCX, ITEMCY);
         break;
      case ElementItemHover:
      case ElementImageHover:
      case ElementTextHover:
         rect.offset(ITEMHOVERCX, ITEMHOVERCY);
         break;
      case ElementItemPress:
      case ElementImagePress:
      case ElementTextPress:
         rect.offset(ITEMPRESSCX, ITEMPRESSCY);
         break;
      default:
         break;
      }
   }
#else
   throw todo(get_app());
#endif
   *lprect = rect;
   return true;
}


/*bool simple_toolbar::SetButtons(const UINT* lpIDArray, int32_t nIDCount)
{
ASSERT_VALID(this);
ASSERT(nIDCount >= 1);  // must be at least one of them
ASSERT(lpIDArray == NULL ||
__is_valid_address(lpIDArray, sizeof(UINT) * nIDCount, FALSE));

// delete all existing buttons
int32_t nCount = (int32_t)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
while (nCount--)
VERIFY(DefWindowProc(TB_DELETEBUTTON, 0, 0));

TBBUTTON button;
memset(&button, 0, sizeof(TBBUTTON));
button.iString = -1;
if (lpIDArray != NULL)
{
// add new buttons to the common control
int32_t iImage = 0;
for (int32_t i = 0; i < nIDCount; i++)
{
button.fsState = TBSTATE_ENABLED;
if ((button.m_id = *lpIDArray++) == 0)
{
// separator
button.m_fsStyle = TBSTYLE_SEP;
// width of separator includes 8 pixel overlap
//            ASSERT(gen_ComCtlVersion != -1);
if (GetStyle() & TBSTYLE_FLAT)
button.iBitmap = 6;
else
button.iBitmap = 8;
}
else
{
// a command button with image
button.m_fsStyle = TBSTYLE_BUTTON;
button.iBitmap = iImage++;
}
if(!AddButton(&button))
return false;
}
}
else
{
// add 'blank' buttons
button.fsState = TBSTATE_ENABLED;
for (int32_t i = 0; i < nIDCount; i++)
{
ASSERT(button.m_fsStyle == TBSTYLE_BUTTON);
if (!DefWindowProc(TB_ADDBUTTONS, 1, (LPARAM)&button))
return FALSE;
}
}
m_nCount = (int32_t)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
m_bDelayedButtonLayout = true;

return TRUE;
}*/


void simple_toolbar::SetSizes(SIZE sizeButton, SIZE sizeImage)
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

   //   if (::IsWindow(get_handle()))
   if(false)
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

/*
bool simple_toolbar::LoadBitmap(const char * lpszResourceName)
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
::draw2d::memory_graphics pdc(this);;
hbmImageWell = imaging::LoadSysColorBitmap(pdc, hInstImageWell, hRsrcImageWell);


// tell common control toolbar about the new bitmap
//   if (!AddReplaceBitmap(hbmImageWell))
//      return FALSE;

// remember the resource handles so the bitmap can be recolored if necessary
m_hInstImageWell = hInstImageWell;
m_hRsrcImageWell = hRsrcImageWell;

_001DiscardImageList();

   m_pimagelist = new image_list();
m_bInternalImageList = true;

m_pimagelist->create(
(char *) lpszResourceName,
m_sizeImage.cx,
1,
RGB(192, 192, 192));

_001OnImageListAttrib();*/

/*
return TRUE;
}
*/

void simple_toolbar::layout()
{
   //ASSERT(m_bDelayedButtonLayout);

   synch_lock ml(&user_mutex());

   m_bDelayedButtonLayout = false;

   bool bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
   //   if(m_bSimpleLayout)
   //      CalcSimpleLayout();
   if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
      ((simple_toolbar*)this)->CalcDynamicLayout(0, LM_HORZ | LM_MRUWIDTH | LM_COMMIT);
   else if (bHorz)
      ((simple_toolbar*)this)->CalcDynamicLayout(0, LM_HORZ | LM_HORZDOCK | LM_COMMIT);
   else
      ((simple_toolbar*)this)->CalcDynamicLayout(0, LM_VERTDOCK | LM_COMMIT);

   size size;
   int32_t ix = 0;
   //   int32_t intrax = max(ITEMCX, max(ITEMHOVERCX, ITEMPRESSCX))
   //            - min(ITEMCX, min(ITEMHOVERCX, ITEMPRESSCX))
   //          + max(ITEMPADLEFT, ITEMPADRIGHT);
   int32_t buttonx1, buttonx2, buttony;
   buttonx1 = m_sizeImage.cx
      + max(ITEMCX, max(ITEMHOVERCX, ITEMPRESSCX))
      - min(ITEMCX, min(ITEMHOVERCX, ITEMPRESSCX))
      + ITEMPADLEFT + ITEMPADRIGHT;
   buttonx2 = max(ITEMCX, max(ITEMHOVERCX, ITEMPRESSCX))
      - min(ITEMCX, min(ITEMHOVERCX, ITEMPRESSCX))
      + ITEMPADLEFT + ITEMPADRIGHT;
   buttony = m_sizeImage.cy
      + max(ITEMCY, max(ITEMHOVERCY, ITEMPRESSCY))
      - min(ITEMCY, min(ITEMHOVERCY, ITEMPRESSCY))
      + ITEMPADTOP + ITEMPADBOTTOM;

   rect  rectClient;
   GetClientRect(rectClient);
   class size sizeText;
   ::draw2d::graphics_sp spgraphics(allocer());
   spgraphics->CreateCompatibleDC(NULL);
   spgraphics->SelectObject(System.visual().font_central().GetMenuFont());
   for(int32_t iItem = 0; iItem < m_itema.get_size(); iItem++)
   {
      simple_toolbar_item & item = m_itema[iItem];
      item.m_rect.left = ix;
      if(item.m_str.is_empty())
      {
         sizeText.cx = 0;
      }
      else
      {
         visual::graphics_extension(get_app()).GetTextExtent(
            spgraphics,
            item.m_str,
            sizeText);
      }

#if defined(WINDOWSEX) || defined(LINUX) || defined(METROWIN) || defined(APPLEOS)

      BaseMenuCentral * pmenucentral = BaseMenuCentral::GetMenuCentral(get_app());

      int32_t iy = 0;

      UINT uiImage = pmenucentral->CommandToImage(item.m_id);

      int32_t cx, cy;

      if((item.m_fsState & TBSTATE_WRAP) != 0)
      {
         if((item.m_fsStyle & TBSTYLE_SEP) != 0)
         {
            cx = buttonx1;
            cy = item.m_iImage;
         }
         else if(item.m_spdib.is_set())
         {
            cx = buttonx2 + sizeText.cx + item.m_spdib->m_size.cx;
            cy = max(buttony, item.m_spdib->m_size.cy);
         }
         else if(item.m_iImage >= 0)
         {
            cx = buttonx1 + sizeText.cx;
            cy = buttony;
         }
         else
         {
            cx = buttonx2 + sizeText.cx;
            cy = buttony;
         }
      }
      else
      {
         if((item.m_fsStyle & TBSTYLE_SEP) != 0)
         {
            cx = item.m_iImage;
            cy = buttony;
         }
         else if(item.m_spdib.is_set())
         {
            cx = buttonx2 + sizeText.cx + item.m_spdib->m_size.cx;
            cy = max(buttony, item.m_spdib->m_size.cy);
         }
         else if(uiImage != 0xffffffff)
         {
            cx = buttonx1 + sizeText.cx;
            cy = buttony;
         }
         else
         {
            cx = buttonx2 + sizeText.cx;
            cy = buttony;
         }
      }
      item.m_rect.right = ix + cx;
      item.m_rect.top = iy;
      item.m_rect.bottom = iy + cy;
      if((item.m_fsState & TBSTATE_WRAP) != 0 || !bHorz)
      {
         iy += cy;
      }
      else
      {
         ix += cx;
      }
#else
      throw todo(get_app());
#endif
   }
   if(m_itema.get_size() > 0)
   {
      point ptOffset;
      if((m_dwCtrlStyle & TBSTYLE_ALIGN_LEFT) == TBSTYLE_ALIGN_LEFT)
      {
         ptOffset.x = 0;
      }
      else if((m_dwCtrlStyle & TBSTYLE_ALIGN_RIGHT) == TBSTYLE_ALIGN_RIGHT)
      {
         ptOffset.x = rectClient.width() - (m_itema.last_element()->m_rect.right - m_itema[0].m_rect.left);
      }
      else if((m_dwCtrlStyle & TBSTYLE_ALIGN_CENTER) == TBSTYLE_ALIGN_CENTER)
      {
         ptOffset.x = (rectClient.width() - (m_itema.last_element()->m_rect.right - m_itema[0].m_rect.left)) / 2;
      }
      else
      {
         ptOffset.x = 0;
      }
      if((m_dwCtrlStyle & TBSTYLE_ALIGN_TOP) == TBSTYLE_ALIGN_TOP)
      {
         ptOffset.y = 0;
      }
      else if((m_dwCtrlStyle & TBSTYLE_ALIGN_BOTTOM) == TBSTYLE_ALIGN_BOTTOM)
      {
         ptOffset.y = rectClient.height() - (m_itema.last_element()->m_rect.bottom - m_itema[0].m_rect.top);
      }
      else if((m_dwCtrlStyle & TBSTYLE_ALIGN_VCENTER) == TBSTYLE_ALIGN_VCENTER)
      {
         ptOffset.y = (rectClient.height() - (m_itema.last_element()->m_rect.bottom - m_itema[0].m_rect.top)) / 2;
      }
      else
      {
         ptOffset.y = 0;
      }
      for(int32_t iItem = 0; iItem < m_itema.get_size(); iItem++)
      {
         simple_toolbar_item & item = m_itema[iItem];
         item.m_rect.offset(ptOffset);
      }
   }

}

void simple_toolbar::_001OnMouseMove(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
   ScreenToClient(&pt);
   if(m_bDockTrack)
   {
      pobj->previous();
   }
   else
   {
      _001Hover(pt);
      if(m_iHover >= 0)
      {
         pmouse->m_bRet = true;
         pmouse->set_lresult(1);
      }
      pobj->previous();
   }
}

void simple_toolbar::_001OnLButtonDown(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
   ScreenToClient(&pt);
   m_iButtonPressItem = _001HitTest(pt);

   if(m_iButtonPressItem >= 0)
   {
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }

   _001RedrawWindow();

   pobj->previous();
}

void simple_toolbar::_001OnLButtonUp(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
   ScreenToClient(&pt);
   if(m_bDockTrack)
   {
      pobj->previous();
   }
   else
   {
      int32_t iItem = _001HitTest(pt);
      if(iItem >= 0 && iItem == m_iButtonPressItem)
      {
         _001OnClick(iItem);
         pmouse->m_bRet = true;
         pmouse->set_lresult(1);
      }
      sp(::user::frame_window) pTarget = (GetOwner().m_p);
      if (pTarget == NULL)
         pTarget = GetParentFrame();
      if (pTarget != NULL)
         pTarget->SendMessageToDescendants(WM_IDLEUPDATECMDUI);
      m_iButtonPressItem = -1;
      _001RedrawWindow();
      pobj->previous();
   }
}


int32_t simple_toolbar::_001HitTest(point pt)
{
   for(int32_t iItem = 0; iItem < m_itema.get_size(); iItem++)
   {
      if(m_itema[iItem].m_rect.contains(pt))
         return iItem;
   }
   if(System.get_capture_uie() == this)
      return -1;
   rect rectWindow;
   GetWindowRect(rectWindow);
   ScreenToClient(rectWindow);
   if(rectWindow.contains(pt))
      return -1;
   else
      return 0x80000000;
}


void simple_toolbar::_001Hover(point pt, bool bRedraw)
{
   int32_t iHover = _001HitTest(pt);
   if(m_iHover != iHover)
   {
      track_mouse_leave();
      m_iHover = iHover;
      OnUpdateHover();
      //      if(m_iHover < -1)
      //    {
      //     KillTimer(TIMER_HOVER);
      //      }
      //    else
      //  {
      //   SetTimer(TIMER_HOVER, 50, NULL);
      //}

      if(bRedraw)
      {
         _001RedrawWindow();
      }
   }
}

void simple_toolbar::_001Hover(bool bRedraw)
{
   point pt;
   GetCursorPos(&pt);
   ScreenToClient(&pt);
   _001Hover(pt, bRedraw);
}

void simple_toolbar::_001OnTimer(signal_details * pobj)
{
   SCAST_PTR(::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent == TIMER_HOVER)
      {
         _001Hover();
      }

      // trans ::user::control_bar::OnTimer(ptimer->m_nIDEvent);
}

void simple_toolbar::_001OnClick(index iItem)
{
   sp(::user::interaction) pwnd = GetOwner();
   pwnd->_001SendCommand(m_itema[iItem].m_id);
}

void simple_toolbar::_001DiscardImageList()
{
   /*   if(m_bInternalImageList)
   {
   if(m_pimagelist != NULL)
   {
   delete m_pimagelist;
   m_pimagelist = NULL;
   }
   }
   else
   {
   m_pimagelist = NULL;
   }*/
}

void simple_toolbar::_001SetImageList(sp(image_list) pimagelist)
{
   UNREFERENCED_PARAMETER(pimagelist);
   /*   m_pimagelist = pimagelist;
   m_bInternalImageList = false;
   _001OnImageListAttrib();*/
}


void simple_toolbar::_001OnImageListAttrib()
{
   /*
   if(m_pimagelistHue == NULL)
   {
   m_pimagelistHue = new image_list();
   }
   ::draw2d::graphics_sp spgraphics(allocer());
   spgraphics->CreateDC("DISPLAY", NULL, NULL, NULL);
   System.visual().imaging().CreateHueImageList(
   &spgraphics,
   m_pimagelistHue,
   m_pimagelist,
   RGB(192, 192, 180),
   0.50);

   if(m_pimagelistBlend == NULL)
   {
   m_pimagelistBlend = new image_list();
   }
   System.visual().imaging().Createcolor_blend_ImageList(
   m_pimagelistBlend,
   m_pimagelist,
   RGB(255, 255, 240),
   64);

   if(m_pimagelistHueLight == NULL)
   {
   m_pimagelistHueLight = new image_list();
   }
   System.visual().imaging().CreateHueImageList(
   &spgraphics,
   m_pimagelistHueLight,
   m_pimagelist,
   RGB(220, 220, 215),
   0.50);
   */
}


/////////////////////////////////////////////////////////////////////////////
// simple_toolbar idle update through SimpleToolCmdUI class

SimpleToolCmdUI::SimpleToolCmdUI(sp(::base::application) papp) :
element(papp),
   cmd_ui(papp)
{
}
void SimpleToolCmdUI::Enable(bool bOn, ::action::context actioncontext)
{
   m_bEnableChanged = TRUE;
   simple_toolbar* pToolBar = dynamic_cast < simple_toolbar * > (m_pOther.m_p);
   ASSERT(pToolBar != NULL);
   //   ASSERT_KINDOF(simple_toolbar, pToolBar);
   ASSERT(m_iIndex < m_iCount);
#if defined(WINDOWSEX) || defined(LINUX) || defined(METROWIN) || defined(APPLEOS)
   UINT nNewStyle = pToolBar->GetButtonStyle((int32_t) m_iIndex) & ~TBBS_DISABLED;
   if (!bOn)
   {
      nNewStyle |= TBBS_DISABLED;
      // WINBUG: If a button is currently pressed and then is disabled
      // COMCTL32.DLL does not unpress the button, even after the mouse
      // button goes up!  We work around this bug by forcing TBBS_PRESSED
      // off when a button is disabled.
      nNewStyle &= ~TBBS_PRESSED;
   }
   ASSERT(!(nNewStyle & TBBS_SEPARATOR));
   pToolBar->SetButtonStyle((int32_t) m_iIndex, nNewStyle);
#else
   throw todo(get_app());
#endif
}

void SimpleToolCmdUI::_001SetCheck(check::e_check echeck, ::action::context actioncontext)
{
   ASSERT(echeck == check::checked
      || echeck == check::unchecked
      || echeck == check::tristate); // 0=>off, 1=>on, 2=>indeterminate
   simple_toolbar* pToolBar = dynamic_cast < simple_toolbar * > (m_pOther.m_p);
   ASSERT(pToolBar != NULL);
   ASSERT_KINDOF(simple_toolbar, pToolBar);
   ASSERT(m_iIndex < m_iCount);

#if defined(WINDOWSEX) || defined(LINUX) || defined(METROWIN) || defined(APPLEOS)
   UINT nNewStyle = pToolBar->GetButtonStyle((int32_t) m_iIndex) &
      ~(TBBS_CHECKED | TBBS_INDETERMINATE);
   if(echeck == check::checked)
      nNewStyle |= TBBS_CHECKED;
   else if(echeck == check::tristate)
      nNewStyle |= TBBS_INDETERMINATE;
   ASSERT(!(nNewStyle & TBBS_SEPARATOR));
   pToolBar->SetButtonStyle((int32_t) m_iIndex, nNewStyle | TBBS_CHECKBOX);
#else
   throw todo(get_app());
#endif
}

void SimpleToolCmdUI::SetText(const char *, ::action::context)
{
   // ignore it
}

int32_t simple_toolbar::GetItemStyle(int32_t iItem)
{
   return m_itema[iItem].m_fsStyle;
}

bool simple_toolbar::SetItemStyle(int32_t iItem, BYTE bStyle)
{
   UNREFERENCED_PARAMETER(iItem);
   UNREFERENCED_PARAMETER(bStyle);
   return false;
}

UINT simple_toolbar::GetButtonStyle(int32_t nIndex)
{
   ASSERT_VALID(this);
   ASSERT(IsWindow());

   simple_toolbar_item & item = m_itema[nIndex];
   return MAKELONG(item.m_fsStyle, item.m_fsState);
}

void simple_toolbar::SetButtonStyle(int32_t nIndex, UINT nStyle)
{
   ASSERT_VALID(this);
   ASSERT(IsWindow());

   simple_toolbar_item & item = m_itema[nIndex];
   if (item.m_fsStyle != (BYTE)LOWORD(nStyle) || item.m_fsState != (BYTE)HIWORD(nStyle))
   {
      item.m_fsStyle = (BYTE)LOWORD(nStyle);
      item.m_fsState = (BYTE)HIWORD(nStyle);
      m_bDelayedButtonLayout = TRUE;
   }

}


void simple_toolbar::_001OnNcCalcSize(signal_details * pobj)
{
#if defined(WINDOWSEX) //|| defined(LINUX)
   SCAST_PTR(::message::nc_calc_size, pnccalcsize, pobj)
      // calculate border space (will add to top/bottom, subtract from right/bottom)
   class rect rect;
   rect.null();
   bool bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
   ::user::control_bar::CalcInsideRect(rect, bHorz);

   // adjust non-client area for border space
   pnccalcsize->m_pparams->rgrc[0].left += rect.left;
   pnccalcsize->m_pparams->rgrc[0].top += rect.top;
   pnccalcsize->m_pparams->rgrc[0].right += rect.right;
   pnccalcsize->m_pparams->rgrc[0].bottom += rect.bottom;
#else
   throw todo(get_app());
#endif
}


void simple_toolbar::_001OnNcHitTest(signal_details * pobj)
{
   SCAST_PTR(::message::nchittest, pnchittest, pobj)
      pnchittest->set_lresult(HTCLIENT);
}


#define CX_OVERLAP  0

int32_t simple_toolbar::WrapToolBar(int32_t nCount, int32_t nWidth)
{
   int32_t nResult = 0;
#if defined(WINDOWSEX) || defined(LINUX) || defined(METROWIN) || defined(APPLEOS)
   ASSERT(nCount > 0);
   ::draw2d::memory_graphics pdc(allocer());
    int32_t x = 0;
   string str;
   for (int32_t i = 0; i < nCount; i++)
   {
      m_itema[i].m_fsState &= ~TBSTATE_WRAP;

      if (m_itema[i].m_fsState & TBSTATE_HIDDEN)
         continue;
      GetButtonText(i, str);
      int32_t dx, dxNext;
      if (m_itema[i].m_fsStyle & TBSTYLE_SEP)
      {
         dx = m_itema[i].m_iImage;
         dxNext = dx;
      }
      else if (!str.is_empty())
      {
         dx = m_sizeButton.cx;
         //         string str;
         //         str = (const wchar_t *) m_itema[i].iString;
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
         for (int32_t j = i; j >= 0  &&  !(m_itema[j].m_fsState & TBSTATE_WRAP); j--)
         {
            // find last separator that isn't hidden
            // a separator that has a command ID is not
            // a separator, but a custom control.
            if ((m_itema[j].m_fsStyle & TBSTYLE_SEP) &&
               (m_itema[j].m_id == "separator") &&
               !(m_itema[j].m_fsState & TBSTATE_HIDDEN))
            {
               bFound = TRUE; i = j; x = 0;
               m_itema[j].m_fsState |= TBSTATE_WRAP;
               nResult++;
               break;
            }
         }
         if (!bFound)
         {
            for (int32_t j = i - 1; j >= 0 && !(m_itema[j].m_fsState & TBSTATE_WRAP); j--)
            {
               // Never wrap anything that is hidden,
               // or any custom controls
               if ((m_itema[j].m_fsState & TBSTATE_HIDDEN) ||
                  ((m_itema[j].m_fsStyle & TBSTYLE_SEP) &&
                  (m_itema[j].m_id != "separator")))
                  continue;

               bFound = TRUE; i = j; x = 0;
               m_itema[j].m_fsState |= TBSTATE_WRAP;
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
#else
   throw todo(get_app());
#endif
   return nResult + 1;
}

void  simple_toolbar::SizeToolBar(int32_t nCount, int32_t nLength, bool bVert)
{
   ASSERT(nCount > 0);

   if (!bVert)
   {
      int32_t nMin, nMax, nTarget, nCurrent, nMid;

      // Wrap ToolBar as specified
      nMax = nLength;
      nTarget = WrapToolBar(nCount, nMax);

      // Wrap ToolBar vertically
      nMin = 0;
      nCurrent = WrapToolBar(nCount, nMin);

      if (nCurrent != nTarget)
      {
         while (nMin < nMax)
         {
            nMid = (nMin + nMax) / 2;
            nCurrent = WrapToolBar(nCount, nMid);

            if (nCurrent == nTarget)
               nMax = nMid;
            else
            {
               if (nMin == nMid)
               {
                  WrapToolBar(nCount, nMax);
                  break;
               }
               nMin = nMid;
            }
         }
      }
      size size = CalcSize(nCount);
      WrapToolBar(nCount, size.cx);
   }
   else
   {
      size sizeMax, sizeMin, sizeMid;

      // Wrap ToolBar vertically
      WrapToolBar(nCount, 0);
      sizeMin = CalcSize(nCount);

      // Wrap ToolBar horizontally
      WrapToolBar(nCount, 32767);
      sizeMax = CalcSize(nCount);

      while (sizeMin.cx < sizeMax.cx)
      {
         sizeMid.cx = (sizeMin.cx + sizeMax.cx) / 2;
         WrapToolBar(nCount, sizeMid.cx);
         sizeMid = CalcSize(nCount);

         if (nLength < sizeMid.cy)
         {
            if (sizeMin == sizeMid)
            {
               WrapToolBar(nCount, sizeMax.cx);
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

struct ___CONTROLPOS
{
   int32_t nIndex;
   string strId;
   rect rectOldPos;
};


size simple_toolbar::CalcLayout(uint32_t dwMode, int32_t nLength)
{
   ASSERT_VALID(this);
   ASSERT(IsWindow());
   if (dwMode & LM_HORZDOCK)
      ASSERT(dwMode & LM_HORZ);

   int32_t nCount;
   //TBBUTTON* m_itema = NULL;
   size sizeResult(0,0);

   nCount = _001GetItemCount();


   if (nCount > 0)
   {
      if (!(m_dwStyle & CBRS_SIZE_FIXED))
      {
         bool bDynamic = (m_dwStyle & CBRS_SIZE_DYNAMIC) != 0;

         if (bDynamic && (dwMode & LM_MRUWIDTH))
            SizeToolBar(nCount, m_nMRUWidth);
         else if (bDynamic && (dwMode & LM_HORZDOCK))
            SizeToolBar(nCount, 32767);
         else if (bDynamic && (dwMode & LM_VERTDOCK))
            SizeToolBar(nCount, 0);
         else if (bDynamic && (nLength != -1))
         {
            class rect rect;
            rect.null();
            CalcInsideRect(rect, (dwMode & LM_HORZ) != 0);
            bool bVert = (dwMode & LM_LENGTHY) != 0;
            int32_t nLen = nLength + (bVert ? rect.height() : rect.width());

            SizeToolBar(nCount, nLen, bVert);
         }
         else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
            SizeToolBar(nCount, m_nMRUWidth);
         else
            SizeToolBar(nCount, (dwMode & LM_HORZ) ? 32767 : 0);
      }

      sizeResult = CalcSize(nCount);

#if defined(WINDOWSEX) || defined(LINUX) || defined(METROWIN) || defined(APPLEOS)
      if (dwMode & LM_COMMIT)
      {
         ___CONTROLPOS* pControl = NULL;
         int32_t nControlCount = 0;
         bool bIsDelayed = m_bDelayedButtonLayout;
         m_bDelayedButtonLayout = FALSE;

         int32_t i;
         for (i = 0; i < nCount; i++)
            if ((m_itema[i].m_fsStyle & TBSTYLE_SEP) && (m_itema[i].m_id != "separator"))
               nControlCount++;

         if (nControlCount > 0)
         {
            pControl = new ___CONTROLPOS[nControlCount];
            nControlCount = 0;

            for(int32_t i = 0; i < nCount; i++)
            {
               if ((m_itema[i].m_fsStyle & TBSTYLE_SEP) && (m_itema[i].m_id != "separator"))
               {
                  pControl[nControlCount].nIndex = i;
                  pControl[nControlCount].strId = m_itema[i].m_id;

                  rect rect;
                  _001GetItemRect(i, &rect);
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
            //            _SetButton(i, &m_itema[i]);
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
            //            button.m_id = i;
            //            GetToolBarCtrl().SetButtonInfo(i, &button);
         }
         //for (i = 0; i < nCount; i++)
         {
//            TBBUTTONINFOW buttona;
  //          memset(&buttona, 0, sizeof(buttona));
    //        buttona.cbSize = sizeof(buttona);
      //      buttona.dwMask =
        //       TBIF_COMMAND
          //     | TBIF_STYLE
            //   | TBIF_SIZE;
            //            UINT uiID = GetItemID(i);
            ///            GetToolBarCtrl().GetButtonInfo(uiID, &buttona);
            //         TRACE("BUTTON.m_id = %d\n", buttona.m_id  );
            //         TRACE("BUTTON.m_fsStyle = %d\n", buttona.m_fsStyle  );
            //         TRACE("BUTTON.cx = %d\n", buttona.cx );
         }

         if (nControlCount > 0)
         {
            for (int32_t i = 0; i < nControlCount; i++)
            {
               /* xxx sp(::user::interaction) pwindow = get_child_by_id(pControl[i].strId);
               if (pwindow != NULL)
               {
               rect rect;
               pwindow->GetWindowRect(&rect);
               point pt = rect.top_left() - pControl[i].rectOldPos.top_left();
               _001GetItemRect(pControl[i].nIndex, &rect);
               pt = rect.top_left() + pt;
               pwindow->SetWindowPos(0, pt.x, pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
               }*/
            }
            delete[] pControl;
         }
         m_bDelayedButtonLayout = bIsDelayed != 0;
      }
#else
      throw todo(get_app());
#endif
      //delete[] m_itema;
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

}


void simple_toolbar::GetButtonText(int32_t i, string &str)
{
   UNREFERENCED_PARAMETER(i);
   str.Empty();
}

/*size simple_toolbar::CalcSize(TBBUTTON* m_itema, int32_t nCount)
{
ASSERT(m_itema != NULL && nCount > 0);

point cur(0,0);
size sizeResult(0,0);

uint32_t dwExtendedStyle = DefWindowProc(TB_GETEXTENDEDSTYLE, 0, 0);

for (int32_t i = 0; i < nCount; i++)
{
//WINBUG: The IE4 version of COMCTL32.DLL calculates the separation
//  on a TBSTYLE_WRAP button as 100% of the value in iBitmap compared
//  to the other versions which calculate it at 2/3 of that value.
//  This is actually a bug which should be fixed in IE 4.01, so we
//  only do the 100% calculation specifically for IE4.
int32_t cySep = m_itema[i].iBitmap;
ASSERT(gen_ComCtlVersion != -1);
if (!(GetStyle() & TBSTYLE_FLAT) && gen_ComCtlVersion != VERSION_IE4)
cySep = cySep * 2 / 3;

if (m_itema[i].fsState & TBSTATE_HIDDEN)
continue;

int32_t cx = m_sizeButton.cx;
if (m_itema[i].m_fsStyle & TBSTYLE_SEP)
{
// a separator represents either a height or width
if (m_itema[i].fsState & TBSTATE_WRAP)
sizeResult.cy = max(cur.y + m_sizeButton.cy + cySep, sizeResult.cy);
else
sizeResult.cx = max(cur.x + m_itema[i].iBitmap, sizeResult.cx);
}
else
{
// check for dropdown style, but only if the buttons are being drawn
if ((m_itema[i].m_fsStyle & TBSTYLE_DROPDOWN) &&
(dwExtendedStyle & TBSTYLE_EX_DRAWDDARROWS))
{
// add size of drop down
//            ASSERT(gen_DropDownWidth != -1);
//            cx += gen_DropDownWidth;
}
sizeResult.cx = max(cur.x + cx, sizeResult.cx);
sizeResult.cy = max(cur.y + m_sizeButton.cy, sizeResult.cy);
}

if (m_itema[i].m_fsStyle & TBSTYLE_SEP)
cur.x += m_itema[i].iBitmap;
else
cur.x += cx - CX_OVERLAP;

if (m_itema[i].fsState & TBSTATE_WRAP)
{
cur.x = 0;
cur.y += m_sizeButton.cy;
if (m_itema[i].m_fsStyle & TBSTYLE_SEP)
cur.y += cySep;
}
}
return sizeResult;
}*/

void simple_toolbar::OnBarStyleChange(uint32_t dwOldStyle, uint32_t dwNewStyle)
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

size simple_toolbar::CalcDynamicLayout(int32_t nLength, uint32_t dwMode)
{
   if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
      ((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
   {
      return CalcFixedLayout((dwMode & LM_STRETCH) != 0, (dwMode & LM_HORZDOCK) != 0);
   }
   return CalcLayout(dwMode, nLength);
}

void simple_toolbar::_001OnMove(signal_details * pobj)
{
   pobj->previous();
}

void simple_toolbar::_001OnMouseLeave(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj)
      m_iHover = 0x80000000;
   OnUpdateHover();
   _001RedrawWindow();
   pbase->set_lresult(0);
}

void simple_toolbar::SetItemImage(int32_t iItem, int32_t iImage)
{
   m_itema[iItem].m_iImage = iImage;
}

void simple_toolbar::OnUpdateHover()
{

}

int32_t simple_toolbar::_001GetHoverItem()
{
   return m_iHover;
}

void simple_toolbar::RemoveAllTools()
{
   m_itema.remove_all();
}
