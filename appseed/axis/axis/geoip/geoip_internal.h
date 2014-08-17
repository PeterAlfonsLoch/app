#pragma once

GEOIP_API uint32_t _GeoIP_seek_record (GeoIP *gi, uint32_t ipnum);
GEOIP_API uint32_t _GeoIP_addr_to_num (const char *addr);

GEOIP_API uint32_t _GeoIP_seek_record_v6 (GeoIP *gi, geoipv6_t ipnum);
GEOIP_API geoipv6_t _GeoIP_addr_to_num_v6 (const char *addr);

GEOIP_API uint32_t _GeoIP_lookupaddress (const char *host);
GEOIP_API geoipv6_t _GeoIP_lookupaddress_v6 (const char *host);
GEOIP_API int32_t __GEOIP_V6_IS_NULL(geoipv6_t v6);

GEOIP_API void _GeoIP_setup_dbfilename();
GEOIP_API char *_GeoIP_full_path_to(const char *file_name);

