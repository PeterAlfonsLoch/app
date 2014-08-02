#pragma once


CLASS_DECL_BASE int_bool from_string(in6_addr * addr, const char * string);
CLASS_DECL_BASE string to_vsstring(const in6_addr *addr);
CLASS_DECL_BASE int_bool from_string(in_addr * addr, const char * string);
CLASS_DECL_BASE string to_vsstring(const in_addr *addr);
#ifdef BSD_STYLE_SOCKETS
CLASS_DECL_BASE string to_vsstring(const sockaddr *addr);
#endif

CLASS_DECL_BASE uint32_t c_inet_addr(const char *src);
CLASS_DECL_BASE int32_t c_inet_pton(int32_t af, const char *src, void *dst);
CLASS_DECL_BASE const char * c_inet_ntop(int32_t af, const void *src, char *dst, int32_t cnt);
CLASS_DECL_BASE string c_inet_ntop(int32_t af, const void *src);


CLASS_DECL_BASE string c_gethostbyname(const char * hostname);

CLASS_DECL_BASE string get_file_extension_mime_type(const string & strExtension);


#include "net_byte_order.h"


