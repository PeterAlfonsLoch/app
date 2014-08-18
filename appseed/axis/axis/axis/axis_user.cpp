#include "framework.h"


int32_t(* g_pfn_simple_message_box) (oswindow windows,const char * lpText,const char * lpCaption,uint32_t iFlags) = NULL;


CLASS_DECL_AXIS int32_t simple_message_box(oswindow windows,const char * lpText,const char * lpCaption,uint32_t iFlags)
{

   if(g_pfn_simple_message_box == NULL)
   {

      return ::MessageBox(windows,lpText,lpCaption,iFlags);

   }
   else
   {

      return (*g_pfn_simple_message_box)(windows,lpText,lpCaption,iFlags);

   }

}


CLASS_DECL_AXIS void set_simple_message_box(int32_t(* pfn) (oswindow windows,const char * lpText,const char * lpCaption,uint32_t iFlags))
{

   g_pfn_simple_message_box = pfn;

}