#pragma once

namespace user
{
   namespace signal
   {
      
      class CLASS_DECL_ca cdc :
         public gen::signal_object
      {
      public:
         cdc(gen::signal * psignal) : signal_object(psignal){};
         ::ca::graphics *    m_pdc;
      };

   } // namespace signal
} // namespace user

class CLASS_DECL_ca window_draw_interface  
{
public:
   virtual void _001OnNcDraw(::ca::graphics * pdc);
   virtual void _001OnDraw(::ca::graphics * pdc);

   window_draw_interface();
   virtual ~window_draw_interface();

   gen::signal m_signalOnDraw;
   gen::signal m_signalOnNcDraw;
};

#define IGUI_PARAM_CDC(pvar) \
   SCAST_PTR(user::signal::cdc, pcdc, pobj) \
   ::ca::graphics * pvar = pcdc->m_pdc;
