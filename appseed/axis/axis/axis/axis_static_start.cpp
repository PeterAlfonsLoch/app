#include "framework.h"
#include "axis/net/net_sockets.h"




namespace axis
{
   
   
   namespace static_start
   {

      
      CLASS_DECL_AXIS void init()
      {
   
         xxdebug_box("axis.dll axis_static_start (0)", "box", MB_OK);
         
   
    
#ifdef BSD_STYLE_SOCKETS
   
         ::sockets::base_socket::s_pmutex = new mutex();
   
#endif
   
   
      }
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      

      
      CLASS_DECL_AXIS void term()
      {


   
#ifdef BSD_STYLE_SOCKETS
         
         delete ::sockets::base_socket::s_pmutex;
   
         ::sockets::base_socket::s_pmutex = NULL;
   
#endif
   
         
      }


   } // namespace static_start

   
} // namespace axis





