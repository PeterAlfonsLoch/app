#pragma once


CLASS_DECL_AURA void __trace_message(const char * lpszPrefix,::signal_details * pobj);
CLASS_DECL_AURA void __trace_message(const char * lpszPrefix,LPMESSAGE lpmsg);

#ifdef __cplusplus

CLASS_DECL_AURA void __node_aura_factory_exchange(sp(::aura::application) papp);
CLASS_DECL_AURA void __node_init_main_data(::aura::application * papp,HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int32_t nCmdShow);

#endif


