#include "framework.h"


namespace turboc
{


   main::main(::aura::application * papp) :
      ::thread(papp)
   {

      m_pfnMain = NULL;

   }


   main::~main()
   {

   }


   int32_t main::run()
   {

      m_iReturnCode = 0;

      ASSERT(m_pfnMain != NULL);

      try
      {

         m_pfnMain();

      }
      catch(...)
      {

         m_iReturnCode = -1;

      }

      System.post_thread_message(WM_QUIT);

      return m_iReturnCode;

   }


} // namespace userstack



