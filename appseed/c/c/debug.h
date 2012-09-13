#pragma once



CLASS_DECL_c int function_DEBUGBOX(const char * pszMessage, const char * pszTitle, int iFlags); 
inline int function_XXDEBUGBOX(const char * pszMessage, const char * pszTitle, int iFlags)
{
}

#define debug_box function_DEBUGBOX
#define xxdebug_box function_XXDEBUGBOX