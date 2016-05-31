#pragma once


BEGIN_EXTERN_C

CLASS_DECL_AURA uint32_t thread_alloc();
CLASS_DECL_AURA int_bool thread_free(uint32_t dwIndex);
CLASS_DECL_AURA void * thread_get_data(uint32_t dwIndex);
CLASS_DECL_AURA int_bool thread_set_data(uint32_t dwIndex,void * lpTlsValue);
CLASS_DECL_AURA void thread_shutdown();

END_EXTERN_C



