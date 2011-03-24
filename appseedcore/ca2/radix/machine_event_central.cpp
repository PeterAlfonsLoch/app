#include "StdAfx.h"

machine_event_central::machine_event_central(::ca::application * papp) :
   ca(papp), 
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
   if(!Begin())
      return false;
   m_bInitialized = true;
   return m_bInitialized;
}


int machine_event_central::run()
{
   while(get_run())
   {
      {
         mutex_lock lockMachineEvent(m_machineevent.m_hmutex);
         machine_event_data data;
         m_machineevent.read(&data);
         System.process(&data);
      }
      Sleep(484);
   }
   return 0;
}

bool machine_event_central::is_close_application()
{
   mutex_lock lockMachineEvent(m_machineevent.m_hmutex);
   machine_event_data data;
   m_machineevent.read(&data);
   System.process(&data);
   return data.m_fixed.m_bRequestCloseApplication;
}


void machine_event_central::command(xml::node * pnode)
{
   mutex_lock lockMachineEvent(m_machineevent.m_hmutex);
   machine_event_data data;
   m_machineevent.read(&data);
   xml::node node(get_app());
   if(data.m_blobCommand.m_pchData != NULL)
   {
      node.load(data.m_blobCommand.m_pchData);
   }
   if(node.m_strName.is_empty())
      node.m_strName = "command";
   node.add_child(pnode);
   data.m_blobCommand = node.get_xml();
   m_machineevent.write(&data);
   Sleep(484);
}