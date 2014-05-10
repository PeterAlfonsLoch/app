#include "framework.h"


BaseSplitWnd::BaseSplitWnd(sp(::base::application) papp) :
   element(papp),
   ::user::split_layout(papp),
   place_holder_container(papp)
{
}

BaseSplitWnd::~BaseSplitWnd()
{
}

bool BaseSplitWnd::pre_create_window(CREATESTRUCT& cs) 
{
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
   
   return ::user::interaction::pre_create_window(cs);
}

void BaseSplitWnd::_001OnDraw(::draw2d::graphics *pdc)
{
   
   int32_t i;
   rect rect;
   COLORREF cr = RGB(92, 92, 80);
   for(i = 0; i < get_pane_count(); i++)
   {
      CalcPaneRect(i, &rect);

      // Top
      pdc->FillSolidRect(
         rect.left, 
         rect.top, 
         rect.width(),
         m_cyBorder,
         cr);

      // Right
      pdc->FillSolidRect(
         rect.right - m_cxBorder, 
         rect.top, 
         m_cxBorder,
         rect.height(),
         cr);

      // Bottom
      pdc->FillSolidRect(
         rect.left, 
         rect.bottom - m_cyBorder, 
         rect.width(),
         m_cyBorder,
         cr);

      // Left
      pdc->FillSolidRect(
         rect.left, 
         rect.top, 
         m_cxBorder,
         rect.height(),
         cr);
   }

}


