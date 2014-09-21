#pragma once


#ifdef AURA_LANGUAGE


#ifdef cplusplus

#include "aura_c.h"
#include "aura_cpp.h"


#else


BEGIN_EXTERN_C


#include "aura_c.h"


END_EXTERN_C


#endif


#else


#if defined(__M)


#include "aura_c.h"
#include "aura_policy_objc.h"


#elif defined(__MM)

#include "aura_c.h"
#include "aura_policy_objc.h"
#include "aura_policy_objcpp.h"


#elif defined(__cplusplus_winrt)

#include "aura_c.h"
#include "aura_cpp.h"
#include "aura_policy_winrt.h"


#else


#error "This is a not supported, hope, yet, non converging babylon language."


#endif


#endif
