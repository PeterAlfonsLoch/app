#include "framework.h"
#include "src/turboc.h"


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


} // namespace turboc