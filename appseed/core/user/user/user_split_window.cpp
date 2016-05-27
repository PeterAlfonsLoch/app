//#include "framework.h"


BaseSplitWnd::BaseSplitWnd(::aura::application * papp) :
   object(papp),
   ::user::split_layout(papp),
   place_holder_container(papp)
{
}

BaseSplitWnd::~BaseSplitWnd()
{
}

bool BaseSplitWnd::pre_create_window(::user::create_struct& cs) 
{
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
   
   return ::user::interaction::pre_create_window(cs);
}

void BaseSplitWnd::_001OnDraw(::draw2d::graphics * pgraphics)
{

   
   
   int32_t i;
   rect rect;
   COLORREF cr = RGB(92, 92, 80);
   for(i = 0; i < get_pane_count(); i++)
   {
      CalcPaneRect(i, &rect);

      // Top
      pgraphics->FillSolidRect(
         rect.left, 
         rect.top, 
         rect.width(),
         m_cyBorder,
         cr);

      // Right
      pgraphics->FillSolidRect(
         rect.right - m_cxBorder, 
         rect.top, 
         m_cxBorder,
         rect.height(),
         cr);

      // Bottom
      pgraphics->FillSolidRect(
         rect.left, 
         rect.bottom - m_cyBorder, 
         rect.width(),
         m_cyBorder,
         cr);

      // Left
      pgraphics->FillSolidRect(
         rect.left, 
         rect.top, 
         m_cxBorder,
         rect.height(),
         cr);
   }

}


