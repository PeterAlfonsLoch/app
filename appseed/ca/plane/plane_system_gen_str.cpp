#include "framework.h"


namespace gen
{


   namespace str
   {


      void format(string_format * pformat, int const & i)
      {
         // TODO: use specs
         pformat->append(gen::str::from(i));

      }

      void format(string_format * pformat, int64_t const & i)
      {
         // TODO: use specs
         pformat->append(gen::str::from(i));

      }

      void format(string_format * pformat, const void * const & p)
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

      void format(string_format * pformat, unsigned int const & ui)
      {
         // TODO: use specs
         pformat->append(gen::str::from(ui));

      }

      void format(string_format * pformat, long long const & ll)
      {
         // TODO: use specs
         pformat->append(gen::str::from(ll));

      }

      void format(string_format * pformat, float const & f)
      {
         // TODO: use specs
         pformat->append(gen::str::from(f));

      }

   } // namespace str


} // namespace gen



