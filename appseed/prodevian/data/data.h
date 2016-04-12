#pragma once


#include "axis/axis/axis.h"


#if defined(_CA2_DATA_DLL)
   #define CLASS_DECL_CA2_DATA  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_CA2_DATA  CLASS_DECL_IMPORT
#endif


#include "app/appseed/data/simpledb/mysql_result.h"
#include "app/appseed/data/simpledb/mysql_database.h"