#include "framework.h"

#ifdef METROWIN

namespace user
{


   Platform::Agile<Windows::UI::Core::CoreWindow> (* base_interaction::s_get_os_window)(base_interaction * pui) = &base_interaction::get_os_window_default;


}


#endif