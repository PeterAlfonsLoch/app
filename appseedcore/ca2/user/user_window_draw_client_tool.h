#pragma once

#include "flags.h"

namespace user
{
   enum ETransparentWndRenderResult
   {
      RenderError,
      RenderSuccess,
      RenderDoNotProceedWithChildren,
   };
}


namespace user
{

   class CLASS_DECL_ca window_draw_client_tool : 
      virtual public ::radix::object
   {
   public:


      flags < ETransparentWndRenderResult>   m_renderresultflags;
      ::ca::graphics *                       m_pdc;
      ::ca::rgn_sp                           m_rgnClip;
      ::ca::rgn_sp                           m_rgnClient;

      
      window_draw_client_tool(::ca::application * papp);
      virtual ~window_draw_client_tool();


      ::ca::graphics * GetDC();
      void FastClear();
      bool IsSignalizedRenderResult(ETransparentWndRenderResult eresult);
      void SignalizeRenderResult(ETransparentWndRenderResult eresult);
      ::ca::rgn & GetClipRgn();
      ::ca::rgn & GetClientRgn();
      void SetDC(::ca::graphics * pdc);

   };

   inline ::ca::rgn & window_draw_client_tool::GetClipRgn()
   {
      return m_rgnClip;
   }

   inline ::ca::rgn & window_draw_client_tool::GetClientRgn()
   {
      return m_rgnClient;
   }

   inline ::ca::graphics * window_draw_client_tool::GetDC()
   {
      return m_pdc;
   }

} // namespace user
