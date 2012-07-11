#include "framework.h"



simple_memory::simple_memory()
{

   m_psz       = NULL;
   m_iAlloc    = 0;
   m_iSize     = 0;

}


simple_memory::simple_memory(const char * psz)
{

   m_iAlloc    = strlen(psz);
   m_iSize     = m_iAlloc;
   m_psz       = (char *) ca2_alloc(m_iSize);
   memcpy(m_psz, psz, m_iSize);

}

simple_memory::~simple_memory()
{
   
   if(m_psz != NULL)
   {
      ca2_free(m_psz);
   }

}


void simple_memory::allocate(int iSize)
{
   
   int iNewAlloc;

   if(m_psz == NULL)
   {

      iNewAlloc = iSize + 2048;
      
      m_psz = (char *) ca2_alloc(iNewAlloc);

      if(m_psz == NULL)
         throw "no memory";

      m_iAlloc = iNewAlloc;

   }
   else if(iSize > m_iAlloc)
   {
      
      iNewAlloc = iSize + 2048;
      
      m_psz = (char *) ca2_realloc(m_psz, iNewAlloc);

      if(m_psz == NULL)
         throw "no memory";

      m_iAlloc = iNewAlloc;

   }

   m_iSize = iSize;

}


void simple_memory::write(void * p, int iCount)
{
   
   allocate(m_iSize + iCount);
   
   memcpy(&m_psz[m_iSize - iCount], p, iCount);

}


int simple_memory::read(void * p, int iCount) const
{
   
   if(m_iPos >= m_iSize)
   {
      return 0;
   }

   int iPosEnd = min(m_iSize, m_iPos + iCount);

   memcpy(p, &m_psz[m_iPos], iPosEnd - m_iPos);

   (const_cast < simple_memory * > (this))->m_iPos = iPosEnd;

}

vsstring simple_memory::str()
{
   
   vsstring str;
   
   to_string(str);

   return str;

}

void simple_memory::to_string(vsstring & str)
{
   
   str.alloc(m_iSize);

   memcpy(str.m_psz, m_psz, m_iSize);

   str.m_psz[m_iSize] = '\0';

}

void simple_memory::from_string(const vsstring & str)
{

   allocate(str.get_length());

   memcpy(get_data(), str, this->get_size());

}

