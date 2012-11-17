#include "framework.h"


unsigned long c_inet_to_ui(const char * src)
{

   if(str_begins_ci_dup(src, "0x"))
   {

      return (unsigned long) atoi64_dup(&src[2], NULL, 16);

   }
   else if(str_begins_dup(src, "0"))
   {

      return (unsigned long) atoi64_dup(&src[1], NULL, 16);

   }
   else
   {

      return (unsigned long) atoi64_dup(src, NULL, 10);

   }

}

#define XX 127
static const unsigned char index_hex[256] = {
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   0, 1, 2, 3,  4, 5, 6, 7,  8, 9,XX,XX, XX,XX,XX,XX,
   XX,10,11,12, 13,14,15,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,10,11,12, 13,14,15,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
};


#define pr_s6_addr16 u.Word
#define pr_s6_addr u.Byte


/*
* StringToV6Addr() returns 1 if the conversion succeeds,
* or 0 if the input is not a valid IPv6 address string.
* (Same as inet_pton(AF_INET6, string, addr).)
*/
CLASS_DECL_c bool from_string(in6_addr * addr, const char * string)
{
   const unsigned char *s = (const unsigned char *)string;
   int section = 0;        /* index of the current section (a 16-bit
                           * piece of the address */
   int double_colon = -1;  /* index of the section after the first
                           * 16-bit group of zeros represented by
                           * the double colon */
   unsigned int val;
   int len;

   /* Handle initial (double) colon */
   if (*s == ':') {
      if (s[1] != ':') return 0;
      s += 2;
      addr->pr_s6_addr16[0] = 0;
      section = double_colon = 1;
   }

   while (*s) {
      if (section == 8) return 0; /* too long */
      if (*s == ':') {
         if (double_colon != -1) return 0; /* two double colons */
         addr->pr_s6_addr16[section++] = 0;
         double_colon = section;
         s++;
         continue;
      }
      for (len = val = 0; len < 4 && index_hex[*s] != XX; len++) {
         val = (val << 4) + index_hex[*s++];
      }
      if (*s == '.') {
         if (len == 0) return 0; /* nothing between : and . */
         break;
      }
      if (*s == ':') {
         s++;
         if (!*s) return 0; /* cannot end with single colon */
      } else if (*s) {
         return 0; /* bad character */
      }
      addr->pr_s6_addr16[section++] = HTONS((unsigned short)val);
   }

   if (*s == '.') {
      /* Have a trailing v4 format address */
      if (section > 6) return 0; /* not enough room */

      /*
      * The number before the '.' is decimal, but we parsed it
      * as hex.  That means it is in BCD.  Check it for validity
      * and convert it to binary.
      */
      if (val > 0x0255 || (val & 0xf0) > 0x90 || (val & 0xf) > 9) return 0;
      val = (val >> 8) * 100 + ((val >> 4) & 0xf) * 10 + (val & 0xf);
      addr->pr_s6_addr[2 * section] = val;

      s++;
      val = index_hex[*s++];
      if (val > 9) return 0;
      while (*s >= '0' && *s <= '9') {
         val = val * 10 + *s++ - '0';
         if (val > 255) return 0;
      }
      if (*s != '.') return 0; /* must have exactly 4 decimal numbers */
      addr->pr_s6_addr[2 * section + 1] = val;
      section++;

      s++;
      val = index_hex[*s++];
      if (val > 9) return 0;
      while (*s >= '0' && *s <= '9') {
         val = val * 10 + *s++ - '0';
         if (val > 255) return 0;
      }
      if (*s != '.') return 0; /* must have exactly 4 decimal numbers */
      addr->pr_s6_addr[2 * section] = val;

      s++;
      val = index_hex[*s++];
      if (val > 9) return 0;
      while (*s >= '0' && *s <= '9') {
         val = val * 10 + *s++ - '0';
         if (val > 255) return 0;
      }
      if (*s) return 0; /* must have exactly 4 decimal numbers */
      addr->pr_s6_addr[2 * section + 1] = val;
      section++;
   }

   if (double_colon != -1) {
      /* Stretch the double colon */
      int tosection;
      int ncopy = section - double_colon;
      for (tosection = 7; ncopy--; tosection--) {
         addr->pr_s6_addr16[tosection] =
            addr->pr_s6_addr16[double_colon + ncopy];
      }
      while (tosection >= double_colon) {
         addr->pr_s6_addr16[tosection--] = 0;
      }
   } else if (section != 8) {
      return 0; /* too short */
   }
   return 1;
}
#undef XX

static const char *basis_hex = "0123456789abcdef";

/*
* V6AddrToString() returns a pointer to the buffer containing
* the text string if the conversion succeeds, and NULL otherwise.
* (Same as inet_ntop(AF_INET6, addr, buf, size), except that errno
* is not set on failure.)
*/
CLASS_DECL_c vsstring to_string(const in6_addr * addr)
{

   vsstring str;

#define STUFF(c) { str += (c); }

   int double_colon = -1;          /* index of the first 16-bit
                                   * group of zeros represented
                                   * by the double colon */
   int double_colon_length = 1;    /* use double colon only if
                                   * there are two or more 16-bit
                                   * groups of zeros */
   int zero_length;
   int section;
   unsigned int val;

   /* Scan to find the placement of the double colon */
   for (section = 0; section < 8; section++) {
      if (addr->pr_s6_addr16[section] == 0) {
         zero_length = 1;
         section++;
         while (section < 8 && addr->pr_s6_addr16[section] == 0) {
            zero_length++;
            section++;
         }
         /* Select the longest sequence of zeros */
         if (zero_length > double_colon_length) {
            double_colon = section - zero_length;
            double_colon_length = zero_length;
         }
      }
   }

   /* Now start converting to a string */
   section = 0;

   if (double_colon == 0) {
      if (double_colon_length == 6 ||
         (double_colon_length == 5 && addr->pr_s6_addr16[5] == 0xffff)) {
            /* ipv4 format address */
            STUFF(':');
            STUFF(':');
            if (double_colon_length == 5) {
               STUFF('f');
               STUFF('f');
               STUFF('f');
               STUFF('f');
               STUFF(':');
            }
            if (addr->pr_s6_addr[12] > 99) STUFF(addr->pr_s6_addr[12]/100 + '0');
            if (addr->pr_s6_addr[12] > 9) STUFF((addr->pr_s6_addr[12]%100)/10 + '0');
            STUFF(addr->pr_s6_addr[12]%10 + '0');
            STUFF('.');
            if (addr->pr_s6_addr[13] > 99) STUFF(addr->pr_s6_addr[13]/100 + '0');
            if (addr->pr_s6_addr[13] > 9) STUFF((addr->pr_s6_addr[13]%100)/10 + '0');
            STUFF(addr->pr_s6_addr[13]%10 + '0');
            STUFF('.');
            if (addr->pr_s6_addr[14] > 99) STUFF(addr->pr_s6_addr[14]/100 + '0');
            if (addr->pr_s6_addr[14] > 9) STUFF((addr->pr_s6_addr[14]%100)/10 + '0');
            STUFF(addr->pr_s6_addr[14]%10 + '0');
            STUFF('.');
            if (addr->pr_s6_addr[15] > 99) STUFF(addr->pr_s6_addr[15]/100 + '0');
            if (addr->pr_s6_addr[15] > 9) STUFF((addr->pr_s6_addr[15]%100)/10 + '0');
            STUFF(addr->pr_s6_addr[15]%10 + '0');
            STUFF('\0');
            return str;
      }
   }

   while (section < 8) {
      if (section == double_colon) {
         STUFF(':');
         STUFF(':');
         section += double_colon_length;
         continue;
      }
      val = NTOHS(addr->pr_s6_addr16[section]);
      if (val > 0xfff) {
         STUFF(basis_hex[val >> 12]);
      }
      if (val > 0xff) {
         STUFF(basis_hex[(val >> 8) & 0xf]);
      }
      if (val > 0xf) {
         STUFF(basis_hex[(val >> 4) & 0xf]);
      }
      STUFF(basis_hex[val & 0xf]);
      section++;
      if (section < 8 && section != double_colon) STUFF(':');
   }
   STUFF('\0');
   return str;
#undef STUFF
}




CLASS_DECL_c bool from_string(in_addr * addr, const char * string)
{
   
   stra_dup stra;
   
   stra.add_tokens(string, ".");
   
   if(stra.get_count() != 4)
      return false;
   
   int i1 = atoi_dup(stra[0]);

   if(i1 < 0 || i1 > 255)
      return false;

   int i2 = atoi_dup(stra[1]);

   if(i2 < 0 || i2 > 255)
      return false;

   int i3 = atoi_dup(stra[2]);

   if(i3 < 0 || i3 > 255)
      return false;

   int i4 = atoi_dup(stra[3]);
   
   if(i4 < 0 || i4 > 255)
      return false;

   addr->S_un.S_un_b.s_b1 = i1;

   addr->S_un.S_un_b.s_b2 = i2;

   addr->S_un.S_un_b.s_b3 = i3;

   addr->S_un.S_un_b.s_b4 = i4;

   addr->S_un.S_addr = HTONL(addr->S_un.S_addr);

   return true;

}


CLASS_DECL_c vsstring to_string(const in_addr * addrParam)
{
   
   in_addr addr;

   addr.S_un.S_addr = NTOHL(addrParam->S_un.S_addr);

   vsstring str;

   str += itoa_dup(addr.S_un.S_un_b.s_b1);

   str += ".";

   str += itoa_dup(addr.S_un.S_un_b.s_b2);

   str += ".";

   str += itoa_dup(addr.S_un.S_un_b.s_b3);

   str += ".";

   str += itoa_dup(addr.S_un.S_un_b.s_b4);

   return str;
   
}


CLASS_DECL_c int c_inet_pton(int af, const char *src, void *dst)
{
   
   if(af == AF_INET)
   {

      in_addr * addr = (in_addr *) dst;

      if(!from_string(addr, src))
         return 0;

      return 1;

   }
   else if(af == AF_INET6)
   {

      in6_addr * addr = (in6_addr *) dst;

      if(!from_string(addr, src))
         return 0;

      return 1;

   }
   else
   {

      return 0;

   }

}


CLASS_DECL_c vsstring c_inet_ntop(int af, const void *src)
{

   vsstring str;
   
   if(af == AF_INET)
   {

      in_addr * addr = (in_addr *) src;

      str = to_string(addr);

   }
   else if(af == AF_INET6)
   {

      in6_addr * addr = (in6_addr *) src;

      str = to_string(addr);

   }

   return true;

}

CLASS_DECL_c const char * c_inet_ntop(int af, const void *src, char *dst, int cnt)
{

   if(dst == NULL)
      return NULL;

   vsstring str = c_inet_ntop(af, src);

   if(str.is_empty())
      return NULL;

   if(str.get_length() > cnt)
      return NULL;

   strcpy(dst, str);

   return dst;

}

#define C_INADDR_NONE ((unsigned long ) -1)

CLASS_DECL_c unsigned long c_inet_addr(const char * src)
{

   stra_dup stra;
   
   stra.add_tokens(src, ".");
   
   if(stra.get_count() > 4)
      return C_INADDR_NONE;

   if(stra.get_count() == 1)
   {

      return HTONL(c_inet_to_ui(src));

   }
   else
   {

      in_addr addr;

      unsigned long ul;

      if(stra.get_count() == 2)
      {

         ul = c_inet_to_ui(stra[0]);

         if(ul > 255)
            return C_INADDR_NONE;

         addr.S_un.S_un_b.s_b1 = (byte) ul;

         ul = c_inet_to_ui(stra[1]);

         if((ul & 0xff000000u) != 0)
            return C_INADDR_NONE;

         addr.S_un.S_un_b.s_b2 = ul & 0xFF;

         addr.S_un.S_un_b.s_b3 = (ul >> 8) & 0xFF;

         addr.S_un.S_un_b.s_b4 = (ul >> 16) & 0xFF;

      }
      else if(stra.get_count() == 3)
      {

         ul = c_inet_to_ui(stra[0]);

         if(ul > 255)
            return C_INADDR_NONE;

         addr.S_un.S_un_b.s_b1 = (byte) ul;

         ul = c_inet_to_ui(stra[1]);

         if(ul > 255)
            return C_INADDR_NONE;

         addr.S_un.S_un_b.s_b2 = (byte) ul;

         ul = c_inet_to_ui(stra[1]);

         if((ul & 0xffff0000u) != 0)
            return C_INADDR_NONE;

         addr.S_un.S_un_b.s_b2 = ul & 0xFF;

         addr.S_un.S_un_b.s_b4 = (ul >> 8) & 0xFF;

      }
      else if(stra.get_count() == 4)
      {

         if(from_string(&addr, src))
            return C_INADDR_NONE;

         return addr.S_un.S_addr;

      }
      else
      {

         throw "not expected";

      }

      return HTONL(addr.S_un.S_addr);

   }
   

}

CLASS_DECL_c vsstring c_gethostbyname(const char * hostname)
{

#ifdef BSD_STYLE_SOCKETS

   struct hostent * pentry = gethostbyname(hostname);

   return c_inet_ntop(pentry->h_addrtype, pentry->h_addr_list[0]);

#else

   return vsstring((((ref new ::Windows::Networking::HostName(rtstr(hostname)))->DisplayName))->Begin());

#endif


}