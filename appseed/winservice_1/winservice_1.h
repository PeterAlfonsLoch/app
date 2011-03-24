#pragma once

#include "include/cube.h"
// this is a win application, by now
#include "win/win.h"

#ifdef _CA2_FONTOPUS_WINSERVICE_1_DLL
    #define CLASS_DECL_CA2_WINSERVICE_1  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_WINSERVICE_1  _declspec(dllimport)
#endif

#include "update_thread.h"
#include "update_schedule_thread.h"

#include "message_window.h"

#include "thread.h"

#include "application.h"
