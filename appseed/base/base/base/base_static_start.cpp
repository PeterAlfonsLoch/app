#include "framework.h"
#include "framework.h" // from "base/net/net_sockets.h"



namespace base
{
   
   
   namespace static_start
   {

      
      CLASS_DECL_BASE void init()
      {
   
         xxdebug_box("base.dll base_static_start (0)", "box", MB_OK);
         
   
    
#ifdef BSD_STYLE_SOCKETS
   
         ::sockets::base_socket::s_pmutex = new mutex();
   
#endif
   
   
      }
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      

      
      CLASS_DECL_BASE void term()
      {


   
#ifdef BSD_STYLE_SOCKETS
         
         delete ::sockets::base_socket::s_pmutex;
   
         ::sockets::base_socket::s_pmutex = NULL;
   
#endif
   
         
      }


   } // namespace static_start

   
} // namespace base





