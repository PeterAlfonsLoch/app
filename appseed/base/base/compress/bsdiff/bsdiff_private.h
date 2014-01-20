#pragma once


#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

/*#ifdef libbsdif_DLL
   #define libbsdif_API  __declspec(dllexport)
#elif defined(USE_BZ_DLL)
   #define libbsdif_API  __declspec(dllimport)
#elif defined(libbsdif_LIB)
   #define libbsdif_API  extern
#else
   #define libbsdif_API  extern
#endif*/

#ifdef WINDOWS
template<class T1, class T2>
int32_t err(int32_t i, const char* str, T1 arg1, T2 arg2)
{
   wchar_t lastErrorTxt[1024];
   FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,GetLastError(),0,lastErrorTxt,1024,NULL);
   printf("%s", string(lastErrorTxt));
   printf(str, arg1, arg2);
   return (i);
}

template<class T>
int32_t err(int32_t i, const char* str, T arg)
{
   wchar_t lastErrorTxt[1024];
   FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,GetLastError(),0,lastErrorTxt,1024,NULL);
   printf("%s", string(lastErrorTxt));
   printf(str, arg);
   return (i);
}
#else
template<class T1, class T2>
int32_t err(int32_t i, const char* str, T1 arg1, T2 arg2)
{
   printf_dup(str, arg1, arg2);
   return (i);
}

template<class T>
int32_t err(int32_t i, const char* str, T arg)
{
   printf_dup(str, arg);
   return (i);
}
#endif

int32_t err(int32_t i, const char* str);

template<class T>
int32_t errx(int32_t i, const char* str, T arg)
{
   
   printf(str, arg);
   
   return i;

}

int32_t errx(int32_t i, const char* str);
