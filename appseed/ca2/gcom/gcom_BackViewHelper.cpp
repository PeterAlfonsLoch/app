#include "StdAfx.h"


namespace gcom
{

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

} // namespace gcom
