#include "framework.h"


blob::blob()
{ 
   m_sizet     = 0; 
   m_pchData   = NULL; 
}

blob::~blob()
{
   if(m_pchData != NULL)
   {
      memory_free_dbg(m_pchData, 0); 
      m_pchData = NULL;
   }
}


void blob::read(HANDLE f)
{
   if(m_pchData != NULL)
      memory_free_dbg(m_pchData, 0);
   DWORD dwRead;
   ::ReadFile(f, &m_sizet, sizeof(m_sizet), &dwRead, NULL);
   if(m_sizet == 0)
   {
      m_pchData = NULL;
   }
   else
   {
      
      m_pchData = (char *) memory_alloc(m_sizet);
      
      size_t sRead = 0;

      while(::ReadFile(f, &m_pchData[sRead], 1024, &dwRead, NULL))
      {
         if(dwRead == 0)
            break;
         sRead += dwRead;
      }

   }
}

void blob::write(HANDLE f)
{
   DWORD dwWritten;
   ::WriteFile(f, &m_sizet, sizeof(m_sizet), &dwWritten, NULL);
   if(m_sizet > 0)
   {
      
      size_t sWritten = 0;

      while(::WriteFile(f, &m_pchData[sWritten], 1024, &dwWritten, NULL))
      {

         if(dwWritten == 0)
            break;

         sWritten += dwWritten;

      }

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
