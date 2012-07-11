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



void simple_memory::FromAsc(const char * psz)
{

   vsstring str;

   while(*psz)
   {

      char ch = ((*psz & 0xf0) >> 4);

      if(ch < 10)
         ch += '0';
      else
         ch += 'A' - 10;

      str += ch;

      ch = ((*psz & 0xf));

      if(ch < 10)
         ch += '0';
      else
         ch += 'A' - 10;

      str += ch;

      psz++;

   }

   From(str);

}



void simple_memory::From(const char * psz)
{

   char ch;

   ::count iLen = strlen(psz);

   allocate(iLen / 2);

   char * pch = (char *) get_data();

   while(*psz != '\0')
   {

      ch = 0;

      if(*psz > '9')
         ch |= ((*psz - 'A' + 10) & 0x0f) << 4;
      else
         ch |= ((*psz - '0') & 0x0f) << 4;

      if(*psz == '\0')
         break;

      psz++;

      if(*psz > '9')
         ch |= ((*psz - 'A' + 10) & 0x0f);
      else
         ch |= ((*psz - '0') & 0x0f);

      *pch = ch;

      psz++;

      pch++;

   }

}



void simple_memory::ToAsc(vsstring & str)
{

   vsstring strTo;

   To(strTo);

   char ch;

   ::count iLen = strTo.get_length() - 1;

   for(int i = 0; i < iLen; i+=2)
   {

      if(strTo[i] <= '9')
         ch = (strTo[i] - '0') << 4;
      else
         ch = (strTo[i] - 'A' + 10) << 4;

      if(strTo[i + 1] <= '9')
         ch |= (strTo[i + 1] - '0');
      else
         ch |= (strTo[i + 1] - 'A' + 10);

      str += ch;

   }

}



void simple_memory::To(vsstring & str, size_t dwStart, size_t dwEnd)
{
   dwStart = max(dwStart, 0);
   if(dwEnd == ((size_t)(-1)))
      dwEnd = this->get_size() - 1;
   char * pch = (char *) get_data();
   for(uint64_t dw = dwStart; dw <= dwEnd; dw++)
   {
      if(((pch[dw] & 0xf0) >> 4) < 10)
         str += (char)(((pch[dw] & 0xf0) >> 4) + '0');
      else
         str += (char)(((pch[dw] & 0xf0) >> 4) + 'A' - 10);
      if(((pch[dw] & 0x0f)) < 10)
         str += (char)((pch[dw] & 0x0f) + '0');
      else
         str += (char)((pch[dw] & 0x0f) + 'A' - 10);
   }
}

