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


   } // namespace str


} // namespace gen



