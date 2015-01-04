#include "framework.h"
#include"net/net_sockets.h"
#include"geoip.h"

#ifdef WINDOWS

#include<Winsock2.h>

#endif

#include<sys/stat.h>

static geoipv6_t IPV6_NULL;


#define GEOIPDATADIR "/core/geoip"

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

#include<sys/mman.h>

#endif

#if defined(APPLEOS)

#include<arpa/inet.h>
#include<sys/time.h>

#endif

//O volume na unidade C n∆o tem nome.
 //O N£mero de SÇrie do Volume Ç 72AC-5E14

 //Pasta de C:\nordroid\app\appseed\axis\axis\geoip

#include "geoip.cpp"
#include "geoip_city.cpp"
#include "geoip_region_name.cpp"
#include "geoip_time_zone.cpp"
#include "geoip_update.cpp"
//2015-01-04  19:32                 0 _geoip.cpp"
//               6 arquivo(s)        385.915 bytes
//               0 pasta(s)   19.203.747.840 bytes dispon°veis
