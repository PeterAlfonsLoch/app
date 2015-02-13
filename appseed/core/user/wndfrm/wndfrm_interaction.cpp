//#include "framework.h"


namespace user
{

   namespace wndfrm
   {


      interaction::interaction(::aura::application * papp) :
         object(papp)
      {
      }


      interaction::~interaction()
      {
      }


      void interaction::update()
      {
      }

      void interaction::get_frame_schema_list(stringa & stra)
      {

         UNREFERENCED_PARAMETER(stra);

      }

      sp(frame::frame) interaction::get_frame_schema(const char * pszSchema)
      {

         UNREFERENCED_PARAMETER(pszSchema);

         return NULL;

      }


   } // namespace wndfrm



} // namespace user





