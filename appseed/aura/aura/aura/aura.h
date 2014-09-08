#pragma once


#ifndef CA2_APP_AURA_AURA_AURA_AURA_H
#define CA2_APP_AURA_AURA_AURA_AURA_H


#include "aura_aura.h"

#define system_user_1 "system_user_1"
#define system_user_2 "system_user_2"

#include "nodeapp/operational_system/config.h"

#if defined(_ACID_LIBRARY)
#define CLASS_DECL_AURA
#elif defined(_AURA_LIBRARY)
#define CLASS_DECL_AURA  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AURA  CLASS_DECL_IMPORT
#endif

#include "app/appseed/aura/version.h"

#include "nodeapp/operational_system/system.h"

#include "aura_types.h"

#include "aura/aura/os/os.h"

#include "aura/primitive/math/_math.h"

#include "aura_heap.h"

#include "aura/primitive/str/str_c.h"

#include "aura/filesystem/file/file_c.h"

#include "aura/primitive/primitive_memory_c.h"

#include "aura/primitive/datetime/datetime_c.h"

#include "aura_number.h"

#include "aura/aura/aura_policy/aura_policy.h"

#endif
