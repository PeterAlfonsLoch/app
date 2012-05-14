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
         System.factory().creatable_small < html::data::image > ();
         System.factory().creatable_small < html::data > ();
      }

      m_phtmlex = new class html_ex(this);
      if(m_phtmlex == NULL)
         return false;
      
      if(!::userbase::application::initialize())
         return false;



      return true;
   }


   html_ex & application::html_ex()
   {
      return *m_phtmlex;
   }

} // namespace html