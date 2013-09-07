#pragma once

   class timer_callback;

class CLASS_DECL_ca2 timer  
{
public:
   class CCreate
   {
   public:
      timer_callback *   m_ptimercallback;
      UINT            m_uiElapse;
      UINT            m_uiIDEvent;
   };

public:
   timer();
   virtual ~timer();
   static const UINT ID_HOVER;
};
