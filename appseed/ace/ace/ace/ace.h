#pragma once


#ifndef CA2_APP_AURA_AURA_AURA_AURA_H
#define CA2_APP_AURA_AURA_AURA_AURA_H

#define CA2_AURA


#include "aura_aura.h"

#define system_user_1 "system_user_1"
#define system_user_2 "system_user_2"

#include "nodeapp/operational_system/config_debug.h"

#include "nodeapp/operational_system/config.h"

#if defined(_ACID_LIBRARY)
#define CLASS_DECL_AURA
#elif defined(_AURA_LIBRARY)
#define CLASS_DECL_AURA  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AURA  CLASS_DECL_IMPORT
#endif

#include "app/appseed/ace/version.h"















#include "nodeapp/operational_system/system.h"

#include "aura_types.h"

#include "ace/ace/os/os.h"

#include "ace/primitive/math/math_math.h"

#include "aura_allocate_heap.h"

#include "aura_allocate_processor_cache_oriented.h"

#include "ace/primitive/str/str_c.h"

#include "ace/filesystem/file/file_c.h"

#include "ace/primitive/primitive_memory_c.h"

#include "ace/primitive/datetime/datetime_c.h"

#include "aura_number.h"

#include "ace/ace/aura_policy/aura_policy.h"

#include "aura__c.h"

#define new AURA_NEW

#endif








