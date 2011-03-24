#include "StdAfx.h"

namespace primitive
{

   memory::memory(const void * pdata, int iCount)
   {
      m_iOffset = 0;
      Construct(NULL);
      allocate(iCount);
      ASSERT(fx_is_valid_address(pdata, iCount, FALSE));
      memcpy(m_pbStorage, pdata, iCount);
   }

   memory::memory(const memory & s)
   {
      operator = (s);
   }

   memory::memory(primitive::memory_container < memory > * pmsc, DWORD_PTR dwAllocationAddUp, UINT nAllocFlags)
   {
      UNREFERENCED_PARAMETER(nAllocFlags);
      UNREFERENCED_PARAMETER(dwAllocationAddUp);
      m_iOffset = 0;
      Construct(pmsc);
   }

   void memory::Construct(primitive::memory_container < memory > * pmsc, DWORD_PTR dwAllocationAddUp, UINT nAllocFlags)
   {
      UNREFERENCED_PARAMETER(nAllocFlags);
      m_iOffset = 0;
      m_bLockMode = false;
      m_bLock = false;
      m_pmsc = pmsc;

      m_pbStorage = NULL;
      m_cbStorage = 0;

      m_dwAllocation = 0;
      m_dwAllocationAddUp = dwAllocationAddUp;
   }


   memory::memory(primitive::memory_container < memory > * pmsc, void * pMemory, memory_size dwSize)
   {
      m_iOffset = 0;
      Construct(pmsc);
      allocate(dwSize);
      ASSERT(fx_is_valid_address(pMemory, dwSize, FALSE));
      memcpy(m_pbStorage, pMemory, dwSize);
   }

   memory::~memory()
   {
      if(m_pbStorage != NULL)
      {
         free(m_pbStorage);
         m_pbStorage = NULL;
      }
   }

   memory_size memory::GetStorageSize() const
   {
      return m_cbStorage;
   }

   memory_size memory::get_size() const
   {
      return m_cbStorage;
   }

   LPBYTE memory::GetAllocation() const
   {
      if(IsEnabled())
         return m_pbStorage + m_iOffset;
      else
      {
         ASSERT(FALSE);
         return NULL;
      }
   }

   LPBYTE memory::DetachStorage()
   {
      LPBYTE pbStorage = m_pbStorage;
      Construct(m_pmsc);
      return pbStorage;
   }


   bool memory::operator ==(memory& s)
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
   void memory::AllocateAddUp(memory_size dwAddUp)
   {
      allocate(m_cbStorage + dwAddUp);
   }

   bool memory::allocate(memory_size dwNewLength)
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
         DWORD_PTR dwAllocation = dwNewLength + m_dwAllocationAddUp;
         m_pbStorage = (LPBYTE) malloc(dwAllocation);
         if(m_pbStorage == NULL)
         {
            return false;
         }
         else 
         {
            m_dwAllocation = dwAllocation;
            m_cbStorage = dwNewLength;
            if(m_pmsc != NULL)
            {
               m_pmsc->OffsetStorageKeptPointers((int) m_pbStorage);
            }
            return true;
         }
      }
      else
      {
         if(dwNewLength > m_dwAllocation)
         {
            DWORD_PTR dwAllocation = dwNewLength + m_dwAllocationAddUp;
            LPVOID lpVoid = realloc(m_pbStorage, dwAllocation);
            if(lpVoid == NULL)
            {
   //            DWORD_PTR dw = GetLastError();
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

   void memory::FullLoad(ex1::file & file)
   {
   
      if(!IsEnabled())
      {
         ASSERT(false);
         return;
      }
   
      DWORD_PTR dwTemp;
      DWORD_PTR cbStorage = file.get_length();
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

   void memory::Lock()
   {
      m_csLock.Lock();
   }

   void memory::Unlock()
   {
      m_csLock.Unlock();
   }

   bool memory::IsLocked() const
   {
      return m_bLock;
   }

   bool memory::IsEnabled() const
   {
      if(m_bLockMode)
         return IsLocked();
      else
         return true;
      
   }

   void memory::copy_from(const memory *pstorage)
   {
      ASSERT(pstorage != NULL);
      allocate(pstorage->GetStorageSize());
      memcpy(GetAllocation(), pstorage->GetAllocation(), GetStorageSize());
   }

   void memory::set_data(void *pdata, memory_size uiSize)
   {
      allocate(uiSize);
      memcpy(GetAllocation(), pdata, uiSize);
   }

   void memory::delete_begin(memory_size iSize)
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

   void memory::eat_begin(void * pdata, memory_size iSize)
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

   void memory::_RemoveOffset()
   {
      if(m_pbStorage != NULL
         && m_cbStorage > m_iOffset) 
      {
         memmove(m_pbStorage, m_pbStorage + m_iOffset, m_cbStorage - m_iOffset);
      }
      m_iOffset = 0;
   }

   memory & memory::operator =(const memory & s)
   {
      if(this != &s)
      {
         Construct(s.m_pmsc);
         copy_from(&s);
      }
      return *this;
   }




   void memory::To(string & str, DWORD_PTR dwStart, DWORD_PTR dwEnd)
   {
      dwStart = max(dwStart, 0);
      if(dwEnd == MAX_DWORD_PTR)
         dwEnd = GetStorageSize() - 1;
      char * pch = (char *) GetAllocation();
      for(DWORD_PTR dw = dwStart; dw <= dwEnd; dw++)
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

   void memory::From(const char * psz)
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

   void memory::ToAsc(string & str)
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

   void memory::FromAsc(const char * psz)
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


   UINT memory::read(ex1::file & file)
   {
      DWORD_PTR dwEnd = file.get_length();
      DWORD_PTR dwPos = file.GetPosition();
      DWORD_PTR dwRemain = dwEnd - dwPos;
      allocate(dwRemain);
      DWORD_PTR dwRead = file.read(GetAllocation(), dwRemain);
      allocate(dwRead);
      return dwRead;
   }


   void memory::from_string(const wchar_t * pwsz)
   {
      from_string(gen::international::unicode_to_utf8(pwsz));
   }

   void memory::from_string(const char * psz)
   {
      allocate(strlen(psz));
      memcpy(GetAllocation(), psz, GetStorageSize());
   }

   void memory::to_string(string & str)
   {
      LPTSTR lpsz = str.GetBufferSetLength(GetStorageSize() + 1);
      memcpy(lpsz, GetAllocation(), GetStorageSize());
      lpsz[GetStorageSize()] = '\0';
      str.ReleaseBuffer();
   }

   void memory::write(ex1::output_stream & ostream)
   {
      ostream.write(GetAllocation(), GetStorageSize());
   }

   void memory::read(ex1::input_stream & istream)
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


   void memory::append(const void * pdata, DWORD_PTR iCount)
   {
      if(iCount <= 0)
         return;
      AllocateAddUp(iCount);
      memcpy(&GetAllocation()[GetStorageSize() - iCount], pdata, iCount);
   }


   void memory::assign(const void * pdata, DWORD_PTR iStart, DWORD_PTR iCount)
   {
      if(iCount < 0)
         iCount = 0;
      allocate(iCount);
      memcpy(m_pbStorage, &((LPBYTE)pdata)[iStart], iCount);
   }

   void memory::append(DWORD_PTR iCount, unsigned char uch)
   {
      if(iCount < 0)
         iCount = 0;
      AllocateAddUp(iCount);
      int iStart = GetStorageSize() - iCount;
      int iEnd = iStart + iCount -1;
      for(int i = iStart; i <= iEnd; i++)
      {
         m_pbStorage[i] = uch;
      }
   }

   void memory::assign(DWORD_PTR iCount, unsigned char uch)
   {
      if(iCount < 0)
         iCount = 0;
      allocate(iCount);
      int iEnd = iCount - 1;
      for(int i = 0; i <= iEnd; i++)
      {
         m_pbStorage[i] = uch;
      }
   }

   unsigned char memory::operator [] (int i) const
   {
      return m_pbStorage[i];
   }

   unsigned char & memory::operator [] (int i)
   {
      return m_pbStorage[i];
   }

   memory::operator const byte *() const
   {
      return m_pbStorage;
   }

   memory::operator byte *()
   {
      return m_pbStorage;
   }

   memory::operator const void *() const
   {
      return m_pbStorage;
   }

   memory::operator void *()
   {
      return m_pbStorage;
   }


} // namespace primitive