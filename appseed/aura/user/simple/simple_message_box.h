#pragma once


extern "C"
CLASS_DECL_AURA int32_t set_simple_message_box(int32_t(*pfn)(oswindow,const char *,const char *,uint32_t));


extern "C"
CLASS_DECL_AURA int32_t simple_message_box(oswindow interaction_impl,const char * lpText,const char * lpCaption,uint32_t uiFlags);


