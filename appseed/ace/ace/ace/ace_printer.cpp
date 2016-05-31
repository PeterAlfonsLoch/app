//#include "framework.h" // previously ace/user/user.h


namespace ace
{


   printer::printer(::ace::application * papp) :
      object(papp)
   {
   }

   printer::~printer()
   {
      close();
   }

   bool printer::open(const char * pszDeviceName)
   {
      UNREFERENCED_PARAMETER(pszDeviceName);
      return false;
   }

   ::draw2d::graphics * printer::create_graphics()
   {
      return NULL;
   }

   bool printer::is_opened()
   {
      return false;
   }

   bool printer::close()
   {
      return true;
   }


} // namespace user













































