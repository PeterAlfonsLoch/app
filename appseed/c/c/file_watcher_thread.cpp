#include "framework.h"


namespace file_watcher
{


   int thread::run()
   {

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
   
      return 0;

   }


} // namespace file_watcher




