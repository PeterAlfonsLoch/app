#pragma once


#ifdef cplusplus


CLASS_DECL_AXIS bool vfxResolveShortcut(string & strTarget,const char * pszSource,sp(::aura::interaction) puiMessageParentOptional);



#endif


#ifdef cplusplus

namespace axis
{


   template < class APP >
   static int32_t simple_app_main(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int32_t nCmdShow)
   {

      if(!defer_axis_init())
      {

         ::OutputDebugString("Failed to defer_axis_init.");

         return -2;

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

      if(!defer_axis_init())
      {

         ::OutputDebugString("Failed to defer_axis_term.");

         iRet -= 9011;

      }

      return iRet;

   }


} // namespace axis





#endif


