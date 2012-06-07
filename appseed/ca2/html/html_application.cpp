#include "framework.h"

namespace html
{

   application::application()
   {
   }

   application::~application()
   {
   }

   bool application::initialize()
   {

      if(is_cube())
      {
         System.factory().creatable_small < html_document > ();
         System.factory().creatable_small < html_child_frame > ();
         System.factory().creatable_small < html_frame > ();
         System.factory().creatable_small < html_view > ();
         System.factory().creatable_small < ::html::data::image > ();
         System.factory().creatable_small < ::html::data > ();
      }

      if(!::userbase::application::initialize())
         return false;



      return true;
   }


} // namespace html