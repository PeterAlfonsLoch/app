#pragma once


#ifdef AURA_LANGUAGE


#ifdef cplusplus


#include "c.h"
#include "cpp.h"


#else


BEGIN_EXTERN_C


#include "c.h"


END_EXTERN_C


#endif


#else


#if defined(__M)


#include "axis_c.h"
#include "axis_c_objc.h"


#elif defined(__MM)


#include "axis_c.h"
#include "axis_c_objc.h"
#include "axis_c_objcpp.h"


#elif defined(__cplusplus_winrt)


#include "axis_c.h"
#include "axis_c_cpp.h"
#include "axis_c_winrt.h"


#else


#error "This is a not supported, hope, yet, non converging babylon language."


#endif


#endif
