#pragma once


#include "aura/primitive/primitive_memory_container.h"


class memory_file;

   
typedef sp(memory_file) memory_file_sp;


class CLASS_DECL_AURA memory_file :
   virtual public ::file::file,
   virtual public primitive::memory_container
{
protected:

   
   memory_position_t      m_dwPosition;


public:
   
   memory_file(const memory_file & file);
   memory_file(memory_file && file);
   memory_file(::aura::application * papp, memory_size_t iSize = 0);
   memory_file(::aura::application * papp, void * pMemory, memory_size_t dwSize);
   memory_file(::aura::application * papp, const memory_file & memoryfile);
   memory_file(::aura::application * papp, ::primitive::memory_base * pmemory);
   virtual ~memory_file();


   virtual bool IsValid() const;
   memory_size_t remove_begin(void * lpBuf, memory_size_t uiCount);
   void load_string(string & str);
   using ::object::create;
   void create(memory_size_t iSize = -1);
   file_position_t seek(file_offset_t lOff, ::file::e_seek  nFrom);
   file_position_t get_position() const;

   virtual string GetFilePath() const;

   virtual ::primitive::memory_base * create_memory();

   void set_length(file_size_t dwNewLen);
   file_size_t get_length() const;
   void Truncate(file_size_t iPosition);
   void clear();
      
   using ::file::file::read;
   virtual memory_size_t read(void *lpBuf, memory_size_t nCount);
      
   using ::file::file::write;
   virtual void write(const void * lpBuf, memory_size_t nCount);
   virtual void write_from_hex(const void * lpBuf,memory_size_t nCount);

   virtual uint64_t GetBufferPtr(UINT nCommand, uint64_t nCount = 0, void ** ppBufStart = NULL, void ** ppBufMax = NULL);

   void flush();


   virtual void full_load(var varFile);

   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;

   using ::file::file::get_internal_data;
   virtual void * get_internal_data();
   virtual memory_size_t get_internal_data_size() const;
   virtual bool set_internal_data_size(memory_size_t c);

   virtual void transfer_to(writer & writer, memory_size_t uiBufferSize = 1024 * 1024);

   void copy_this(const memory_file & file);

   memory_file & operator = (const memory_file & file);

   memory_size_t read_inline(void *lpBuf, memory_size_t nCount)
   {

      memory_offset_t iDiff = m_spmemory.m_p->m_cbStorage - m_dwPosition;

      if (iDiff <= 0)
         return 0;

      if (nCount > iDiff)
         nCount = iDiff;

      if (nCount == 1)
      {
         
         *((byte*)lpBuf) = m_spmemory.m_p->m_pbStorage[m_dwPosition];

      }
      else if (nCount == 2)
      {

         *((uint16_t *)lpBuf) = *((uint16_t *)&m_spmemory.m_p->m_pbStorage[m_dwPosition]);

      }
      else if (nCount == 4)
      {

         *((uint32_t*)lpBuf) = *((uint32_t*)&m_spmemory.m_p->m_pbStorage[m_dwPosition]);

      }
      else if (nCount == 8)
      {

         *((uint64_t *)lpBuf) = *((uint64_t *)&m_spmemory.m_p->m_pbStorage[m_dwPosition]);

      }
      else
      {

         memcpy(lpBuf, &m_spmemory.m_p->m_pbStorage[m_dwPosition], (size_t)nCount);

      }

      m_dwPosition += nCount;

      return nCount;
   }


   void write_inline(const void * lpBuf, memory_size_t nCount)
   {

      if (nCount <= 0)
         return;

      memory_size_t iEndPosition = m_dwPosition + nCount;

      if (iEndPosition <= 0)
      {
         
         m_dwPosition = 0;
         
         return;

      }

      if (m_spmemory.is_null() || iEndPosition > m_spmemory->get_size())
      {

         allocate(iEndPosition);

      }

      LPBYTE lpb = get_data();

      //ASSERT(__is_valid_address(&(lpb)[m_dwPosition], (uint_ptr)nCount, TRUE));

      memcpy(&(lpb)[m_dwPosition], lpBuf, (size_t)nCount);

      m_dwPosition = (memory_position_t)iEndPosition;

   }

};


