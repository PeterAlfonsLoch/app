//#include "framework.h"


#if !defined(METROWIN)


namespace primitive
{


   shared_memory::shared_memory(const memory_base & s)
   {

      m_nAllocFlags     = 0;
      m_hGlobalMemory   = NULL;
      m_bAllowGrow      = TRUE;
      m_pbStorage = NULL;
      m_pbComputed = NULL;

      memory_base::operator             = (s);

   }

   shared_memory::shared_memory(primitive::memory_container * pcontainer, double dAllocationRateUp, UINT nAllocFlags)
   {

      m_nAllocFlags        = nAllocFlags;
      m_bAllowGrow         = TRUE;
      m_pcontainer         = pcontainer;
      m_dAllocationRateUp  = dAllocationRateUp;
      m_pbStorage = NULL;
      m_pbComputed = NULL;

   }

   shared_memory::shared_memory(primitive::memory_container * pcontainer, void * pMemory, memory_size_t dwSize)
   {

      m_nAllocFlags     = 0;
      m_pcontainer      = pcontainer;
      m_bAllowGrow      = TRUE;
      m_pbStorage = NULL;
      m_pbComputed = NULL;

      allocate(dwSize);

      ASSERT(__is_valid_address(pMemory, (uint_ptr) dwSize, FALSE));

      memcpy(m_pbStorage, pMemory, (size_t) dwSize);

   }

   shared_memory::shared_memory(const void * pMemory, memory_size_t dwSize)
   {

      m_nAllocFlags     = 0;
      m_pcontainer      = NULL;
      m_bAllowGrow      = TRUE;
      m_pbStorage = NULL;
      m_pbComputed = NULL;

      allocate(dwSize);

      ASSERT(__is_valid_address(pMemory, (uint_ptr) dwSize, FALSE));

      memcpy(m_pbStorage, pMemory, (size_t) dwSize);

   }


   shared_memory::~shared_memory()
   {

      if(m_pbStorage != NULL)
      {

         impl_free(m_pbStorage);

      }

   }


   LPBYTE shared_memory::detach_shared_memory(HGLOBAL & hglobal)
   {

      if(m_iOffset > 0)
      {
         
         sp(shared_memory) pbase = clone();

         impl_free(m_pbStorage);

         pbase->detach_shared_memory(hglobal);

      }
      else
      {

         hglobal              = m_hGlobalMemory;

      }

      LPBYTE pbStorage     = m_pbStorage;

      m_hGlobalMemory      = NULL;
      m_pbStorage          = NULL;
      m_pbComputed   = NULL;
      m_cbStorage          = 0;
      m_dwAllocation       = 0;

      return pbStorage;

   }


   void shared_memory::SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow)
   {
      
      UNREFERENCED_PARAMETER(bAllowGrow);

      ASSERT(m_hGlobalMemory == NULL);        // do once only

      ASSERT(m_pbStorage == NULL);     // do once only

      if (hGlobalMemory == NULL)
      {

         throw invalid_argument_exception(get_app());

      }

      m_hGlobalMemory = hGlobalMemory;

      m_pbStorage = (BYTE*)::GlobalLock(m_hGlobalMemory);

      m_pbComputed = m_pbStorage;

      m_dwAllocation = m_cbStorage = (ULONG)::GlobalSize(m_hGlobalMemory);

      // xxx m_bAllowGrow = bAllowGrow;

   }


   LPBYTE shared_memory::impl_alloc(memory_size_t nBytes)
   {

      ASSERT(m_hGlobalMemory == NULL);        // do once only

      m_hGlobalMemory = ::GlobalAlloc(m_nAllocFlags, nBytes);

      if (m_hGlobalMemory == NULL)
         return NULL;

      return (LPBYTE) ::GlobalLock(m_hGlobalMemory);

   }


   LPBYTE shared_memory::impl_realloc(void*, memory_size_t nBytes)
   {
      
      if (!m_bAllowGrow)
         return NULL;

      ASSERT(m_hGlobalMemory != NULL);

      ::GlobalUnlock(m_hGlobalMemory);

      HGLOBAL hNew;

      hNew = ::GlobalReAlloc(m_hGlobalMemory, nBytes, m_nAllocFlags);

      if (hNew == NULL)
         return NULL;

      m_hGlobalMemory = hNew;

      return (LPBYTE) ::GlobalLock(m_hGlobalMemory);

   }

   
   void shared_memory::impl_free(LPBYTE)
   {
      
      ASSERT(m_hGlobalMemory != NULL);

      ::GlobalUnlock(m_hGlobalMemory);

      ::GlobalFree(m_hGlobalMemory);

   }

   
   //LPBYTE * shared_memory::detach()
   //{

   //   throw not_supported_exception(get_app(),"not valid for Global Memory(\"HGLOBAL\")");

   //}


   //void shared_memory::free_data()
   //{
   //   if(m_pbStorage != NULL)
   //   {
   //      m_dwAllocation    = 0;
   //      try
   //      {
   //         ::GlobalUnlock(m_hGlobalMemory);
   //         ::GlobalFree(m_hGlobalMemory);
   //      }
   //      catch(...)
   //      {
   //      }
   //      m_pbStorage       = NULL;
   //      m_pbComputed = NULL;
   //   }
   //}

















   /*void shared_memory::copy_from(const memory_base *pstorage)
   {
      ASSERT(pstorage != NULL);
      allocate(pstorage->get_size());
      memcpy(get_data(), pstorage->get_data(), (size_t) this->get_size());

   }

   void shared_memory::set_data(void *pdata, memory_size_t uiSize)
   {
      allocate(uiSize);
      memcpy(get_data(), pdata, (size_t) uiSize);
   }
   */

   /*void shared_memory::To(string & str, memory_position_t iStart, memory_position_t iEnd)
   {
      iStart = MAX(iStart, 0);
      if(iEnd == -1)
         iEnd = this->get_size() - 1;
      char * pch = (char *) get_data();
      for(memory_position_t i = iStart; i <= iEnd; i++)
      {
         if(((pch[i] & 0xf0) >> 4) < 10)
            str += (char)(((pch[i] & 0xf0) >> 4) + '0');
         else
            str += (char)(((pch[i] & 0xf0) >> 4) + 'A' - 10);
         if(((pch[i] & 0x0f)) < 10)
            str += (char)((pch[i] & 0x0f) + '0');
         else
            str += (char)((pch[i] & 0x0f) + 'A' - 10);
      }
   }

   void shared_memory::From(const char * psz)
   {
      char ch;
      int32_t iLen = strlen(psz);
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

   void shared_memory::ToAsc(string & str)
   {
      string strTo;
      To(strTo);
      char ch;
      int32_t iLen = strTo.get_length() - 1;
      for(int32_t i = 0; i < iLen; i+=2)
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

   void shared_memory::FromAsc(const char * psz)
   {
      string str;
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
   }*/


   /*void shared_memory::from_string(const unichar * pwsz)
   {
      from_string(::str::international::unicode_to_utf8(pwsz));
   }

   void shared_memory::from_string(const char * psz)
   {
      allocate(strlen(psz));
      memcpy(get_data(), psz, this->get_size());
   }

   void shared_memory::to_string(string & str)
   {
      LPTSTR lpsz = str.GetBufferSetLength(this->get_size() + 1);
      memcpy(lpsz, get_data(), this->get_size());
      lpsz[this->get_size()] = '\0';
      str.ReleaseBuffer();
   }
   */


} // namespace primitive


#endif



