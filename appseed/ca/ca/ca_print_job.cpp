#include "framework.h"


namespace ca
{


   print_job::print_job(sp(::ca::application) papp) :
      ca(papp),
      ::ca::job(papp)
   {
      m_iPageStart = -1;
      m_iPageCount = -1;
      m_iPrintingPage = 0;
   }

   print_job::~print_job()
   {
   }


} // namespace ca