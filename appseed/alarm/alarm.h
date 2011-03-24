#pragma once

#include "include/cube.h"


#ifdef _CA2_FONTOPUS_ALARM_DLL
    #define CLASS_DECL_CA2_ALARM  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_ALARM  _declspec(dllimport)
#endif

namespace alarm
{
   class application;
} // namespace alarm

#undef App
#define App(pcaapp) (alarm::app_cast(pcaapp))


#include "alatel_document.h"
#include "alatel_frame.h"
#include "alatel_view.h"

#include "alatel_alarm_list_view.h"
#include "alatel_week_view.h"

#include "document.h"
#include "frame.h"
#include "view.h"

#include "pane_view.h"
#include "pane_view_update_hint.h"

#include "service.h"
#include "application.h"

