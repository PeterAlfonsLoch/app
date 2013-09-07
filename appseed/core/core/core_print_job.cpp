#include "framework.h"


namespace core
{


   print_job::print_job(sp(base_application) papp) :
      element(papp),
      ::core::job(papp)
   {
      m_iPageStart = -1;
      m_iPageCount = -1;
      m_iPrintingPage = 0;
   }

   print_job::~print_job()
   {
   }


} // namespace core
