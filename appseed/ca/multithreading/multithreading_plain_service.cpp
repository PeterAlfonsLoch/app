#include "framework.h"


plain_service::plain_service(::ca::application * papp) :
   ca(papp),
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
   m_stopping = true;
   m_stopped.wait(millis(ui));
}

void plain_service::CallServiceThread()
{
   ServiceThread();
   m_stopped.SetEvent();
}

