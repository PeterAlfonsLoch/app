#include "StdAfx.h"
#include "netnodeScriptInstance.h"
#include "netnodeScriptManager.h"

netnodeScriptInstance::netnodeScriptInstance(netnodeScript * pscript) :
   ca(pscript->get_app()),
   netnodeScriptImpl(pscript)
{
}

netnodeScriptInstance::~netnodeScriptInstance()
{
}

void netnodeScriptInstance::destroy()
{
   delete this;
}