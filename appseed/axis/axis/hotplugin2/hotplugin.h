#pragma once


// hotplugin
// interface for a hot plugin
// hot plugin - a plugin that can easily change underlying plugin implementation
//
// hot plugin plugin - represents plugin interface
// hot plugin host - is a plugin - also - that can host a plugin by forwarding calls


namespace hotplugin
{

   
   class composer;


} // namespace hotplugin


#include "hotplugin_plugin.h"
#include "hotplugin_host.h"
#include "hotplugin_container_launcher.h"
#include "hotplugin_composer.h"

typedef ::hotplugin::plugin * (* FN_NEW_HOTPLUGIN)();


namespace hotplugin
{


   enum e_message
   {
      
      message_alive = 1977,
      message_init = 1984,
      message_set_window,
      message_paint,
      message_message,
      message_set_ready,
      message_set_installing,
      message_open_url,
      message_set_plugin_url

   };



   CLASS_DECL_AXIS ::axis::system * get_base_system();

   CLASS_DECL_AXIS bool start_base_system();
   CLASS_DECL_AXIS void stop_base_system();


#ifdef WINDOWS

   // hotplugin plugin dll HINSTANCE
   CLASS_DECL_AXIS HINSTANCE get_hinstance();
   CLASS_DECL_AXIS void set_hinstance(HINSTANCE hinstance);
   CLASS_DECL_AXIS void entry_hall_windows_on_paint(HDC hdc,const RECT & rect,const string & strEntryHallText);

#endif

} // namespace ca2plugin_container



