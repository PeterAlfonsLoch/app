#pragma once


#include "np.h"


namespace npca2
{


   class host : 
      public nsPluginInstanceBase,
      public ::hotplugin::host
   {
   public:

   
      HWND                          m_hwndMessage;
      NPP                           m_instance;
      HWND                          m_hwnd;
      bool                          m_bStream;
      NPObject *                    m_pobjectWindow;
      NPVariant                     m_varDocument;
   


      host(NPP aInstance);
      virtual ~host();

      NPError SetWindow(NPWindow* pNPWindow) ;

   

      uint16 HandleEvent(void * pvoid);


      // npca2::host_interaction::plugin
      virtual HWND get_host_window();
      virtual void redraw();
      virtual bool is_ok();
      virtual void post_message(UINT uiMessage, WPARAM wparam, LPARAM lparam);
      

      NPBool init(NPWindow* aWindow);
      void shut();
      NPBool isInitialized();
      virtual NPError NewStream(NPMIMEType type, NPStream* stream, NPBool seekable, uint16* stype);
      int32  Write(NPStream *stream, int32 offset, int32 len, void *buffer);
      virtual NPError DestroyStream(NPStream *stream, NPError reason);

     // locals
      const char * getVersion();


      // host
      virtual bool      open_url(const char * pszUrl);


      virtual vsstring  calc_location_url();


      void on_paint(HDC hdcWindow, LPCRECT lprect);

      bool finalize();

#ifdef _WINDOWS
      UINT_PTR message_handler(UINT_PTR uiMessage, WPARAM wparam, LPARAM lparam);
#else
      int message_handler(XEvent * pevent);
#endif
   };

} // namespace npca2

