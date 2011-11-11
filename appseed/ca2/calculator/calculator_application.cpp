#include "StdAfx.h"
#include "application.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"


namespace calculator
{

   application::application(void)
   {
   }

   application::~application(void)
   {
   }

   bool application::initialize()
   {

      m_pcalculator = new class calculator(this);

      if(m_pcalculator == NULL)
         return false;

      return true;
   }

   calculator & application::calculator()
   {
      return * m_pcalculator;
   }

} // namespace calculator