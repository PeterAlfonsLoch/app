#pragma once

// hotplugin
// interface for a hot plugin
// hot plugin - a plugin that can easily change underlying plugin implementation
//
// hot plugin plugin - represents plugin interface
// hot plugin host - is a plugin - also - that can host a plugin by forwarding calls


#include "hotplugin_plugin.h"
#include "hotplugin_host.h"

typedef ::hotplugin::plugin * (* FN_NEW_HOTPLUGIN)();


namespace hotplugin
{

   enum e_message
   {

      message_init = 1984,
      message_set_window,
      message_paint,
      message_message,
      message_set_ready,

   };


   class CLASS_DECL_c container_launcher :
      virtual public ::launcher
   {
   public:

      vsstring m_strChannel;

      container_launcher(const char * pszChannel);
         
      virtual bool ensure_executable() { return true; }

      vsstring get_params();

      virtual vsstring get_executable_path();

   };


} // namespace ca2plugin_container