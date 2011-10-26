#pragma once


class CLASS_DECL_____ event_wait
{
public:


   simple_event *    m_pevent;


   event_wait(simple_event * pmutex, bool bInitialWait);
   ~event_wait();


   void wait();


};

