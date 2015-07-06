#pragma once




class android_init_data
{
public:

   int      m_iScreenWidth;
   int      m_iScreenHeight;

};




typedef void FN_native_activity_android_main(android_init_data * pinitdata);
typedef FN_native_activity_android_main * PFN_native_activity_android_main;
