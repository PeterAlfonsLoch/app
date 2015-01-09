#pragma once

#include "turboc_application.h"



CLASS_DECL_TURBOC ::turboc::context & get_turboc_context();
CLASS_DECL_TURBOC ::turboc::application & get_turboc_application();
CLASS_DECL_TURBOC ::console::application & get_console_application();

inline ::turboc::context & tc()
{
   return get_turboc_context();
}