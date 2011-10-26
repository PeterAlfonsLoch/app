#pragma once

class update_schedule_thread;

class CLASS_DECL_CA2_WINSERVICE_1 update_thread : 
   public ::radix::thread
{
public:

   update_thread(::ca::application * papp);

   update_schedule_thread * m_pschedulethread;
   bool initialize_instance();
   int run();
   void defer_update(const char * pszVersionShift, const char * pszBuild);
   void update(const char * pszVersionShift, const char * pszBuild);
};