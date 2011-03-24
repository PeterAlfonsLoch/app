#include "StdAfx.h"
#include "syllomatter_console.h"
#include "win\win.h"
#include "resource.h"
#include "gen/CommandLineInfo.h"
#include <iostream>

	IMPLEMENT_DYNAMIC(syllomatter_console, app )

syllomatter_console::syllomatter_console(void)
{
   m_pszAppName = (char * )malloc(100);
   strcpy((char *) m_pszAppName, "NetShareClient");
   m_strBaseSupportId = "votagus_ca2_syllomatter";
}

syllomatter_console::~syllomatter_console(void)
{
}

BOOL syllomatter_console::InitInstance()
{
   set_locale("pt-br");
   set_style("pt-br");

   if(!base_support())
      return FALSE;


   if(!app::InitInstance())
      return FALSE;

   Ex1AppInitialize();

   if(!ca33::application_interface::initialize())
      return FALSE;



   gen::CommandLineInfo cmdInfo;
   Ex1::GetApp()->_001ParseCommandLine(cmdInfo);

   SetRegistryKey("ca2core");



   std::cout << "symat /saaimat./ is an abbreviation of syllomatter\n";
   std::cout << "syllomatter an abbreviation of syllogism matter\n";
   std::cout << "the new matter plus the old matter makes THE MATTER\n";

   LPWSTR lpwstr = ::GetCommandLineW();
   int numargs;
   int numchars;
   wparse_cmdline(
      lpwstr, 
      NULL, 
      NULL,
      &numargs,
      &numchars);

   WCHAR * m_pszCmdLine = new WCHAR[numchars];
   WCHAR ** m_argv = new WCHAR*[numargs];

   wparse_cmdline(
      lpwstr, 
      m_argv, 
      m_pszCmdLine,
      &numargs,
      &numchars);

   int m_argc = numargs - 1;

   class symat symat;
   symat.set_app(this);

   try
   {
	for (int i = 1; i < m_argc; i++)
	{
		LPCWSTR pszParam = m_argv[i];
      if(wcscmp(pszParam, L"create") == 0)
      {
         symat.create(m_argv[i + 1]);
         break;
      }
      else if(wcscmp(pszParam, L"co") == 0)
      {
         // first argument: repository
         // second argument: check out path
         symat.checkout(m_argv[i + 1], m_argv[i + 2]);
         break;
      }
	}
   }
   catch(const char * psz)
   {
      std::cerr << psz;
   }

   return TRUE;
}

BOOL syllomatter_console::ExitInstance()
{
   return TRUE;
}

void syllomatter_console::bergedge_start()
{
}

Ex1FactoryImpl * syllomatter_console::Ex1AppGetFactoryImpl()
{
   return new WinFactoryImpl();
}



BOOL syllomatter_console::OnCmdMsg(UINT nID, int nCode, void* pExtra,
		CAFX_CMDHANDLERINFO* pHandlerInfo)
{
   return gen::app::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



CLASS_DECL_CA2_SYLLOMATTERCONSOLE bergedge_application * get_new_app()
{
   syllomatter_console * papp = new syllomatter_console;
   papp->m_hInstance = AfxGetApp()->m_hInstance;
   return papp;
}


bergedge_application * syllomatter_console::get_app()
{
   return this;
}

