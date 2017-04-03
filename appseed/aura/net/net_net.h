#pragma once

#if defined(LINUX) || defined(APPLEOS)

#include <netinet/in.h>

#if defined(APPLEOS)

typedef in6_addr in_addr6;

#endif

#endif

CLASS_DECL_AURA int_bool from_string(in6_addr & addr,const string & str);
template < >
CLASS_DECL_AURA void to_string(string & str, const in6_addr & addr);
CLASS_DECL_AURA int_bool from_string(in_addr & addr,const string & str);
template <  >
CLASS_DECL_AURA void to_string(string & str, const in_addr & addr);
template < >
CLASS_DECL_AURA void to_string(string & str, const sockaddr_in &  addr);
template < >
CLASS_DECL_AURA void to_string(string & str, const sockaddr_in6 &  addr);
#ifdef BSD_STYLE_SOCKETS
template < >
CLASS_DECL_AURA void to_string(string & str, const sockaddr & addr);
#endif





CLASS_DECL_AURA uint32_t c_inet_addr(const char *src);
CLASS_DECL_AURA int32_t c_inet_pton(int32_t af,const char *src,void *dst);
CLASS_DECL_AURA const char * c_inet_ntop(int32_t af,const void *src,char *dst,int32_t cnt);
CLASS_DECL_AURA string c_inet_ntop(int32_t af,const void *src);



CLASS_DECL_AURA string c_gethostbyname(const char * hostname);

CLASS_DECL_AURA string get_file_extension_mime_type(const string & strExtension);


#include "net_byte_order.h"


