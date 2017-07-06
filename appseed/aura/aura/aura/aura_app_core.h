#pragma once


// ATTENTION
// This class should (if it uses) member functions with care:
// It is used after all application app_core (library) finalization,
// when even new/delete/strings/ids can be used anymore for example.

class CLASS_DECL_AURA app_core
{
public:


   DWORD m_dwStartTime;
   DWORD m_dwAfterApplicationFirstRequest;


   int start();

   int end();


};




#ifdef WINDOWSEX

typedef int32_t(* PFN_APP_CORE_MAIN)(HINSTANCE hInstance,HINSTANCE hPrevInstance,const char * lpCmdLine,int32_t nCmdShow,app_core & appcore);

CLASS_DECL_AURA int32_t app_common_main(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow, app_core & appcore);
CLASS_DECL_AURA int32_t app_common_main(int argc, char *argv[], app_core & appcore);

#else // WINDOWS

typedef int32_t(* PFN_APP_CORE_MAIN)(const char * lpCmdLine,int32_t nCmdShow,app_core & appcore);

#endif







