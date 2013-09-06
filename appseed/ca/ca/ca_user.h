#pragma once


namespace ca
{


   class thread_base;


} // namespace ca





class hthread :
    virtual public root
{
public:


   event               * m_pevent;
   ::ca::thread_base          * m_pthread;
   os_thread                  * m_posthread;


   hthread();
   virtual ~hthread();


   void wait();


};





namespace ca2
{

   class thread;

}






CLASS_DECL_ca mutex & user_mutex();

