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



