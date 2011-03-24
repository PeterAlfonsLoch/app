// FrameWndInterface.cpp: implementation of the FrameWndInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vmsgen.h"
#include "_vmsgenFrameWndInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace _vmsgen
{
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FrameWndInterface::FrameWndInterface()
{

}

FrameWndInterface::~FrameWndInterface()
{

}

OleFrameHook * FrameWndInterface::GetNotifyHook()
{
   return NULL;
}


} // namespace _vmsgen

