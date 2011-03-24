#include "StdAfx.h"
#include "VmpPlusThread.h"
#include "VmpHighThread.h"

#include "XfplayerDoc.h"

// Scoring
#include "XfplayerScoring.h"



VmpPlusThread::VmpPlusThread(::ca::application * papp)
: thread(papp)
{
}

VmpPlusThread::~VmpPlusThread()
{
}

bool VmpPlusThread::initialize_instance()
{
   if(!thread::initialize_instance())
      return false;
   return true;
}

int VmpPlusThread::exit_instance()
{
   // TODO:  perform any per-thread cleanup here
   return thread::exit_instance();
}

void VmpPlusThread::EnableWaveInMessageTranslation(bool bEnable)
{
   m_bEnableWaveInMessageTranslation = bEnable;
}
