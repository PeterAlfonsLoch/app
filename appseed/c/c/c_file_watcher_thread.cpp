#include "framework.h"


namespace file_watcher
{


   int32_t thread::run()
   {
      /*
#ifndef METROWIN
      try
      {

         MSG msg;
         
         while(true)
         {

            msg.message = 0;

            while(GetMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {

               if(msg.message == WM_QUIT)
                  goto quit;

            }
            
            try
            {
         
               update();
               
            }
            catch(::file_watcher::exception &)
            {
         
            }
            
         }
quit:;
         
      }
      catch(...)
      {
         
      }
#endif
      */
      return 0;

   }


} // namespace file_watcher




