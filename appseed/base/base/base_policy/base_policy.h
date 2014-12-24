#pragma once


#ifdef AURA_LANGUAGE


#ifdef cplusplus



#include "base_c.h"
#include "base_cpp.h"


#else


BEGIN_EXTERN_C


#include "base_c.h"


END_EXTERN_C


#endif


#else


#if defined(__M)


#include "base_c.h"
#include "base_policy_objc.h"


#elif defined(__MM)


#include "base_c.h"
#include "base_policy_objc.h"
#include "base_policy_objcpp.h"


#elif defined(__cplusplus_winrt)


#include "base_c.h"
#include "base_cpp.h"
#include "base_policy_winrt.h"


#else


#error "This is a not supported, hope, yet, non converging babylon language."


#endif


#endif
