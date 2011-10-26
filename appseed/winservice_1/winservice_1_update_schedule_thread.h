#pragma once

class CLASS_DECL_CA2_WINSERVICE_1 update_schedule_thread : 
   public simple_thread
{
public:
   
   update_schedule_thread(::ca::application * papp);

   int run();

   mutex            m_mutexUpdating;
   
};