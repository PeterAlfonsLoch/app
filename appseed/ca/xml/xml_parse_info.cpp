#include "framework.h"


namespace xml
{


   parse_info::parse_info(::ca::applicationsp papp)
   {
      m_bTrimValue      = false; 
      m_bEntityValue    = true; 
      m_bForceParse     = false;
      m_pentities       = &Sys(papp).xml().m_entities; 
      
      m_bErrorOccur     = false;
      m_pszErrorPointer = ::null();
      m_eparseerror     = parse_error_welformed;
      m_chEscapeValue   = '\\';
   }


} // namespace xml



