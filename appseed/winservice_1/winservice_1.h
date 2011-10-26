#pragma once


#include "include/ca2.h"
#include "os/windows/os.h"


#ifdef _CA2_FONTOPUS_WINSERVICE_1_DLL
    #define CLASS_DECL_CA2_WINSERVICE_1  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_WINSERVICE_1  _declspec(dllimport)
#endif



#include "winservice_1_update_thread.h"
#include "winservice_1_update_schedule_thread.h"
#include "winservice_1_message_window.h"
#include "winservice_1_thread.h"


#include "winservice_1_application.h"


