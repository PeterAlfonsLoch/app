#include "StdAfx.h"
#include "application_interface.h"

#include "MixerVisualCentral.h"
#include "MixerControlView.h"

namespace mixeruserbase
{

   application_interface::application_interface()
   {
      m_pvisualcentral = NULL;
   }

   application_interface::~application_interface()
   {
   }

   void application_interface::on_application_signal(::ca::application::signal_object * pobj)
   {
      mixer::application_interface::on_application_signal(pobj);
      if(pobj->m_esignal == ::ca::application::signal_initialize1)
      {
         System.factory().creatable_small < GoodMixerDoc >();
         System.factory().creatable_small < MixerMainView >();
         System.factory().creatable_small < MixerControlView >();
      }
      else if(pobj->m_esignal == ::ca::application::signal_initialize)
      {
         m_pvisualcentral = new MixerVisualCentral(get_app());
         if(m_pvisualcentral == NULL)
         {
            TRACE("no primitive::memory to initialize MixerVisualCentral");
            pobj->m_bOk = false;
            pobj->m_bRet = true;
            return;
         }
      }
      else if(pobj->m_esignal == ::ca::application::signal_exit_instance)
      {
         if(m_pvisualcentral != NULL)
         {
            delete m_pvisualcentral;
            m_pvisualcentral = NULL;
         }
      }
   }

   MixerVisualCentral & application_interface::GetMixerVisualCentral()
   {
      return * m_pvisualcentral;
   }



} // namespace mixeruserbase