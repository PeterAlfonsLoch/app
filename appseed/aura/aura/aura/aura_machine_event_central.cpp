#include "framework.h"

machine_event_central::machine_event_central(sp(::aura::application) papp) :
   element(papp), 
   thread(papp),
   simple_thread(papp)
{
   m_bInitialized = false;
}

machine_event_central::~machine_event_central()
{
}

bool machine_event_central::initialize()
{
   if(m_bInitialized)
      return true;
   if(!begin())
      return false;
   m_bInitialized = true;
   return m_bInitialized;
}


int32_t machine_event_central::run()
{

   while(get_run())
   {

      {
         synch_lock lockMachineEvent(&m_machineevent.m_mutex);

         machine_event_data data;

         m_machineevent.read(&data);

         System.process_machine_event_data(&data);
      }

      Sleep(484);

   }

   return 0;

}


bool machine_event_central::is_close_application()
{
   
   synch_lock lockMachineEvent(&m_machineevent.m_mutex);

   machine_event_data data;

   m_machineevent.read(&data);

   System.process_machine_event_data(&data);

   return data.m_fixed.m_bRequestCloseApplication;

}


void machine_event_central::command(sp(::xml::node) pnode)
{
   synch_lock lockMachineEvent(&m_machineevent.m_mutex);
   machine_event_data data;
   m_machineevent.read(&data);
   xml::document doc(get_app());
   if(data.m_blobCommand.m_pchData != NULL)
   {
      doc.load(data.m_blobCommand.m_pchData);
   }
   if(doc.get_name().is_empty())
      doc.set_name("command");
   doc.add_child(pnode);
   data.m_blobCommand = doc.get_xml();
   m_machineevent.write(&data);
   Sleep(484);
}