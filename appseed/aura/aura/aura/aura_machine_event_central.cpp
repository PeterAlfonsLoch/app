//#include "framework.h"


machine_event_central::machine_event_central(::aura::application * papp) :
   object(papp), 
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

   // todo (camilo) instead of sleeping (at machine_event_central::run) , wait for change messages pooling in the machine event data file.

   // meanwhile, not being used, so exit... It is a problem for Instrumentation Profiling, as function timing (and not cpu usage), counts.
#if 0

   if(!begin())
      return false;

#endif

   m_bInitialized = true;

   return m_bInitialized;

}


int32_t machine_event_central::run()
{

   // todo (camilo) instead of sleeping, wait for change messages pooling in the machine event data file.

   // meanwhile, not being used, so exit... It is a problem for Instrumentation Profiling, as function timing (and not cpu usage), counts.

#if 0

   while(get_run())
   {

      {
         synch_lock lockMachineEvent(&m_machineevent.m_mutex);

         //machine_event_data data;

         //m_machineevent.read(&data);

         //System.process_machine_event_data(&data);
      }

      Sleep(484);

   }

#endif

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