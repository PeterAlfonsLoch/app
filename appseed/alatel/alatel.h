#pragma once


#include "include/ca2.h"


#ifdef _CA2_FONTOPUS_ALARM_DLL
    #define CLASS_DECL_CA2_ALARM  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_ALARM  _declspec(dllimport)
#endif

namespace alatel
{
   class application;
} // namespace alatel

#undef App
#define App(pcaapp) (alatel::app_cast(pcaapp))


#include "alatel_main_document.h"
#include "alatel_main_frame.h"
#include "alatel_main_view.h"

#include "alatel_pane_view.h"
#include "alatel_pane_view_update_hint.h"

#include "alatel_alarm_list_view.h"
#include "alatel_week_view.h"

#include "alatel_document.h"
#include "alatel_frame.h"
#include "alatel_view.h"


#include "alatel_service.h"
#include "alatel_application.h"

