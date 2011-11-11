#include "StdAfx.h"
#include "mixeruserbase_application_interface.h"
#include "mixeruserbase_central.h"
#include "mixeruserbase_control_view.h"
#include "mixeruserbase_frame_window.h"

namespace mixeruserbase
{

   application_interface::application_interface()
   {
      m_pcentral = NULL;
   }

   application_interface::~application_interface()
   {
   }

   void application_interface::on_application_signal(::radix::application_signal_object * pobj)
   {
      mixer::application_interface::on_application_signal(pobj);
      if(pobj->m_esignal == ::ca::application_signal_initialize1)
      {
         if(App(dynamic_cast < ::ca::application * >(this)).is_bergedge())
         {
            System.factory().creatable_small < document >();
            System.factory().creatable_small < main_view >();
            System.factory().creatable_small < control_view >();
            System.factory().creatable_small < frame_window >();
         }
      }
      else if(pobj->m_esignal == ::ca::application_signal_initialize)
      {
         if(App(dynamic_cast < ::ca::application * >(this)).is_bergedge())
         {
            m_pcentral = new central(&App(dynamic_cast < ::ca::application * >(this)));
            if(m_pcentral == NULL)
            {
               TRACE("no primitive::memory to initialize MixerVisualCentral");
               pobj->m_bOk = false;
               pobj->m_bRet = true;
               return;
            }
            if(!m_pcentral->Initialize(&App(dynamic_cast < ::ca::application * >(this))))
            {
               TRACE("could not initialize mixer visual central");
               pobj->m_bOk = false;
               pobj->m_bRet = true;
               return;
            }
         }
      }
      else if(pobj->m_esignal == ::ca::application_signal_exit_instance)
      {
         if(App(dynamic_cast < ::ca::application * >(this)).is_bergedge())
         {
            if(m_pcentral != NULL)
            {
               delete m_pcentral;
               m_pcentral = NULL;
            }
         }
      }
   }

   central & application_interface::get_mixeruserbase_central()
   {
      return * m_pcentral;
   }



} // namespace mixeruserbase