#include "framework.h"
#include  "windows_system_interaction_impl.h"

namespace base
{

   system_interaction_impl::system_interaction_impl(::aura::application * papp):
      ::object(papp),
      ::user::interaction(papp)
   {

   }

   system_interaction_impl::~system_interaction_impl()
   {


   }

   void system_interaction_impl::install_message_handling(::message::dispatch * pdispatch)
   {

      ::user::interaction::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_SETTINGCHANGE,pdispatch,this,&system_interaction_impl::_001MessageHub);
      IGUI_WIN_MSG_LINK(WM_DISPLAYCHANGE,pdispatch,this,&system_interaction_impl::_001MessageHub);

   }

   void system_interaction_impl::_001MessageHub(signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj);

      if(pbase != NULL)
      {

         if(pbase->m_uiMessage == WM_DISPLAYCHANGE ||
            (pbase->m_uiMessage == WM_SETTINGCHANGE &&
            (pbase->m_wparam == SPI_SETWORKAREA)))
         {

            System.enum_display_monitors();

            ::user::interaction * pui = NULL;

            while(System.get_frame(pui))
            {

               try
               {

                  pui->post_message(WM_APP + 1984 + 21);

               }
               catch(...)
               {
               }

            }


         }

      }

   }



} // namespace base


