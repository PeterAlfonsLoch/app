#pragma once


#include "aura/os/ansios/ansios_file.h"


#include "linux_debug.h"



BEGIN_EXTERN_C

off_t tell64(int fd);

END_EXTERN_C



#ifdef cplusplus

#define LOG_THIS_TAG (demangle(typeid(*this).name()))
#define LOG_MEMBER_PREFIX __FUNCTION__

#endif


