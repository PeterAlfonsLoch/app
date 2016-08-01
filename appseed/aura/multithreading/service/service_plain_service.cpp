#include "framework.h"


plain_service::plain_service(::aura::application * papp) :
   object(papp),
   service_base(papp)
{
}

plain_service::~plain_service()
{
}

void plain_service::Start(uint32_t)
{
   thread_pool::QueueUserWorkItem(this, &plain_service::CallServiceThread);
}

void plain_service::Stop(uint32_t ui)
{
   System.m_bDoNotExitIfNoApplications = false;
   m_bStopping = true;
   m_stopped.wait(millis((uint32_t) m_dwStopTimeout));
}

void plain_service::CallServiceThread()
{

   call_server();

}

