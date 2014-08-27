#pragma once




#ifdef cplusplus


CLASS_DECL_AXIS bool vfxResolveShortcut(string & strTarget,const char * pszSource,sp(::user::interaction) puiMessageParentOptional);




#endif









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
      ::windows::main_init_data * pmaininitdata = new ::windows::main_init_data;


      pmaininitdata->m_hInstance = hInstance;
      pmaininitdata->m_hPrevInstance = hPrevInstance;
      pmaininitdata->m_vssCommandLine = ::str::international::unicode_to_utf8(::GetCommandLineW());
      pmaininitdata->m_nCmdShow = nCmdShow;

      papp->init_main_data(pmaininitdata);

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



