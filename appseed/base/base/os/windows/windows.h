#pragma once




#include "axis/axis/os/windows/windows.h"





#ifdef cplusplus


#ifdef WINDOWSEX

namespace base
{


   class system_interaction_impl;


} // namespace axis


#endif

namespace base
{


   template < class APP >
   static_function int32_t simple_app_main(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int32_t nCmdShow)
   {

      if(!defer_base_init())
      {
         return -1;
      }

      APP  * papp = new APP;

      __node_init_main_data(papp,hInstance,hPrevInstance,lpCmdLine,nCmdShow);

      int32_t iRet;

      iRet = papp->main();

      try
      {

         delete papp;

         papp = NULL;

      }
      catch(...)
      {
      }

      defer_base_term();

      return iRet;

   }


} // namespace base





#endif


#include "base/graphics/graphics_window_graphics.h"
#include "windows_window_gdi.h"
