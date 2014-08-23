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


#include "c.h"
#include "policy_objc.h"


#elif defined(__MM)


#include "c.h"
#include "policy_objc.h"
#include "policy_objcpp.h"


#elif defined(__cplusplus_winrt)


#include "c.h"
#include "policy_cpp.h"
#include "policy_winrt.h"


#else


#error "This is a not supported, hope, yet, non converging babylon language."


#endif


#endif
