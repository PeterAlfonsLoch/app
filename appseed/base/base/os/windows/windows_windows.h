#pragma once


#include "openssl/ssl.h"


#include "windows_registry.h"
#include "windows_process.h"
#include "windows_simple_hold_handle.h"
#include "windows_file.h"
#include "windows_file_watcher.h"


#define GetAValue(rgb)      (LOBYTE((rgb)>>24))



#define MESSAGE MSG
#define LPMESSAGE LPMSG