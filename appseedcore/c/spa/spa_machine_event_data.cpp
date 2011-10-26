#include "StdAfx.h"


blob::blob()
{ 
   m_sizet     = 0; 
   m_pchData   = NULL; 
}

blob::~blob()
{
   if(m_pchData != NULL)
   {
      ca2_free(m_pchData); 
      m_pchData = NULL;
   }
}


void blob::read(HANDLE f)
{
   if(m_pchData != NULL)
      ca2_free(m_pchData);
   DWORD dwRead;
   ::ReadFile(f, &m_sizet, sizeof(m_sizet), &dwRead, NULL);
   if(m_sizet == 0)
   {
      m_pchData = NULL;
   }
   else
   {
      m_pchData = (char *) ca2_alloc(m_sizet);
      ::ReadFile(f, m_pchData, m_sizet, &dwRead, NULL);
   }
}

void blob::write(HANDLE f)
{
   DWORD dwWritten;
   ::WriteFile(f, &m_sizet, sizeof(m_sizet), &dwWritten, NULL);
   if(m_sizet >= 0)
   {
      ::WriteFile(f, m_pchData, m_sizet, &dwWritten, NULL);
   }
}

blob & blob::operator = (const char * psz)
{
   m_sizet = strlen_dup(psz) + 1;
   m_pchData = (char *) strdup_dup(psz);
   return *this;
}


machine_event_data::fixed::fixed()
{
   m_bRequestCloseApplication    = false;
   m_bSpaUpgrade                 = false;
}

void machine_event_data::read(HANDLE f)
{
   DWORD dwRead;
   ::ReadFile(f, &m_fixed, sizeof(m_fixed), &dwRead, NULL);
   m_blobCommand.read(f);
}

void machine_event_data::write(HANDLE f)
{
   DWORD dwWritten;
   ::WriteFile(f, &m_fixed, sizeof(m_fixed), &dwWritten, NULL);
   m_blobCommand.write(f);
}
