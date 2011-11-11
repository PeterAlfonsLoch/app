#pragma once


class CLASS_DECL_____ machine_event
{
public:


   simple_mutex      m_mutex;
   bool              m_bInitialized;


   machine_event();
   virtual ~machine_event();


   bool initialize();

   bool read(machine_event_data * pdata);
   bool write(machine_event_data * pdata);

};
