#pragma once


BEGIN_EXTERN_C


struct tm;

CLASS_DECL_AURA dword get_tick_count();

CLASS_DECL_AURA time_t timegm(tm *tmp);


END_EXTERN_C



