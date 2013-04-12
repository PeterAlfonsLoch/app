#include "framework.h"
#include "plugin_instance.h"

::hotplugin::plugin * new_hotplugin();


namespace plugin
{


   instance::instance()
   {

      m_pfile           = ::null();

      m_lpbMemory       = ::null();

      m_iMemory         = -1;

      m_puiHost         = ::null();

      m_oswindow        = ::ca::null();

      m_bStream         = false;

   }

   instance::~instance()
   {
      if(m_puiHost != ::null())
      {
         delete m_puiHost;
      }

   }


   bool instance::initialize()
   {

      m_oswindow = m_phost->get_host_window();

      if(m_oswindow == ::null())
         return FALSE;

      m_bInitialized = true;

      //NPN_GetValue(m_instance, NPNVnetscapeWindow, &m_oswindow);

      start_ca2_system();

      return TRUE;

   }


   void instance::shut()
   {

      //::KillTimer(::null(), (uint_ptr) this);

      plugin::finalize();

      m_oswindow = ::ca::null();

      m_bInitialized = false;

   }


   host_interaction * instance::create_host_interaction()
   {

      host_interaction * pinteraction = new host_interaction(m_psystem);

      pinteraction->create_message_window("npca2");

      sp(::ca::window) pwindow = pinteraction->m_pimpl;

      pwindow->m_bTranslateMouseMessageCursor = false;

      return pinteraction;

   }


} // namespace plugin


::hotplugin::plugin * new_hotplugin()
{

   return new ::plugin::instance();

}

