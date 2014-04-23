#pragma once


#include "simple_ui_style.h"
#include "simple_ui_interaction.h"
#include "simple_ui_label.h"
#include "simple_ui_edit_box.h"
#include "simple_ui_password.h"
#include "simple_ui_tap.h"


#ifdef WINDOWSEX


#include "base/os/windows/windows_simple_ui.h"


#elif defined(LINUX)


#include "base/os/linux/linux_simple_ui.h"


#elif defined(MACOS)


#include "base/os/macos/macos_simple_ui.h"


#elif defined(METROWIN)


#include "base/os/metrowin/metrowin_simple_ui.h"


#elif defined(ANDROID)


#include "base/os/android/android_simple_ui.h"


#elif defined(SOLARIS)


#include "base/os/solaris/solaris_simple_ui.h"


#elif defined(APPLE_IOS)


#include "base/os/ios/ios_simple_ui.h"


#else


#error "Please implement simple ui for this platform"


#endif
