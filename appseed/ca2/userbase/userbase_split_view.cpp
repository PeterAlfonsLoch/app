#include "framework.h"

namespace userbase
{

   split_view::split_view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp),
      split_layout(papp),
      place_holder_container(papp)
   {
   }

   split_view::~split_view()
   {
   }

   void split_view::install_message_handling(::ca::message::dispatch * pinterface)
   {
      view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &split_view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &split_view::_001OnShowWindow);
   }



   /////////////////////////////////////////////////////////////////////////////
   // split_view diagnostics

   #ifdef DEBUG
   void split_view::assert_valid() const
   {
      view::assert_valid();
   }

   void split_view::dump(dump_context & dumpcontext) const
   {
      view::dump(dumpcontext);
   }
   #endif //DEBUG


   void split_view::_001OnSize(ca::signal_object * pobj) 
   {
      SCAST_PTR(::ca::message::size, psize, pobj)
      psize->previous();
      //layout();
   }

   bool split_view::pre_create_window(CREATESTRUCT& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
      
      return view::pre_create_window(cs);
   }

   void split_view::_001OnDraw(::ca::graphics *pdc)
   {
      int32_t i;
      rect rect;
      COLORREF cr = ARGB(184, 92, 92, 80);
      //COLORREF crBack = ARGB(77, 230, 230, 210);
      //pdc->set_alpha_mode(::ca::alpha_mode_blend);
      for(i = 0; i < get_pane_count(); i++)
      {
         CalcPaneRect(i, &rect);

        // pdc->FillSolidRect(rect, crBack);


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


   void split_view::_001OnShowWindow(ca::signal_object * pobj) 
   {
      SCAST_PTR(::ca::message::show_window, pshowwindow, pobj)
      pshowwindow->previous();
      layout();
   }

} // namespace userbase