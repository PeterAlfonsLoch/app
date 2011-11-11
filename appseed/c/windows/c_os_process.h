#pragma once
#ifdef WIN32
#include <ShellAPI.h> // TODO: try to remove - by replacing -  SHELLEXECUTEINFOA from execute_sync
#elif defined WIN64
#include <ShellAPI.h> // TODO: try to remove - by replacing -  SHELLEXECUTEINFOA from execute_sync
#endif


CLASS_DECL_____ void call_sync(const char * path, const char * param);
#ifdef WINDOWS
CLASS_DECL_____ void execute_sync(SHELLEXECUTEINFOA * pinfoa);
#endif
