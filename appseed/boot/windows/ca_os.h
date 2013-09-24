#pragma once


#include "openssl/ssl.h"


#include "ca_os_gdi.h"
#include "ca_os_registry.h"
#include "ca_os_process.h"
#include "ca_os_simple_hold_handle.h"
#include "ca_os_file.h"
#include "ca_os_file_watcher.h"
#include "ca_os_graphics_round_rect.h"


#define GetAValue(rgb)      (LOBYTE((rgb)>>24))



#define MESSAGE MSG
#define LPMESSAGE LPMSG