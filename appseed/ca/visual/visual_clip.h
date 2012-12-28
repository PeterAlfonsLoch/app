#pragma once

namespace visual
{

   class CLASS_DECL_ca clip  
   {
   public:
      clip();
      clip(::ca::window * pwnd, ::ca::graphics * pdc);
      clip(::ca::graphics * pdc, ::ca::region * prgn);
      clip(::ca::graphics * pdc, LPCRECT lprect);
      virtual ~clip();
      
   protected:
      ::ca::region   m_rgn; // applied clipping region   
      ::ca::region    m_rgnOld; // previous clipping region
      int32_t      m_iOldType; // previous clipping region type
      ::ca::graphics   *   m_pdc; // clipped device context
      ::ca::window *  m_pwnd; // ::ca::window that draws at the device context
      bool   m_bAcquired; // Do function has been called

   public:
      void Do(::ca::window * pwnd, ::ca::graphics * pdc);
      void Do(::ca::graphics * pdc, ::ca::region * prgn);
      void Do(::ca::graphics * pdc, LPCRECT lpcrect);
      void Undo();



   };


} // namespace visual