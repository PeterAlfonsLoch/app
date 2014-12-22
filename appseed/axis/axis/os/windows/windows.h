#pragma once


#ifdef cplusplus

namespace axis
{


   template < class APP >
   static int32_t simple_app_main(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int32_t nCmdShow)
   {

      if(!defer_axis_init())
      {
         return -1;
      }

      APP  * papp = new APP;

      __node_init_main_data(papp, hInstance,hPrevInstance,lpCmdLine,nCmdShow);

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

      defer_axis_term();

      return iRet;

   }


} // namespace axis





#endif


