#include "framework.h"


namespace user
{


   print_job::print_job(sp(::aura::application) papp) :
      element(papp),
      ::print_job(papp),
      ::job(papp),
      ::user::job(papp),
      thread(papp)
   {

   }


   print_job::~print_job()
   {

   }


   int32_t print_job::run()
   {

      throw interface_only_exception(get_app());

      return -1;

   }

} // namespace user




