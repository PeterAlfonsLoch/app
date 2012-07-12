#pragma once


// hotplugin
// interface for a hot plugin
// hot plugin - a plugin that can easily change underlying plugin implementation
//
// hot plugin plugin - represents plugin interface
// hot plugin host - is a plugin - also - that can host a plugin by forwarding calls


#include "hotplugin_plugin.h"
#include "hotplugin_host.h"
#include "hotplugin_container_launcher.h"


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

   };


} // namespace ca2plugin_container



