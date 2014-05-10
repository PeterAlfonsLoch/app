#pragma once

   class timer_callback;

class CLASS_DECL_CORE timer  
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
