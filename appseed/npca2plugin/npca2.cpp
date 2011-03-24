#include "StdAfx.h"
#include "plugin_instance.h"

#undef new

NPIdentifier sFoo_id;
NPIdentifier sBar_id;
NPIdentifier sDocument_id;
NPIdentifier sLocation_id;
NPIdentifier sBody_id;
NPIdentifier sCreateElement_id;
NPIdentifier sCreateTextNode_id;
NPIdentifier sAppendChild_id;
NPIdentifier sPluginType_id;
NPObject *sWindowObj;

void __cdecl _ca2_purecall(void)
{
    throw simple_exception();
}

//void on_npca2_detach();

HINSTANCE g_hinstance = NULL;

extern "C" NPError _NS_PluginInitialize()
{
   return NPERR_NO_ERROR;
}

extern "C" void _NS_PluginShutdown()
{
}

nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct)
{
  if(!aCreateDataStruct)
    return NULL;

  nsPluginInstance * plugin = (nsPluginInstance *) malloc(sizeof(nsPluginInstance));
  ::new (plugin) nsPluginInstance(aCreateDataStruct->instance);
  return plugin;
}

void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin)
{
   try
   {
      if(aPlugin)
         free(aPlugin);
   }
   catch(...)
   {
   }
}



extern "C" int APIENTRY
DllMain(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
      g_hinstance = hinstance;

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
      //on_npca2_detach();

	}
	return 1;   // ok
}







const char * ca2_browser_plugin_get_module_name()
{
   return "npca2plugin.dll";
}





/*void on_npca2_detach()
{

}

*/