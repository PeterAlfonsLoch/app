#include "framework.h"

#if defined(LINUX) || defined(APPLEOS)
#include <dlfcn.h>
#endif

#include <math.h>

#include "asphere/asphere_application.cpp"
#include "asphere/asphere_asphere.cpp"


#include "calculator/calculator_application.cpp"
#include "calculator/calculator_document.cpp"
#include "calculator/calculator_frame.cpp"
#include "calculator/calculator_view.cpp"

#include "command/command_application.cpp"
#include "command/command_document.cpp"
#include "command/command_form_callback.cpp"
#include "command/command_frame.cpp"
#include "command/command_pane_view.cpp"
#include "command/command_pane_view_update_hint.cpp"
#include "command/command_primary_view.cpp"
#include "command/command_view.cpp"



#include "console/console_application.cpp"
#include "console/console_prompt.cpp"
#include "console/console_prompt_document.cpp"
#include "console/console_prompt_frame.cpp"
#include "console/console_prompt_impact.cpp"

#include "filehandler/filehandler_application.cpp"
#include "filehandler/filehandler_document.cpp"
#include "filehandler/filehandler_frame.cpp"
#include "filehandler/filehandler_pane_view.cpp"
#include "filehandler/filehandler_pane_view_update_hint.cpp"
#include "filehandler/filehandler_view.cpp"


#include "sphere/sphere_application.cpp"
#include "sphere/sphere_library.cpp"

#include "userstack/userstack_pane_view.cpp"
#include "userstack/userstack_pane_view_update_hint.cpp"
#include "userstack/userstack_view.cpp"
#include "userstack/userstack_application.cpp"
#include "userstack/userstack_document.cpp"
#include "userstack/userstack_form_callback.cpp"
#include "userstack/userstack_frame.cpp"
