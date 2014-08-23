#pragma once


#ifdef AURA_LANGUAGE


#ifdef cplusplus


#include "axis_c.h"
#include "axis_cpp.h"


#else


BEGIN_EXTERN_C


#include "axis_c.h"


END_EXTERN_C


#endif


#else


#if defined(__M)


#include "axis_c.h"
#include "axis_policy_objc.h"


#elif defined(__MM)


#include "axis_c.h"
#include "axis_policy_objc.h"
#include "axis_policy_objcpp.h"


#elif defined(__cplusplus_winrt)


#include "axis_c.h"
#include "axis_policy_cpp.h"
#include "axis_policy_winrt.h"


#else


#error "This is a not supported, hope, yet, non converging babylon language."


#endif


#endif
