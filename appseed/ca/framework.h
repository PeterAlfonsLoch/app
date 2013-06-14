#ifndef __GNUC__
#pragma once
#endif

#ifdef __OBJC__
#include "c_mm.h"
#else
#include "c/c.h"
#if defined(MACOS)
#include "macos/c_os_internal.h"
#elif defined(LINUX)
#include "linux/c_os_internal.h"
#elif defined(WINDOWS)
#include "windows/c_os_internal.h"
#endif
#endif




