#pragma once


#include "setup/debug.h"


#ifndef CA2_APP_AURA_AURA_AURA_AURA_H
#define CA2_APP_AURA_AURA_AURA_AURA_H

#define CA2_AURA


#include "aura_aura.h"


#include "ace/ace.h"


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

#include "aura/primitive/math/math_math.h"

#include "aura_allocate_heap.h"

#include "aura_allocate_processor_cache_oriented.h"

#include "aura/primitive/str/str_c.h"

#include "aura/filesystem/file/file_c.h"

#include "aura/primitive/primitive_memory_c.h"

#include "aura/primitive/datetime/datetime_c.h"

#include "aura_number.h"

#include "aura/aura/aura_policy/aura_policy.h"

#include "aura__c.h"

#define new AURA_NEW

#endif








