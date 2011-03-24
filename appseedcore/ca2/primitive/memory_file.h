#pragma once

namespace primitive
{

   template < class MEMORY >
   class memory_file :
      virtual public ex1::file,
      virtual public primitive::memory_container < MEMORY >
   {
   protected:

   
      DWORD_PTR   m_dwPosition;


   public:
   
      bool     m_bSynch;


      memory_file(::ca::application * papp, DWORD_PTR iSize = 0);
      memory_file(::ca::application * papp, void * pMemory, DWORD_PTR dwSize);
      memory_file(::ca::application * papp, const memory_file & memoryfile);
      memory_file(::ca::application * papp, MEMORY & storage);
      virtual ~memory_file < MEMORY >();

      virtual bool IsValid() const;
      int RemoveBegin(void * lpBuf, DWORD_PTR uiCount);
      void load_string(string & str);
      void create(DWORD_PTR iSize = -1);
      void seek_to_begin();
      INT_PTR seek(INT_PTR lOff, UINT nFrom);
      DWORD_PTR GetPosition() const;

      virtual string GetFilePath() const;

      void SetLength(DWORD_PTR dwNewLen);
      DWORD_PTR get_length() const;
      void Truncate(DWORD_PTR iPosition);
      void clear();
      virtual DWORD_PTR read(void *lpBuf, DWORD_PTR nCount);
      virtual void write(const void * lpBuf, DWORD_PTR nCount);

      virtual DWORD_PTR GetBufferPtr(UINT nCommand, DWORD_PTR nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);

      void Flush();


      virtual void full_load(const char * psz);

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


   };




   template < class MEMORY >
   memory_file < MEMORY >::memory_file(::ca::application * papp, DWORD_PTR iSize) :
      ca(papp),
      primitive_memory_container (papp)
   {
      m_bSynch = false;
      m_dwPosition = 0;
      if(iSize >= 0)
      {
         create(iSize);
      }
   }

   template < class MEMORY >
   memory_file < MEMORY >::memory_file(::ca::application * papp, void * pMemory, DWORD_PTR dwSize) :
      ca(papp),
      primitive::memory_container < primitive::memory > (papp, pMemory, dwSize)
   {
      m_bSynch = false;
      m_dwPosition = 0;
   }

   template < class MEMORY >
   memory_file < MEMORY >::memory_file(::ca::application * papp, const memory_file < MEMORY > & memoryfile) :
      ca(papp),
      primitive::memory_container < primitive::memory > (papp, *memoryfile.get_memory())
   {
      m_bSynch = false;
      m_dwPosition = 0;
   }

   template < class MEMORY >
   memory_file < MEMORY >::memory_file(::ca::application * papp, MEMORY & storage) :
      ca(papp),
      primitive::memory_container < MEMORY > (papp, storage)
   {
      m_bSynch = false;
      m_dwPosition = 0;
   }

   template < class MEMORY >
   memory_file < MEMORY >::~memory_file()
   {

   }

   template < class MEMORY >
   DWORD_PTR memory_file < MEMORY >::read(void *lpBuf, DWORD_PTR nCount)
   {
      ::ca::lock lockMemory(m_bSynch ? m_pmemorystorage : NULL, true);
      ASSERT(IsValid());

      if(m_dwPosition >= get_size())
         return 0;

      if(nCount >= get_size())
      {
         nCount -= m_dwPosition;
      }

      if(nCount + m_dwPosition > get_size())
         nCount = get_size() - m_dwPosition;

      memcpy(lpBuf, &((LPBYTE)GetAllocation())[m_dwPosition], nCount);
   
      m_dwPosition += nCount;

      return nCount;
   }

   template < class MEMORY >
   void memory_file < MEMORY >::write(const void * lpBuf, DWORD_PTR nCount)
   {
      ::ca::lock lockMemory(m_bSynch ? m_pmemorystorage : NULL, true);
      ASSERT(IsValid());

      DWORD_PTR iEndPosition = m_dwPosition + nCount;
      if(iEndPosition >= (int) get_size())
      {
         allocate(iEndPosition );
      }

      if(iEndPosition <= 0)
      {
         m_dwPosition = 0;
         return;
      }
   
      LPBYTE lpb = GetAllocation();

      ASSERT(fx_is_valid_address(&(lpb)[m_dwPosition], nCount, TRUE));

      memcpy(&(lpb)[m_dwPosition], lpBuf, nCount);

      m_dwPosition = iEndPosition;
   }

   template < class MEMORY >
   void memory_file < MEMORY >::Truncate(DWORD_PTR iPosition)
   {
      ::ca::lock lockMemory(m_bSynch ? m_pmemorystorage : NULL, true);
      allocate(iPosition);
      if(m_dwPosition > iPosition)
         m_dwPosition = iPosition;


   }
   
   
   template < class MEMORY >
   void memory_file < MEMORY >::clear()
   {
      ::ca::lock lockMemory(m_bSynch ? m_pmemorystorage : NULL, true);
       m_dwPosition = 0;
       Truncate(0);
   }

   template < class MEMORY >
   DWORD_PTR memory_file < MEMORY >::get_length() const
   {
      ASSERT(IsValid());
       return get_size();
   }


   template < class MEMORY >
   DWORD_PTR memory_file < MEMORY >::GetPosition() const
   {
      ASSERT(IsValid());
      return m_dwPosition;
   }

   template < class MEMORY >
   void memory_file < MEMORY >::seek_to_begin()
   {
      ASSERT(IsValid());
       m_dwPosition = 0;

   }

   template < class MEMORY >
   INT_PTR memory_file < MEMORY >::seek(INT_PTR lOff, UINT nFrom)
   {
      ::ca::lock lockMemory(m_bSynch ? m_pmemorystorage : NULL, true);
      ASSERT(IsValid());
      ASSERT(nFrom == ::ex1::seek_begin || nFrom == ::ex1::seek_end || nFrom == ::ex1::seek_current);
      ASSERT(::ex1::seek_begin == FILE_BEGIN && ::ex1::seek_end == FILE_END && ::ex1::seek_current == FILE_CURRENT);

      DWORD_PTR dwNew = (DWORD_PTR) -1;

      switch(nFrom)
      {
      case ::ex1::seek_begin:
         dwNew = lOff;
         break;
      case ::ex1::seek_end:
         dwNew = get_length() - lOff;
         break;
      case ::ex1::seek_current:
         if(lOff < 0)
         {
            dwNew = m_dwPosition + lOff;
            if(dwNew > m_dwPosition)
               dwNew = 0;
         }
         else
         {
            dwNew = m_dwPosition + lOff;
         }
      
         break;
      default:
         return -1;
      }

      m_dwPosition = dwNew;

      if(dwNew > get_size())
         allocate(dwNew);

      return dwNew;
   }

   template < class MEMORY >
   void memory_file < MEMORY >::create(DWORD_PTR iSize)
   {
      allocate(iSize);
   }

   template < class MEMORY >
   void memory_file < MEMORY >::load_string(string &str)
   {
      LPTSTR lpsz = str.GetBuffer(get_size() + 1);
      memcpy(lpsz, GetAllocation(), get_size());
      lpsz[get_size()] = 0;
      str.ReleaseBuffer();
   }

   template < class MEMORY >
   int memory_file < MEMORY >::RemoveBegin(void *lpBuf, DWORD_PTR uiCount)
   {
      ::ca::lock lockMemory(m_bSynch ? m_pmemorystorage : NULL, true);
      ASSERT(IsValid());
      if(uiCount > get_size())
         uiCount = get_size();
      if(lpBuf != NULL)
      {
         memcpy(lpBuf, ((LPBYTE)GetAllocation()), uiCount);
      }
      if(uiCount < get_size())
      {
         memmove(
            GetAllocation(), 
            &((LPBYTE)GetAllocation())[uiCount],
            get_size() - uiCount);
      }
   
      if(m_dwPosition <= uiCount)
         m_dwPosition = 0;
      else
         m_dwPosition -= uiCount;


      allocate(get_size() - uiCount);

      return uiCount;

   }

   template < class MEMORY >
   bool memory_file < MEMORY >::IsValid() const
   {
      return primitive_memory_container::IsValid() && !(m_dwPosition & 0x80000000);
   }

   template < class MEMORY >
   string memory_file < MEMORY >::GetFilePath() const
   {
      return L"";
   }

   template < class MEMORY >
   DWORD_PTR memory_file < MEMORY >::GetBufferPtr(UINT nCommand, DWORD_PTR nCount, void ** ppBufStart, void ** ppBufMax)
   {
      UNREFERENCED_PARAMETER(nCommand);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(ppBufStart);
      UNREFERENCED_PARAMETER(ppBufMax);
      return 0;
   }

   template < class MEMORY >
   void memory_file < MEMORY >::Flush()
   {
   }

   template < class MEMORY >
   void memory_file < MEMORY >::SetLength(DWORD_PTR dwNewLen)
   {
      Truncate(dwNewLen);
   }


   #ifdef _DEBUG
   template < class MEMORY >
   void memory_file < MEMORY >::assert_valid() const
   {
      file::assert_valid();
   }
   template < class MEMORY >
   void memory_file < MEMORY >::dump(dump_context & dumpcontext) const
   {
      file::dump(dumpcontext);
   }
   #endif




   template < class MEMORY >
   void memory_file < MEMORY >::full_load(const char * psz)
   {
      ::ca::lock lockMemory(m_bSynch ? m_pmemorystorage : NULL, true);
      ASSERT(IsValid());

      MEMORY storage;
      storage.allocate(1024 * 1024 * 8);   
      ex1::filesp spfile(get_app());
      if(!spfile->open(psz, ::ex1::file::type_binary | ::ex1::file::mode_read | ::ex1::file::shareDenyNone))
         return;
      else
      {
         UINT_PTR uiRead;
         while((uiRead = spfile->read(storage.GetAllocation(), storage.GetStorageSize())) > 0)
         {
            write(storage.GetAllocation(), uiRead);
         }
      }
   }

} // namespace primitive


