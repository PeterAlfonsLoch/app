#include "framework.h"


namespace ca
{


   namespace html
   {


      html::html()
      {

      }


      html::~html()
      {

      }


      bool html::initialize()
      {

         if(Application.is_cube())
         {
            System.factory().creatable_small < html_document > ();
            System.factory().creatable_small < html_child_frame > ();
            System.factory().creatable_small < html_frame > ();
            System.factory().creatable_small < html_view > ();
            System.factory().creatable_small < ::html::data::image > ();
            System.factory().creatable_small < ::html::data > ();
         }

         if(!::html::html::initialize())
            return false;

         return true;

      }


   } // namespace html


} // namespace ca



