#include "framework.h" // previously aura/user/user.h


extern "C"
CLASS_DECL_AURA int32_t aura_simple_message_box(oswindow interaction_impl,const char * lpText,const char * lpCaption,uint32_t uiFlags);


int32_t(*g_pfn_simple_message_box)(oswindow,const char *,const char *,uint32_t) = NULL;


extern "C"
CLASS_DECL_AURA int32_t simple_message_box(oswindow window,const char * lpText,const char * lpCaption,uint32_t uiFlags)
{
#ifndef METROWIN
   if(g_pfn_simple_message_box != NULL)
   {
      return (*g_pfn_simple_message_box)(window,lpText,lpCaption,uiFlags);
   }
#endif
   return aura_simple_message_box(window,lpText,lpCaption,uiFlags);

}

#ifndef WINDOWSEX
//----------------------------------------------------------------------------------------------------------------
// TODO(casey) : Handmade Hero Casei Muratori (Casey) contribution!! Thank you, (casey)!!
// Casey Muratori fallback concept - meets my self-healing concept - < count paranoid?!?!?!!
//
int MessageBoxA(oswindow_data * window,const char * pszText,const char * pszTitle,unsigned int uiFlags)
{

   return ::MessageBoxW(window,wstring(pszText),wstring(pszTitle),uiFlags);

}
//
//
//----------------------------------------------------------------------------------------------------------------
#endif

extern "C"
CLASS_DECL_AURA int32_t aura_simple_message_box(oswindow interaction_impl,const char * lpText,const char * lpCaption,uint32_t uiFlags)
{

   return ::MessageBoxA(interaction_impl,lpText,lpCaption,uiFlags);

}


extern "C"
CLASS_DECL_AURA void set_simple_message_box(int32_t(*pfn)(oswindow,const char *,const char *,uint32_t))
{

   g_pfn_simple_message_box = pfn;

}
