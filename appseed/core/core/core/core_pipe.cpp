#include "framework.h"


#ifndef METROWIN

#if defined(LINUX) || defined(ANDROID)
#include <fcntl.h>
#include <unistd.h>
#endif


namespace core
{


   pipe::pipe(bool bInherit)
   {

      m_pchBuf = NULL;

#ifdef WINDOWS

      m_sa.nLength = sizeof(SECURITY_ATTRIBUTES);
      m_sa.bInheritHandle = bInherit ? TRUE : FALSE;
      m_sa.lpSecurityDescriptor = NULL;
      m_hRead = NULL;
      m_hWrite = NULL;
