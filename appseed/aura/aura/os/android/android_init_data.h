#pragma once




class android_init_data
{
public:

   int            m_iScreenWidth;
   int            m_iScreenHeight;
   const char *   m_pszCommandLine;

};




typedef void FN_native_activity_android_start(android_init_data * pinitdata);
typedef FN_native_activity_android_start * PFN_native_activity_android_start;
