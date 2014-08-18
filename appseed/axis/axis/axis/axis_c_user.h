#pragma once



CLASS_DECL_AXIS int32_t simple_message_box(oswindow windows,const char * lpText,const char * lpCaption,uint32_t iFlags);

CLASS_DECL_AXIS void set_simple_message_box(int32_t (* pfn) (oswindow windows,const char * lpText,const char * lpCaption,uint32_t iFlags));





