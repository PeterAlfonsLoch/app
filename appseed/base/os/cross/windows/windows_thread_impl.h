#pragma once


struct hthread :
    virtual public root
{


   event               * m_pevent;
   base_thread          * m_pthread;
   os_thread                  * m_posthread;


   hthread();
   virtual ~hthread();


   void wait();


};
