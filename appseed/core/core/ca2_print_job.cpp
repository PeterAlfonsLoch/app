#include "framework.h"


namespace ca2
{


   print_job::print_job(sp(base_application) papp) :
      element(papp),
      ::ca2::job(papp)
   {
      m_iPageStart = -1;
      m_iPageCount = -1;
      m_iPrintingPage = 0;
   }

   print_job::~print_job()
   {
   }


} // namespace ca2
