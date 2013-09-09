#pragma once




class hthread :
    virtual public root
{
public:


   event               * m_pevent;
   base_thread          * m_pthread;
   os_thread                  * m_posthread;


   hthread();
   virtual ~hthread();


   void wait();


};





class thread;








