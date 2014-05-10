#include "framework.h"
#include "plugin_instance.h"

::hotplugin::plugin * new_hotplugin(sp(base_application) papp);


namespace plugin
{


   instance::instance(sp(base_application) papp) :
      element(papp),
      hotplugin::plugin(papp),
      ::simple_ui::style(papp),
      ::user::interaction(papp),
      plugin(papp)
   {

      m_pfile           = NULL;

//      m_lpbMemory       = NULL;

  //    m_iMemory         = -1;

      m_puiHost         = NULL;

      m_oswindow        = NULL;

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

      m_oswindow = NULL;

      m_bInitialized = false;

   }


   host_interaction * instance::create_host_interaction()
   {

      host_interaction * pinteraction = new host_interaction(get_app());

      pinteraction->create_message_queue("npca2");

      pinteraction->m_bMessageWindow = false;

      pinteraction->m_pimpl->m_bMessageWindow = false;

      pinteraction->install_message_handling(pinteraction->m_pimpl);

      ::window_sp pwindow = pinteraction->m_pimpl;

      pwindow->m_bTranslateMouseMessageCursor = false;

      return pinteraction;

   }


} // namespace plugin




::hotplugin::plugin * new_hotplugin(sp(base_application) papp)
{

   return new ::plugin::instance(papp);

}

