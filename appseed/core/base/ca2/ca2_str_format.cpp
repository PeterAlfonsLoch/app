#include "framework.h"


#ifndef NO_VARIADIC_TEMPLATE


namespace ca2
{


   namespace str
   {


      void format(string_format * pformat, char const & ch)
      {

         if(pformat->m_chLength == 'X')
         {

            string str = ::hex::hi_from((void *) &ch, 1);

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


      void format(string_format * pformat, calculator::value const & cval)
      {

         pformat->append(cval.to_string());

      }

      void format(string_format * pformat, lparam const & lparam)
      {

          ::str::format(pformat, lparam.m_lparam);

      }

   } // namespace str


} // namespace ca2


#endif



