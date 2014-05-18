#include "framework.h"


simple_app::simple_app() :
   ::base::system(this)
{
   
   m_iError = 0;

}

simple_app::~simple_app()
{

}


int32_t simple_app::main()
{

   //Sleep(15 * 1000);

   __argc = _init_args();
	__targv = _argv;
	_init_file();

	TCHAR *cmd = GetCommandLine();

	// Skip program name
	if (*cmd == _T('"'))
	{
	    while (*cmd && *cmd != _T('"'))
	        cmd++;
	    if (*cmd == _T('"'))
	        cmd++;
	}
	else
	{
	    while (*cmd > _T(' '))
	        cmd++;
	}

	// Skip any white space
	while (*cmd && *cmd <= _T(' '))
	    cmd++;

	STARTUPINFO si;
	si.dwFlags = 0;
	GetStartupInfo(&si);

   //initialize_primitive_heap(); 


//	_init_atexit();
//	_initterm(__xc_a, __xc_z);			// call C++ constructors

   //initialize_primitive_trace();

   if(!os_initialize())
   {
      return -1;
   }
    
       
   if(!main_initialize()) 
   {
      return -1;
   }

   body();
   
   main_finalize();
    
   os_finalize(); 
    
   //finalize_primitive_heap(); 

	//_doexit();
	_term_args();

   return m_iError;

}


void simple_app::body()
{

   try
   {
      if ((m_iError = simple_app_pre_run()) != 0)
      {
         if (m_iError != 0)
            m_iError = -1;

         return;

      }
   }
   catch (...)
   {

      if (m_iError > 0)
         m_iError = -1;

      return;

   }


   try
   {

      set_main_thread(GetCurrentThread());

      set_main_thread_id(GetCurrentThreadId());

      if ((m_iError = pre_run()) != 0)
      {

         if (m_iError != 0)
            m_iError = -1;

         return;

      }

      SetCurrentHandles();

   }
   catch (...)
   {
      if (m_iError > 0)
         m_iError = -1;

      return;

   }


   try
   {

      if(!intro())
      {
         if(m_iError > 0)
            m_iError = -1;

         return;

      }

   }
   catch(...)
   {
      if(m_iError > 0)
         m_iError = -1;

      return;

   }

   try
   {

      m_iError = run();

   }
   catch(...)
   {
      if(m_iError > 0)
         m_iError = -1;

      return;

   }

   try
   {

      end();

   }
   catch(...)
   {
   }

}

bool simple_app::intro()
{
   return true;
}

int32_t simple_app::refrain()
{

	while(true)
	{
      GetMessage(&m_msg, NULL, 0, 0xffffffffu);
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	}

   return 0;
}

bool simple_app::end()
{
   return true;
}


int32_t simple_app::simple_app_pre_run()
{
   return 0;
}