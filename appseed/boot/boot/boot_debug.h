#pragma once



CLASS_DECL_BOOT int32_t FUNCTION_DEBUGBOX(const char * pszMessage, const char * pszTitle, int32_t iFlags); 
inline int32_t FUNCTION_XXDEBUGBOX(const char * pszMessage, const char * pszTitle, int32_t iFlags)
{
   return 0;
}

#define debug_box FUNCTION_DEBUGBOX
#define xxdebug_box FUNCTION_XXDEBUGBOX



