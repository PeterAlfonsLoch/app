#include "framework.h"



#ifdef VARIADIC_TEMPLATE


#ifdef APPLEOS

//#include <stdlib.h>

#endif


void string_format::construct(string_format_printer * pprinter, string_format_printer::PRINTER pfnPrinter, void * pvoidPrinter)
{

   m_pszBuffer                   = NULL;
   m_iSize                       = 0;
   m_iLength                     = 0;

   m_pprinter                    = pprinter;
   m_pfnPrinter                  = pfnPrinter;
   m_pvoidPrinter                = pvoidPrinter;

   m_estate                      = state_initial;

   m_bLeftJustify                = false;
   m_bForceShowSign              = false;
   m_bSharp                      = false;
   m_bZeroPadding                = false;


   m_iWidth                      = -1;
   m_iPrecision                  = -1;
   m_chLength                    = '\0';
   m_chSpec                      = '\0';

}


string_format::~string_format()
{

   if(m_pszBuffer != NULL)
   {

      memory_free(m_pszBuffer);

   }

}


void string_format::allocate_add_up(strsize iLenAddUp)
{

   strsize iNewSize;

   if(m_iSize <= 0)
   {

      iNewSize = ((iLenAddUp + 1 + 1023) & ~1023);

   }
   else
   {

      iNewSize = ((m_iLength + iLenAddUp + 1 + 1023) & ~1023);

      if(iNewSize < m_iSize)
      {

         return;

      }

   }

   if(iNewSize != m_iSize)
   {

      if(m_pszBuffer == NULL)
      {

         m_pszBuffer = (char *) memory_alloc(iNewSize);

      }
      else
      {

         m_pszBuffer = (char *) memory_realloc(m_pszBuffer, iNewSize);

      }

      m_iSize = iNewSize;

   }

   if(m_pszBuffer == NULL)
      throw memory_exception(get_thread_app());


   memset(&m_pszBuffer[m_iLength], 0, m_iSize - m_iLength);

}




bool string_format::parse(const char * & s)
{
   if(m_estate == state_initial)
   {
      while(*s != '\0')
      {
         if(*s == '-')
         {
            m_bLeftJustify = true;
         }
         else if(*s == '+')
         {
            m_bForceShowSign = true;
         }
         else if(*s == '#')
         {
            m_bSharp = true;
         }
         else if(*s == '0')
         {
            m_bZeroPadding = true;
         }
         else
         {
            break;
         }
         s++;
      }
      if(*s == '\0')
      {
         throw simple_exception(get_thread_app(), "unfineshed argument specifier");
      }
      const char * start = s;
      while(*s != '\0')
      {
         if(*s == '*')
         {
            s++;
            m_estate = state_waiting_width;
            return true;
         }
         else if(isdigit_dup(*s))
         {
         }
         else
         {
            break;
         }
         s++;
      }
      if(*s == '\0')
      {
         throw simple_exception(get_thread_app(), "unfineshed argument specifier");
      }
      if(s > start)
      {
         m_iWidth = (int32_t) natoi_dup(start, s - start);
      }
      m_estate = state_parse_precision;
   }
   if(m_estate == state_parse_precision)
   {
      if(*s == '.')
      {
         s++;
      }
      const char * start = s;
      while(*s != '\0')
      {
         if(*s == '*')
         {
            s++;
            m_estate = state_waiting_precision;
            return true;
         }
         else if(isdigit_dup(*s))
         {
         }
         else
         {
            break;
         }
         s++;
      }
      if(*s == '\0')
      {
         throw simple_exception(get_thread_app(), "unfineshed argument specifier");
      }
      if(s > start)
      {
         m_iPrecision = natoi_dup(start, s - start);
      }
      m_estate = state_parse_length;
   }
   if(m_estate == state_parse_length)
   {
      if(*s == 'l' || *s == 'L' || *s == 'h')
      {
         m_chLength = *s;
         s++;
      }
      if(*s == '\0')
      {
         throw simple_exception(get_thread_app(), "unfineshed argument specifier");
      }
      if(*s == 'c' || *s == 'd' || *s == 'i'
      || *s == 'e' || *s == 'E' || *s == 'f'
      || *s == 'g' || *s == 'G' || *s == 'o'
      || *s == 'g' || *s == 'G' || *s == 's'
      || *s == 'u' || *s == 'x' || *s == 'X'
      || *s == 'p')
      {
         m_chLength = *s;
         s++;
      }
      else
      {
         throw simple_exception(get_thread_app(), "unfineshed format specifier");
      }
      return false;
   }
   else
   {
      throw "invalid state";
   }


}



   namespace str
   {


      void format(string_format * pformat, char const & ch)
      {

         if(pformat->m_chLength == 'X')
         {

            string str = ::hex::upper_from((void *) &ch, 1);

            while(pformat->m_iWidth > str.get_length())
            {
               str = "0" + str;
            }

            pformat->append(str);

         }
         else
         {

            pformat->append(string((char) ch));

         }

      }


      void format(string_format * pformat, uchar const & uch)
      {

         pformat->append(string((char) uch));

      }


      void format(string_format * pformat, int16_t const & sh)
      {

         pformat->append(::str::from((int32_t) sh));

      }


      void format(string_format * pformat, uint16_t const & ush)
      {

         pformat->append(::str::from((uint32_t) ush));

      }


      void format(string_format * pformat, int32_t const & i)
      {
         // TODO: use specs
         string str = ::str::from(i);
         if(pformat->m_bZeroPadding)
         {
            while(str.get_length() < pformat->m_iWidth)
            {
                str = "0" + str;
            }
         }
         pformat->append(str);

      }

      void format(string_format * pformat, uint32_t const & ui)
      {
         // TODO: use specs
         pformat->append(::str::from(ui));

      }

      void format(string_format * pformat, int64_t const & i)
      {
         // TODO: use specs
         pformat->append(::str::from(i));

      }

      void format(string_format * pformat, uint64_t const & i)
      {
         // TODO: use specs
         pformat->append(::str::from(i));

      }

      void format(string_format * pformat, float const & f)
      {
         // TODO: use specs
         pformat->append(::str::from(f));

      }

      void format(string_format * pformat, double const & d)
      {
         // TODO: use specs
         char sz[1024];
         int decimal_point;
         int negative;
         if(pformat->m_iPrecision >= 0)
         {
#if defined(ANDROID)
            //throw 3;
//             if(fcvt(d, pformat->m_iPrecision, &decimal_point, &negative, sz, sizeof(sz)) == -1)
             {
                sprintf(sz, "%f", d);
                //pformat->append(::str::from(d));
                //return;
             }
#elif defined(APPLEOS)

            char * sz2 = fcvt(d, pformat->m_iPrecision, &decimal_point, &negative);

            if(sz2 == NULL)
            {
               pformat->append(::str::from(d));
               return;
            }

            strcpy(sz, sz2);

#else
             if(fcvt_r(d, pformat->m_iPrecision, &decimal_point, &negative, sz, sizeof(sz)) == -1)
             {
                pformat->append(::str::from(d));
                return;
             }

#endif
             string str(sz);
             string strResult;

             if(negative)
             {
                 strResult = "-";
             }
             else if(pformat->m_bForceShowSign)
             {
                strResult = "+";
             }

             strResult += str.substr(0, decimal_point);
             if(pformat->m_iPrecision > 0 && decimal_point > str.get_length())
             {
                strResult += ".";
                strResult += str.substr(decimal_point);
             }



            pformat->append(strResult);

         }
         else
         {
#ifdef ANDROID
//             if(ecvt_r(d, sizeof(sz), &decimal_point, &negative, sz, sizeof(sz)) == -1)
             {
                sprintf(sz, "%f", d);
    //            pformat->append(::str::from(d));
  //              return;
             }

#elif defined(APPLEOS)

            char * sz2 = ecvt(d, sizeof(sz), &decimal_point, &negative);

            if(sz2 == NULL)
            {
               pformat->append(::str::from(d));
               return;
            }

            strcpy(sz, sz2);

#else
             if(ecvt_r(d, sizeof(sz), &decimal_point, &negative, sz, sizeof(sz)) == -1)
             {
                pformat->append(::str::from(d));
                return;
             }
#endif
             string str(sz);
             string strResult;

             if(negative)
             {
                 strResult = "-";
             }
             else if(pformat->m_bForceShowSign)
             {
                strResult = "+";
             }

             strResult += str.substr(0, decimal_point);
             if(decimal_point > str.get_length())
             {
                strResult += ".";
                strResult += str.substr(decimal_point);
             }



            pformat->append(strResult);

         }



      }



      void format(string_format * pformat, const void * const & p)
      {
         // TODO: use specs
         pformat->append(::str::from((uint_ptr)p));

      }

      void format(string_format * pformat, void * const & p)
      {
         // TODO: use specs
         pformat->append(::str::from((uint_ptr)p));

      }

      void format(string_format * pformat, const char * const & psz)
      {

         pformat->append(psz);

      }

      void format(string_format * pformat, unsigned char * const & psz)
      {

         pformat->append((const char *) psz);

      }



      void format(string_format * pformat, string const & str)
      {

         pformat->append(str);

      }



      void format(string_format * pformat, lparam const & lparam)
      {

          ::str::format(pformat, (int_ptr)lparam.m_lparam);

      }

   } // namespace str




#endif
