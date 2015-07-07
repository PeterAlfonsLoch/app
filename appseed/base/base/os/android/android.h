#pragma once


#include "axis/os/android/android.h"

#include "base/graphics/graphics_window_graphics.h"

#ifdef VSNORD
BEGIN_EXTERN_C
#include "android_vsnord_native_app_glue.h"
END_EXTERN_C
#include "android_window_anative.h"

#else

#include "android_window_android.h"

#endif // VSNORD


#include "android_window_android.h"
//#include "android_window_impl.h"
#include "android_view_bitmap.h"



#include "android_windowing.h"