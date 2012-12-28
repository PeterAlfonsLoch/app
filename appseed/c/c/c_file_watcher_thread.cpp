#include "framework.h"


namespace file_watcher
{


   int32_t thread::run()
   {

#ifndef METROWIN
      try
      {
         
         while(true)
         {
            
            try
            {
         
               update();
               
            }
            catch(::file_watcher::exception &)
            {
         
            }
            
         }
         
      }
      catch(...)
      {
         
      }
#endif
      return 0;

   }


} // namespace file_watcher




