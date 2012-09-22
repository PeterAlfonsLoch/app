#include "framework.h"


simple_app::simple_app()
{
   
   m_iError = 0;

}

simple_app::~simple_app()
{

}


int simple_app::main()
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

   initialize_primitive_heap();


//	_init_atexit();
//	_initterm(__xc_a, __xc_z);			// call C++ constructors

   initialize_primitive_trace();

   if(!os_initialize())
      return -1;
       
   if(!main_initialize()) 
      return -1;

   body();
   
   finalize_primitive_trace();
   
   main_finalize();
    
   os_finalize(); 
    
   finalize_primitive_heap(); 

	//_doexit();
	_term_args();

   return m_iError;

}


void simple_app::body()
{

   if(__argc >= 2)
   {

      if(!strncmp_dup(__argv[1], "-install:", strlen_dup("-install:")))
      {

         //Sleep(15 * 1000);

         xxdebug_box(__argv[1], "simple_app::body", 0);

         vsstring strCommandLine;

         for(int i = 1; i < __argc; i++)
         {

            if(i == 1)
            {
               strCommandLine = &__argv[1][strlen_dup("-install:")];
            }
            else
            {
               strCommandLine = strCommandLine + " ";
               strCommandLine = strCommandLine + __argv[i];
            }

         }
         
         DWORD dwStartError;
         
         spa::ca2_app_install_run(strCommandLine, dwStartError, true);
         
         return;

      }
   }

   try
   {

      if(!initialize())
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

      finalize();

   }
   catch(...)
   {
   }

}

bool simple_app::initialize()
{
   return true;
}

int simple_app::run()
{

	while(true)
	{
      GetMessage(&m_msg, NULL, 0, 0xffffffffu);
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	}

   return 0;
}

bool simple_app::finalize()
{
   return true;
}
