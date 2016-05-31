




namespace ace
{


   string app_launcher::get_executable_path()
   {
      
#ifdef MACOS
      
      if(file_exists_dup("/Users/carlos/.ca2/mypath/"+m_strApp+".txt"))
      {
         
         string strPath = file_as_string_dup("/Users/carlos/.ca2/mypath/"+m_strApp+".txt");
         
         if(strPath.has_char())
         {
          
            return strPath;
            
         }
         
      }
      else
      {
         file_put_contents_dup("/Users/carlos/.ca2/mypath/tst.txt", "/Users/carlos/.ca2/mypath/"+m_strApp+".txt");
      }
      
      return Sys(get_thread_app()).dir().ca2module() / "app";
      
#else

#ifdef DEBUG

#ifdef WINDOWS

      return Sys(get_thread_app()).dir().ca2module() / "app.exe";

#else

      return Sys(get_thread_app()).dir().ca2module() / "app";

#endif

#else

      return path::a_spa();

#endif
      #endif

   }

   string app_launcher::get_params()
   {

      string strParameters;

      strParameters = " : app=" + m_strApp;

      return strParameters;

   }


   bool app_launcher::start()
   {

#ifdef METROWIN

      return false;

#elif defined(WINDOWS)

	   wstring wstrApp(get_executable_path());

	   wstring wstrDir(dir::name(string(wstrApp)));

	   wstring wstrParams = get_params();

	   STARTUPINFOW si;
      memset(&si,0,sizeof(si));
      si.cb = sizeof(si);
      si.dwFlags = STARTF_USESHOWWINDOW;
      si.wShowWindow = SW_SHOWNORMAL;
      PROCESS_INFORMATION pi;
      memset(&pi,0,sizeof(pi));

      wstring wstrCmdLine = (L"\"" + wstrApp + L"\"" + wstrParams).c_str();

      if(::CreateProcessW((unichar *)wstrApp.c_str(),(unichar *)wstrCmdLine.c_str(),
         NULL,NULL,FALSE,0,NULL,wstrDir,
         &si,&pi))
         return true;

#else

	   string strPath = get_executable_path();

	   string strDir = dir::name(strPath);

	   string strParams = get_params();


	  if (call_async(strPath, strParams, strDir , 0, false) == 0)
		  return true;

#endif

      return false;

   }


} // namespace ace




