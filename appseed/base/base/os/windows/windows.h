#pragma once






namespace aura
{


   template < class APP >
   static int32_t simple_app_main(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int32_t nCmdShow)
   {

      if(!defer_aura_init())
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

      defer_base_term();

      return iRet;

   }


} // namespace base



