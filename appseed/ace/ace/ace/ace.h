#pragma once


#ifndef CA2_APP_ACE_ACE_ACE_ACE_H
#define CA2_APP_ACE_ACE_ACE_ACE_H

#define CA2_ACE


#include "ace_ace.h"

#define system_user_1 "system_user_1"
#define system_user_2 "system_user_2"

#include "nodeapp/operational_system/config_debug.h"

#include "nodeapp/operational_system/config.h"

#if defined(_ACID_LIBRARY)
#define CLASS_DECL_ACE
#elif defined(_ACE_LIBRARY)
#define CLASS_DECL_ACE  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_ACE  CLASS_DECL_IMPORT
#endif

#include "app/appseed/ace/version.h"















#include "nodeapp/operational_system/system.h"

#include "ace_types.h"

#include "ace/ace/os/os.h"

#include "ace/primitive/math/math_math.h"

#include "ace_allocate_heap.h"

#include "ace_allocate_processor_cache_oriented.h"

#include "ace/primitive/str/str_c.h"

#include "ace/filesystem/file/file_c.h"

#include "ace/primitive/primitive_memory_c.h"

#include "ace/primitive/datetime/datetime_c.h"

#include "ace_number.h"

#include "ace/ace/ace_policy/ace_policy.h"

#include "ace__c.h"

#define new ACE_NEW

#endif








