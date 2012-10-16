#pragma once



CLASS_DECL_c int FUNCTION_DEBUGBOX(const char * pszMessage, const char * pszTitle, int iFlags); 
inline int FUNCTION_XXDEBUGBOX(const char * pszMessage, const char * pszTitle, int iFlags)
{
   return 0;
}

#define debug_box FUNCTION_DEBUGBOX
#define xxdebug_box FUNCTION_XXDEBUGBOX