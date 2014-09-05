// http://www.beedub.com/Sprite093/src/lib/c/etc/gcvt.c


//#if defined(LIBC_SCCS) && !defined(lint)
//static char sccsid[] = "@(#)gcvt.c	5.2 (Berkeley) 3/9/86";
//#endif LIBC_SCCS and not lint

/*
* gcvt  - Floating output conversion to minimal length string
*/


#define p2walk(ch) if(nchar <= 0) return NULL; if(nchar <= 1) {*p2 = '\0'; return buf;}  *p2 = ch; p2++; nchar--;

char * gcvt_dup(char * buf,int nchar, double arg,int ndigit)
{

   int sign,decpt;
   char p1[128];
   char * p2 = buf;
   int i;

   ecvt_dup(p1, 128, arg,ndigit,&decpt,&sign);
   p2 = buf;
   if(sign)
      *p2++ = '-';
   for(i=ndigit - 1; i>0 && p1[i] == '0'; i--)
      ndigit--;
   if(decpt >= 0 && decpt - ndigit > 4
      || decpt < 0 && decpt < -3) { /* use E-style */
      decpt--;
      p2walk(*p1++);
      p2walk('.');
      for(i=1; i<ndigit; i++)
         p2walk(*p1++);
      p2walk('e');
      if(decpt<0)
      {
         decpt = -decpt;
         p2walk('-');
      }
      else
      {
         p2walk('+');
      }
      p2walk(decpt / 10 + '0');
      p2walk(decpt % 10 + '0');
   }
   else
   {
      if(decpt <= 0)
      {
         if(*p1 != '0')
            p2walk('.');
         while(decpt<0)
         {
            decpt++;
            p2walk('0');
         }
      }
      for(i=1; i <= ndigit; i++)
      {
         p2walk(*p1++);
         if(i == decpt)
            p2walk('.');
      }
      if(ndigit<decpt)
      {
         while(ndigit++<decpt)
            p2walk('0');
         p2walk('.');
      }
   }
   if(p2[-1] == '.')
      p2--;
   *p2 = '\0';
   return buf;
}
