#include "framework.h"


namespace gen
{


   namespace str
   {


      void format(string_format * pformat, char const & ch)
      {

         pformat->append(string((char) ch));

      }


      void format(string_format * pformat, uchar const & uch)
      {

         pformat->append(string((char) uch));

      }


      void format(string_format * pformat, int16_t const & sh)
      {

         pformat->append(gen::str::from((int32_t) sh));

      }


      void format(string_format * pformat, uint16_t const & ush)
      {

         pformat->append(gen::str::from((uint32_t) ush));

      }


      void format(string_format * pformat, int32_t const & i)
      {
         // TODO: use specs
         pformat->append(gen::str::from(i));

      }

      void format(string_format * pformat, uint32_t const & ui)
      {
         // TODO: use specs
         pformat->append(gen::str::from(ui));

      }

      void format(string_format * pformat, int64_t const & i)
      {
         // TODO: use specs
         pformat->append(gen::str::from(i));

      }

      void format(string_format * pformat, uint64_t const & i)
      {
         // TODO: use specs
         pformat->append(gen::str::from(i));

      }

      void format(string_format * pformat, float const & f)
      {
         // TODO: use specs
         pformat->append(gen::str::from(f));

      }

      void format(string_format * pformat, double const & d)
      {
         // TODO: use specs
         pformat->append(gen::str::from(d));

      }



      void format(string_format * pformat, const void * const & p)
      {
         // TODO: use specs
         pformat->append(gen::str::from((uint_ptr)p));

      }

      void format(string_format * pformat, void * const & p)
      {
         // TODO: use specs
         pformat->append(gen::str::from((uint_ptr)p));

      }

      void format(string_format * pformat, const char * const & psz)
      {

         pformat->append(psz);

      }

      void format(string_format * pformat, unsigned char * const & psz)
      {

         pformat->append((const char *) psz);

      }






   } // namespace str


} // namespace gen



