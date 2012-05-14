#include "framework.h"


plain_service::plain_service(::ca::application * papp) :
   ca(papp),
   m_stopping(false),
   service_base(papp)
{
}

plain_service::~plain_service(void)
{
}

void plain_service::Start(DWORD)
{
   thread_pool::QueueUserWorkItem(this, &plain_service::CallServiceThread);
}

void plain_service::Stop(DWORD)
{
   m_stopping = true;
   m_stopped.wait();
}

void plain_service::CallServiceThread()
{
   ServiceThread();
   m_stopped.SetEvent();
}

