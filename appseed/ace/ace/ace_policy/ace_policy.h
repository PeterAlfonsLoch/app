#pragma once


#ifdef ACE_LANGUAGE


#ifdef cplusplus


#include "ace_c.h"
#include "ace_cpp.h"


#else


BEGIN_EXTERN_C


#include "ace_c.h"


END_EXTERN_C


#endif


#else


#if defined(__M)


#include "ace_c.h"
#include "ace_policy_objc.h"


#elif defined(__MM)


#include "ace_c.h"
#include "ace_policy_objc.h"
#include "ace_policy_objcpp.h"


#elif defined(__cplusplus_winrt)


#include "ace_c.h"
#include "ace_cpp.h"
#include "ace_policy_winrt.h"


#else


#error "This is a not supported, hope, yet, non converging babylon language."


#endif


#endif
