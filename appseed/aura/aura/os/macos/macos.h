#pragma once


#include "macos_oswindow.h"

#include "macos_ns_exception.h"


#include "macos_multithreading.h"

#ifdef cplusplus

namespace macos
{
   
   CGFloat get_system_main_menu_bar_height();
   CGFloat get_system_dock_height();
   
   
} // namespace macos


#endif