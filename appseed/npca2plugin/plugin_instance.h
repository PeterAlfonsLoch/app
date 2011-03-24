#pragma once

#include "np.h"

class CLASS_DECL_CA2_NPCA2 nsPluginInstance : 
   public nsPluginInstanceBase,
   public npca2::plugin
{
public:

   
   
   NPP                           m_instance;
   HWND                          m_hwnd;
   bool                          m_bStream;
   NPObject *                    m_pobjectWindow;
   NPVariant                     m_varDocument;
   


   nsPluginInstance(NPP aInstance);
   ~nsPluginInstance();

   NPError SetWindow(NPWindow* pNPWindow) ;

   

   uint16 HandleEvent(void * pvoid);


   // npca2::host_interaction::plugin
   virtual HWND get_host_window();
   virtual void redraw();
   virtual bool is_ok();
   virtual void post_message(UINT uiMessage, WPARAM wparam, LPARAM lparam);
   virtual void get_window_rect(__rect64 * lprect);
   virtual void get_window_rect(LPRECT lprect);
   virtual bool open_url(const char * pszUrl);
   virtual npca2::host_interaction * create_host_interaction();

   NPBool init(NPWindow* aWindow);
   void shut();
   NPBool isInitialized();
   virtual NPError NewStream(NPMIMEType type, NPStream* stream, NPBool seekable, uint16* stype);
   int32  Write(NPStream *stream, int32 offset, int32 len, void *buffer);
   virtual NPError DestroyStream(NPStream *stream, NPError reason);

  // locals
   const char * getVersion();


};
