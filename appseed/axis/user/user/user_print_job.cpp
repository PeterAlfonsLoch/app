//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"




namespace user
{


   print_job::print_job(::aura::application * papp) :
      ::object(papp),
      ::job(papp),
      ::user::job(papp),
      thread(papp)
   {

      m_iPageStart = -1;
      m_iPageCount = -1;
      m_iPrintingPage = 0;
   }


   print_job::~print_job()
   {

   }


   int32_t print_job::run()
   {

      ::exception::throw_interface_only(get_app());

      return -1;

   }

} // namespace user




