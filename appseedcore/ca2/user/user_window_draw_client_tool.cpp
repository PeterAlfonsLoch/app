#include "StdAfx.h"

namespace user
{

   window_draw_client_tool::window_draw_client_tool(::ca::application * papp) :
      ca(papp)
   {
      m_rgnClip.create(papp);
      m_rgnClient.create(papp);
      m_rgnClip->CreateRectRgn(0, 0, 0, 0);
      m_rgnClient->CreateRectRgn(0, 0, 0, 0);
   }

   window_draw_client_tool::~window_draw_client_tool()
   {

   }

   void window_draw_client_tool::SetDC(::ca::graphics * pdc)
   {
      m_pdc = pdc;
   }


   bool window_draw_client_tool::IsSignalizedRenderResult(ETransparentWndRenderResult eresult)
   {
      return m_renderresultflags.is_signalized(eresult);
   }

   void window_draw_client_tool::SignalizeRenderResult(ETransparentWndRenderResult eresult)
   {
      m_renderresultflags.signalize(eresult);
   }




   void window_draw_client_tool::FastClear()
   {
      m_renderresultflags.unsignalize_all();
   }

} // namespace user

