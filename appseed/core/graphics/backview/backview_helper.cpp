#include "framework.h"


namespace backview
{

   Helper::Helper(Main & main) :
      m_main(main)
   {
   }


   Main & Helper::HelperGetMain()
   {
      return m_main;
   }

} // namespace backview




