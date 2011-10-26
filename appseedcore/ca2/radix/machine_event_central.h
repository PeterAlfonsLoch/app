#pragma once


class CLASS_DECL_ca machine_event_central :
   public simple_thread
{
public:
   machine_event_central(::ca::application * papp);
   virtual ~machine_event_central();

   machine_event  m_machineevent;
   bool     m_bInitialized;

   void read(machine_event_data * pdata);
   void write(machine_event_data * pdata);

   bool initialize();
   int run();

   bool is_close_application();

   void command(xml::node * pnodeCommand);

};