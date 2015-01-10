#include "framework.h"
//#include "src/turboc.h"


namespace turboc
{


   application::application()
   {


   }

   application::~application()
   {

   }

   bool application::initialize_instance()
   {

      m_pcontext = new context(this);

      if(!::console::application::initialize_instance())
         return false;

      return true;

   }


   bool application::start_main(PFN_MAIN pfnMain)
   {

      if(m_pmain != NULL)
      {

         return false;

      }

      m_pmain = new ::turboc::main(this);

      m_pmain->m_pfnMain = pfnMain;

      m_pmain->begin();


      return true;

   }


} // namespace turboc