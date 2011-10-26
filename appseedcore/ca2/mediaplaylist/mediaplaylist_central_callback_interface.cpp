#include "StdAfx.h"


namespace mediaplaylist
{


   central_callback_interface::central_callback_interface()
   {

   }

   central_callback_interface::~central_callback_interface()
   {

   }

   void central_callback_interface::OnEvent(e_event eevent)
   {
      UNREFERENCED_PARAMETER(eevent);
   }


   ::mediaplaylist::document * central_callback_interface::OnBeforeOpenPlaylist()
   {
      return NULL;
   }


} // namespace mediaplaylist


