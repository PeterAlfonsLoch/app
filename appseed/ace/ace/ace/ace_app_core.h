#pragma once


// ATTENTION
// This class should (if it uses) member functions with care:
// It is used after all application app_core (library) finalization,
// when even new/delete/strings/ids can be used anymore for example.

class app_core
{
public:


   DWORD m_dwStartTime;
   DWORD m_dwAfterApplicationFirstRequest;


};




#ifdef WINDOWSEX

typedef int32_t(* PFN_APP_CORE_MAIN)(HINSTANCE hInstance,HINSTANCE hPrevInstance,const char * lpCmdLine,int32_t nCmdShow,app_core & appcore);

#else // WINDOWS

typedef int32_t(* PFN_APP_CORE_MAIN)(const char * lpCmdLine,int32_t nCmdShow,app_core & appcore);

#endif



