#include "StdAfx.h"
#include "sal.h"


/////////////////////////////////////////////////////////////////////////////
// Standard WinMain implementation
//  Can be replaced as long as 'AfxWinInit' is called first

int CLASS_DECL_VMSWIN AfxWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	__in LPTSTR lpCmdLine, int nCmdShow)
{

   
   ASSERT(hPrevInstance == NULL);

   if(::get_app() == NULL)
   {
      string strId;
      wstring wstr = ::GetCommandLineW();
      string str = gen::international::unicode_to_utf8(wstr);
      int iFind = str.find(" : ");
      if(iFind >= 0)
      {
         iFind = str.find("app=", iFind);
         if(iFind >= 0)
         {
            int iEnd = str.find(" ", iFind);
            if(iEnd < 0)
            {
               strId = str.Mid(iFind + 4);
            }
            else
            {
               strId = str.Mid(iFind + 4, iEnd - iFind - 4);
            }
            gen::str::begins_eat(strId, "\"");
            gen::str::ends_eat(strId, "\"");
         }
      }
      if(strId.is_empty())
         strId = "mplite";
      string strLibrary;
      strLibrary = strId + ".dll";
      HMODULE hmodule = ::LoadLibraryA(strLibrary);
      bool bRawCube = false;
      if(hmodule == NULL)
      {
         hmodule = ::LoadLibraryA("cube.dll");
         DWORD dwLastError = ::GetLastError();
         bRawCube = true;
      }
      LP_GET_NEW_APP  lpgetnewapp = NULL;
      if(hmodule != NULL && lpgetnewapp == NULL)
      {
#ifdef X86
         xxx wont or shouldnot happen in this separated file
#else
         lpgetnewapp = (LP_GET_NEW_APP) ::GetProcAddress(hmodule, "?get_new_app@@YAPEAVapplication@ca@@XZ");
#endif
      }
      if(lpgetnewapp != NULL)
      {
         ::ca::application * pcaapp = lpgetnewapp();
         if(bRawCube)
         {
            pcaapp->construct(strId);
         }
      }
   }

	
   
   int nReturnCode            = -1;
   thread* pThread            = ::get_app();
   icube::application* pApp   = &App(::get_app());

	
   
   // AFX internal initialization
	if (!AfxWinInit(hInstance, hPrevInstance, lpCmdLine, nCmdShow))
		goto InitFailure;

	
   
   // App global initializations (rare)
	if (pApp != NULL && !pApp->InitApplication())
		goto InitFailure;

   
   
   pThread->se_translator::attach();

	
   
   // Perform specific initializations
   try
   {
      try
      {
	      if(!pApp->process_initialize())
	      {
		      if (pThread->GetMainWnd() != NULL)
		      {
			      TRACE(traceAppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
			      pThread->GetMainWnd()->DestroyWindow();
		      }
		      goto InitFailure;
	      }
      }
      catch(const ::ca::exception &)
      {
         if (pThread->GetMainWnd() != NULL)
         {
            pThread->GetMainWnd()->DestroyWindow();
            pThread->SetMainWnd(NULL);
         }
	      goto InitFailure;
      }
      try
      {
	      if(!pThread->initialize_instance())
	      {
		      if (pThread->GetMainWnd() != NULL)
		      {
			      TRACE(traceAppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
			      pThread->GetMainWnd()->DestroyWindow();
		      }

            try
            {
               nReturnCode = pThread->exit();
            }
            catch(...)
            {
               nReturnCode = -1;
            }
		      goto InitFailure;
	      }
      }
      catch(const ::ca::exception & e)
      {
         if(pThread->on_run_exception((::ca::exception &) e))
            goto run;
	      if (pThread->GetMainWnd() != NULL)
	      {
		      TRACE(traceAppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
            try
            {
		         pThread->GetMainWnd()->DestroyWindow();
            }
            catch(::ca::exception &)
            {
            }
            pThread->SetMainWnd(NULL);
	      }
         if(pApp->final_handle_exception((::ca::exception &) e))
            goto run;
	      if (pThread->GetMainWnd() != NULL)
	      {
		      TRACE(traceAppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
            try
            {
		         pThread->GetMainWnd()->DestroyWindow();
            }
            catch(::ca::exception &)
            {
            }
            pThread->SetMainWnd(NULL);
	      }
         try
         {
            nReturnCode = pThread->exit();
         }
         catch(...)
         {
            nReturnCode = -1;
         }
		   goto InitFailure;
      }
      try
      {
	      if(!pApp->bergedge_start())
	      {
		      if (pThread->GetMainWnd() != NULL)
		      {
			      TRACE(traceAppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
			      pThread->GetMainWnd()->DestroyWindow();
		      }
            try
            {
               nReturnCode = pThread->exit();
            }
            catch(...)
            {
               nReturnCode = -1;
            }
		      goto InitFailure;
	      }
      }
      catch(const ::ca::exception & e)
      {
         if(pThread->on_run_exception((::ca::exception &) e))
            goto run;
	      if (pThread->GetMainWnd() != NULL)
	      {
		      TRACE(traceAppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
            try
            {
		         pThread->GetMainWnd()->DestroyWindow();
            }
            catch(::ca::exception &)
            {
            }
            pThread->SetMainWnd(NULL);
	      }
         if(pApp->final_handle_exception((::ca::exception &) e))
            goto run;
	      if (pThread->GetMainWnd() != NULL)
	      {
		      TRACE(traceAppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
            try
            {
		         pThread->GetMainWnd()->DestroyWindow();
            }
            catch(::ca::exception &)
            {
            }
            pThread->SetMainWnd(NULL);
	      }
         try
         {
            nReturnCode = pThread->exit();
         }
         catch(...)
         {
            nReturnCode = -1;
         }
		   goto InitFailure;
      }
   run:
      try
      {
	      nReturnCode = pThread->run();
      }
      catch(const ::ca::exception & e)
      {
         if(pThread->on_run_exception((::ca::exception &) e))
            goto run;
	      if (pThread->GetMainWnd() != NULL)
	      {
		      TRACE(traceAppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
            try
            {
		         pThread->GetMainWnd()->DestroyWindow();
            }
            catch(::ca::exception &)
            {
            }
            pThread->SetMainWnd(NULL);
	      }
         if(pApp->final_handle_exception((::ca::exception &) e))
            goto run;
	      if (pThread->GetMainWnd() != NULL)
	      {
		      TRACE(traceAppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
            try
            {
		         pThread->GetMainWnd()->DestroyWindow();
            }
            catch(::ca::exception &)
            {
            }
            pThread->SetMainWnd(NULL);
	      }
         try
         {
            nReturnCode = pThread->exit();
         }
         catch(...)
         {
            nReturnCode = -1;
         }
		   goto InitFailure;
      }
      try
      {
         nReturnCode = pThread->exit();
      }
      catch(...)
      {
         nReturnCode = -1;
      }
      pThread->se_translator::detach();
   }
   catch(...)
   {
      // linux-like exit style on crash, differently from general windows error message approach
      // to prevent or correct from crash, should:
      // - look at dumps - to do;
      // - look at trace and log - always doing;
      // - look at debugger with the visual or other tool atashed - to doing;
      // - fill other possibilities;
      // - restart and send information in the holy back, and stateful or self-heal as feedback from below;
      // - ...
      // - ..
      // - .
      // - .
      // - .
      // - .
      // -  .
      // - ...
      // - ...
      // - ...
      // to pro-activia and overall benefits workaround:
      // - stateful applications:
      //      - browser urls, tabs, entire history, in the ca2computing cloud;
      //      - word - html document to simplify here - with all history of undo and redos per document optimized by cvs, svn, syllomatter;
      //           - not directly related but use date and title to name document;
      //      - save forms after every key press in .undo.redo.form file parallel to appmatter / form/undo.redo.file parity;
      //      - last karaoke song and scoring, a little less motivated at time of writing;
      //
      // - ex-new-revolut-dynamic-news-self-healing
      //      - pre-history, antecendentes
      //            - sometimes we can't recover from the last state
      //            - to start from the beggining can be too heavy, waity, worky, bory(ing)
      //      - try to creativetily under-auto-domain with constrained-learning, or heuristcally recover from restart, shutdown, login, logoff;
      //           - reification :
      //           - if the document is corrupted, try to open the most of it
      //           - if can only detect that the document cannot be opened or damaged, should creatively workarounds as it comes, as could it be
      //              done, for example search in the web for a proper solution?
      //           - karaoke file does not open? can open next? do it... may animate with a temporary icon...
      //           - import a little as pepper for the meal, prodevian technology into estamira, so gaming experience relativity can open ligh
      //               speed into cartesian dimensions of
      //               ca2, estamira and prodevian. Take care not to flood prodevian brand black ink over the floor of the estamira office...
      //               black letters, or colorful and pink are accepted and sometimes desired, for example, hello kity prodevian, pirarucu games,
      //               I think no one likes to be boring, but a entire background in black... I don't know... only for your personal office, may be...
      //           - could an online colaborator investigate crashes promptly in a funny way, and make news and jokes? Like terra and UOL for the real world?
      //               - new crash, two documents lost, weathers fault, too hot, can't think, my mother was angry with me, lead to buggy code;
      //               - new version with bug fixes;
      //      - new versions
      //      - automatic updates
      //      - upgrades
      //      - rearrangemntes
      //      - downgrade in the form of retro
      // - ...
      // - ..
      // - .
      // - .
      // - .
      // - .
      // -  .
      // - ...
      // - ...
      // - ...

   }
InitFailure:
#ifdef _DEBUG
	// Check for missing AfxLockTempMap calls
	if (AfxGetModuleThreadState()->m_nTempMapLock != 0)
	{
		TRACE(traceAppMsg, 0, "Warning: Temp map lock count non-zero (%ld).\n",
			AfxGetModuleThreadState()->m_nTempMapLock);
	}
	pApp->LockTempMaps();
	pApp->UnlockTempMaps(-1);
#endif

	AfxWinTerm();
	return nReturnCode;
}
