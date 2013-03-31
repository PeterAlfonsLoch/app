#include "framework.h"
#include "plugin_instance.h"

::hotplugin::plugin * new_hotplugin();


namespace plugin
{


   instance::instance()
   {

      m_pfile           = NULL;

      m_lpbMemory       = NULL;

      m_iMemory         = -1;

      m_puiHost         = NULL;

      m_oswindow        = ::ca::null();

      m_bStream         = false;

   }

   instance::~instance()
   {
      if(m_puiHost != NULL)
      {
         delete m_puiHost;
      }

   }


   bool instance::initialize()
   {

      m_oswindow = m_phost->get_host_window();

      if(m_oswindow == NULL)
         return FALSE;

      m_bInitialized = true;

      //NPN_GetValue(m_instance, NPNVnetscapeWindow, &m_oswindow);

      start_ca2_system();

      return TRUE;

   }


   void instance::shut()
   {

      //::KillTimer(NULL, (uint_ptr) this);

      plugin::finalize();

      m_oswindow = ::ca::null();

      m_bInitialized = false;

   }


   host_interaction * instance::create_host_interaction()
   {

      host_interaction * pinteraction = new host_interaction(m_psystem);

      pinteraction->create_message_window("npca2");

      ::ca::window * pwindow = dynamic_cast < ::ca::window * > (pinteraction->m_pimpl.m_p);

      pwindow->m_bTranslateMouseMessageCursor = false;

      return pinteraction;

   }


} // namespace plugin


::hotplugin::plugin * new_hotplugin()
{

   return new ::plugin::instance();

}

