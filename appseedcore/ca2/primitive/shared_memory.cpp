#include "StdAfx.h"

namespace primitive
{

   shared_memory::shared_memory(const shared_memory & s)
   {
      operator = (s);
   }

   shared_memory::shared_memory(primitive::memory_container < shared_memory > * pmsc, DWORD dwAllocationAddUp, UINT nAllocFlags)
   {
      m_iOffset = 0;
      Construct(pmsc, dwAllocationAddUp, nAllocFlags);
   }

   void shared_memory::Construct(primitive::memory_container < shared_memory > * pmsc, DWORD dwAllocationAddUp, UINT nAllocFlags)
   {
      m_nAllocFlags = nAllocFlags;
      m_hGlobalMemory = NULL;
      m_bAllowGrow = TRUE;
      m_iOffset = 0;
      m_bLockMode = false;
      m_bLock = false;
      m_pmsc = pmsc;

      m_pbStorage = NULL;
      m_cbStorage = 0;

      m_dwAllocation = 0;
      m_dwAllocationAddUp = dwAllocationAddUp;
   }


   shared_memory::shared_memory(primitive::memory_container < shared_memory > * pmsc, void * pMemory, memory_size dwSize)
   {
      m_iOffset = 0;
      Construct(pmsc);
      allocate(dwSize);
      ASSERT(fx_is_valid_address(pMemory, dwSize, FALSE));
      memcpy(m_pbStorage, pMemory, dwSize);
   }

   shared_memory::~shared_memory()
   {
      if(m_pbStorage != NULL)
      {
         free(m_pbStorage);
         m_pbStorage = NULL;
      }
   }

   memory_size shared_memory::GetStorageSize() const
   {
      return m_cbStorage;
   }

   LPBYTE shared_memory::GetAllocation() const
   {
      if(IsEnabled())
         return m_pbStorage + m_iOffset;
      else
      {
         ASSERT(FALSE);
         return NULL;
      }
   }

   LPBYTE shared_memory::DetachStorage()
   {
      LPBYTE pbStorage = m_pbStorage;
      Construct(m_pmsc);
      return pbStorage;
   }


   bool shared_memory::operator ==(shared_memory& s)
   {
      bool b = false;
      Lock();
      s.Lock();
       if(GetStorageSize() == s.GetStorageSize())
         b = memcmp(GetAllocation(), s.GetAllocation(), GetStorageSize()) == 0;
      s.Unlock(),
      Unlock();
       return b;
   }
   void shared_memory::AllocateAddUp(memory_size dwAddUp)
   {
      allocate(m_cbStorage + dwAddUp);
   }

   bool shared_memory::allocate(memory_size dwNewLength)
   {
      if(!IsEnabled())
      {
         ASSERT(FALSE);
         return false;
      }
   
      if(dwNewLength <= 0)
      {
         m_iOffset = 0;
         m_cbStorage = 0;
         return true;
      }
   

      _RemoveOffset();
   
   
      if(m_pbStorage == NULL)
      {

         m_iOffset = 0;
         DWORD dwAllocation = dwNewLength + m_dwAllocationAddUp;
         m_pbStorage = (LPBYTE) Alloc(dwAllocation);
         if(m_pbStorage != NULL)
         {
            m_dwAllocation = dwAllocation;
            m_cbStorage = dwNewLength;
            if(m_pmsc != NULL)
            {
               m_pmsc->OffsetStorageKeptPointers((int) m_pbStorage);
            }
            return true;
         }
         else
         {
            return false;
         }
      }
      else
      {
         if(dwNewLength > m_dwAllocation)
         {
            DWORD dwAllocation = dwNewLength + m_dwAllocationAddUp;
            LPVOID lpVoid = Realloc(m_pbStorage, dwAllocation);
            if(lpVoid == NULL)
            {
   //            DWORD dw = GetLastError();
               return false;
            }
            else
            {
               int iOffset = (LPBYTE) lpVoid - m_pbStorage;
               if(m_pmsc != NULL)
               {
                  m_pmsc->OffsetStorageKeptPointers(iOffset);
               }
            
               m_dwAllocation = dwAllocation;
               m_pbStorage = (LPBYTE) lpVoid;
               m_cbStorage = dwNewLength;
               return true;
            }
         }
         else
         {
            m_cbStorage = dwNewLength;
            return true;
         }
      
      }
   }

   void shared_memory::FullLoad(ex1::file & file)
   {
   
      if(!IsEnabled())
      {
         ASSERT(false);
         return;
      }
   
      DWORD dwTemp;
      DWORD cbStorage = file.get_length();
      file.seek_to_begin();
      allocate(cbStorage);
      try
      {
         dwTemp = file.read(GetAllocation(), cbStorage);
      }
      catch(ex1::file_exception_sp * pe)
      {
           TRACE0("smfOpenFile: read error on image!");
   #ifdef _DEBUG
          (*pe)->dump(afxdump);
   #endif 
          delete pe;
      }
      if (cbStorage != dwTemp)
      {
         TRACE0("smfOpenFile: read error on image!");
      }
   }

   void shared_memory::Lock()
   {
      m_csLock.Lock();
   }

   void shared_memory::Unlock()
   {
      m_csLock.Unlock();
   }

   bool shared_memory::IsLocked() const
   {
      return m_bLock;
   }

   bool shared_memory::IsEnabled() const
   {
      if(m_bLockMode)
         return IsLocked();
      else
         return true;
      
   }

   void shared_memory::copy_from(const shared_memory *pstorage)
   {
      ASSERT(pstorage != NULL);
      allocate(pstorage->GetStorageSize());
      memcpy(GetAllocation(), pstorage->GetAllocation(), GetStorageSize());

   }

   void shared_memory::set_data(void *pdata, memory_size uiSize)
   {
      allocate(uiSize);
      memcpy(GetAllocation(), pdata, uiSize);
   }

   /*void shared_memory::delete_begin(memory_size iSize)
   {
      ASSERT(iSize >= 0);
      ASSERT(iSize <= GetStorageSize());
      if(iSize >= 0 &&
         iSize <= GetStorageSize())
      {
         m_iOffset += iSize;
         if(m_pmsc != NULL)
         {
            m_pmsc->OffsetStorageKeptPointers(iSize);
         }
         m_cbStorage -= iSize;
      }
   }*/

   void shared_memory::_RemoveOffset()
   {
      if(m_pbStorage != NULL
         && m_cbStorage > m_iOffset) 
      {
         memmove(m_pbStorage, m_pbStorage + m_iOffset, m_cbStorage - m_iOffset);
      }
      m_iOffset = 0;
   }

   shared_memory & shared_memory::operator =(const shared_memory & s)
   {
      if(this != &s)
      {
         Construct(s.m_pmsc);
         copy_from(&s);
      }
      return *this;
   }




   void shared_memory::To(string & str, int iStart, int iEnd)
   {
      iStart = max(iStart, 0);
      if(iEnd == -1)
         iEnd = GetStorageSize() - 1;
      char * pch = (char *) GetAllocation();
      for(int i = iStart; i <= iEnd; i++)
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
      int iLen = strlen(psz);
      allocate(iLen / 2);
      char * pch = (char *) GetAllocation();
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
      int iLen = strTo.get_length() - 1;
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
   }


   UINT shared_memory::read(ex1::file & file)
   {
      DWORD dwEnd = file.get_length();
      DWORD dwPos = file.GetPosition();
      DWORD dwRemain = dwEnd - dwPos;
      allocate(dwRemain);
      DWORD dwRead = file.read(GetAllocation(), dwRemain);
      allocate(dwRead);
      return dwRead;
   }


   void shared_memory::from_string(const wchar_t * pwsz)
   {
      from_string(gen::international::unicode_to_utf8(pwsz));
   }

   void shared_memory::from_string(const char * psz)
   {
      allocate(strlen(psz));
      memcpy(GetAllocation(), psz, GetStorageSize());
   }

   void shared_memory::to_string(string & str)
   {
      LPTSTR lpsz = str.GetBufferSetLength(GetStorageSize() + 1);
      memcpy(lpsz, GetAllocation(), GetStorageSize());
      lpsz[GetStorageSize()] = '\0';
      str.ReleaseBuffer();
   }


   void shared_memory::write(ex1::output_stream & ostream)
   {
      ostream.write(GetAllocation(), GetStorageSize());
   }

   void shared_memory::read(ex1::input_stream & istream)
   {
      UINT uiRead;
      UINT uiBufSize = 1024 + 1024;
      UINT uiSize = 0;
   
      while(true)
      {
         allocate(uiSize + uiBufSize);
         uiRead = istream.read(&GetAllocation()[uiSize], uiBufSize);
         if(uiRead < uiBufSize)
         {
            allocate(uiSize + uiRead);
            break;
         }
         uiSize += uiBufSize;
      }
   }



   void shared_memory::SetHandle(HGLOBAL hGlobalMemory, BOOL bAllowGrow)
   {
      UNREFERENCED_PARAMETER(bAllowGrow);
      ASSERT(m_hGlobalMemory == NULL);        // do once only
      ASSERT(m_pbStorage == NULL);     // do once only

      if (hGlobalMemory == NULL) 
      {
         AfxThrowInvalidArgException();
      }

      m_hGlobalMemory = hGlobalMemory;
      m_pbStorage = (BYTE*)::GlobalLock(m_hGlobalMemory);
      m_dwAllocation = m_cbStorage = (ULONG)::GlobalSize(m_hGlobalMemory);
      // xxx m_bAllowGrow = bAllowGrow;
   }

   BYTE* shared_memory::Alloc(SIZE_T nBytes)
   {
      ASSERT(m_hGlobalMemory == NULL);        // do once only
      m_hGlobalMemory = ::GlobalAlloc(m_nAllocFlags, nBytes);
      if (m_hGlobalMemory == NULL)
         return NULL;
      return (BYTE*)::GlobalLock(m_hGlobalMemory);
   }

   BYTE* shared_memory::Realloc(BYTE*, SIZE_T nBytes)
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
      return (BYTE*)::GlobalLock(m_hGlobalMemory);
   }

   void shared_memory::Free(BYTE*)
   {
      ASSERT(m_hGlobalMemory != NULL);
      ::GlobalUnlock(m_hGlobalMemory);
      ::GlobalFree(m_hGlobalMemory);
   }

   HGLOBAL shared_memory::Detach()
   {
      HGLOBAL hMem;
      ASSERT(m_hGlobalMemory != NULL);
      hMem = m_hGlobalMemory;

      ::GlobalUnlock(m_hGlobalMemory);
      m_hGlobalMemory = NULL; // detach from global handle

      // re-initialize the CMemFile parts too
      m_pbStorage = NULL;
      m_dwAllocation = m_cbStorage = 0;

      return hMem;
   }

   void shared_memory::delete_begin(memory_size iSize)
   {
      ASSERT(iSize >= 0);
      ASSERT(iSize <= GetStorageSize());
      if(iSize >= 0 &&
         iSize <= GetStorageSize())
      {
         m_iOffset += iSize;
         if(m_pmsc != NULL)
         {
            m_pmsc->OffsetStorageKeptPointers(iSize);
         }
         m_cbStorage -= iSize;
      }
   }

   void shared_memory::eat_begin(void * pdata, memory_size iSize)
   {
      ASSERT(iSize >= 0);
      ASSERT(iSize <= GetStorageSize());
      if(iSize >= 0 &&
         iSize <= GetStorageSize())
      {
         memcpy(pdata, GetAllocation(), iSize);
         delete_begin(iSize);
      }
   }

} // namespace primitive

