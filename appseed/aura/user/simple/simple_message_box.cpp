#include "aura/user/user.h"


extern "C"
CLASS_DECL_AURA int32_t aura_simple_message_box(oswindow interaction_impl,const char * lpText,const char * lpCaption,uint32_t uiFlags);


int32_t(*g_pfn_simple_message_box)(oswindow,const char *,const char *,uint32_t) = NULL;


extern "C"
CLASS_DECL_AURA int32_t simple_message_box(oswindow window,const char * lpText,const char * lpCaption,uint32_t uiFlags)
{

   if(g_pfn_simple_message_box != NULL)
   {
      return (*g_pfn_simple_message_box)(window,lpText,lpCaption,uiFlags);
   }

   return aura_simple_message_box(window,lpText,lpCaption,uiFlags);

}



extern "C"
CLASS_DECL_AURA int32_t aura_simple_message_box(oswindow interaction_impl,const char * lpText,const char * lpCaption,uint32_t uiFlags)
{

   return ::MessageBox(interaction_impl,lpText,lpCaption,uiFlags);

}


extern "C"
CLASS_DECL_AURA void set_simple_message_box(int32_t(*pfn)(oswindow,const char *,const char *,uint32_t))
{

   g_pfn_simple_message_box = pfn;

}
