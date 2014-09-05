// http://www.beedub.com/Sprite093/src/lib/c/etc/gcvt.c
//#if defined(LIBC_SCCS) && !defined(lint)
//static char sccsid[] = "@(#)gcvt.c	5.2 (Berkeley) 3/9/86";
//#endif LIBC_SCCS and not lint

/*
* gcvt  - Floating output conversion to minimal length string
*/

#include "framework.h"


#define GCVTBUFSIZE 2 * DBL_MAX_10_EXP + 33

char * gcvt_internal(double number,int ndigit, char * buf)
{
   int sign,decpt;
   char sz[GCVTBUFSIZE];
   register char *p1;
   register char *p2;
   register int i;

   ecvt_dup(sz,GCVTBUFSIZE,  number,ndigit,&decpt,&sign);
   p1 = sz;
   p2 = buf;
   if(sign)
      *p2++ = '-';
   for(i=ndigit - 1; i>0 && p1[i] == '0'; i--)
      ndigit--;
   if(decpt >= 0 && decpt - ndigit > 4
      || decpt < 0 && decpt < -3) { /* use E-style */
      decpt--;
      *p2++ = *p1++;
      *p2++ = '.';
      for(i=1; i<ndigit; i++)
         *p2++ = *p1++;
      *p2++ = 'e';
      if(decpt<0) {
         decpt = -decpt;
         *p2++ = '-';
      }
      else
         *p2++ = '+';
      *p2++ = decpt / 10 + '0';
      *p2++ = decpt % 10 + '0';
   }
   else {
      if(decpt <= 0) {
         if(*p1 != '0')
            *p2++ = '.';
         while(decpt<0) {
            decpt++;
            *p2++ = '0';
         }
      }
      for(i=1; i <= ndigit; i++) {
         *p2++ = *p1++;
         if(i == decpt)
            *p2++ = '.';
      }
      if(ndigit<decpt) {
         while(ndigit++<decpt)
            *p2++ = '0';
         *p2++ = '.';
      }
   }
   if(p2[-1] == '.')
      p2--;
   *p2 = '\0';
   return(buf);
}




int gcvt_dup(char *buf,int nchar,double arg,int ndigits)
{

   char sz[GCVTBUFSIZE + 9];

   gcvt_internal(arg,ndigits,sz);

   if(strlen(sz) > nchar)
      return EINVAL;

   strcpy(buf,sz);

   return 0;

}



