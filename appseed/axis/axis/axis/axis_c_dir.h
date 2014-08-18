#pragma once

#if defined(WINDOWS)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif


CLASS_DECL_AXIS int_bool dir_is(const char * path1);
CLASS_DECL_AXIS int_bool dir_mk(const char * lpcsz);
