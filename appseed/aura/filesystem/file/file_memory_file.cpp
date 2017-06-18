//#include "framework.h"

memory_file::memory_file(const memory_file & m) :
   object((const object &)m),
   file((const file &)m),
   memory_container((const memory_container &)m)
{

   m_dwPosition = m.m_dwPosition;

}

memory_file::memory_file(memory_file && m) :
   object(m),
   file(m),
   memory_container(m)
{

   m_dwPosition = m.m_dwPosition;

}

memory_file::memory_file(::aura::application * papp, memory_size_t iSize) :
   object(papp),
   memory_container(papp)
{

   m_dwPosition = 0;

   if (iSize > 0)
   {
      create(iSize);
   }

}


memory_file::memory_file(::aura::application * papp, void * pMemory, memory_size_t dwSize) :
   object(papp),
   memory_container(papp, pMemory, dwSize)
{

   m_dwPosition = 0;

}


memory_file::memory_file(::aura::application * papp, const memory_file & memoryfile) :
   object(papp),
   memory_container(papp, ((memory_file &)memoryfile).get_memory())
{

   m_dwPosition = 0;

}


memory_file::memory_file(::aura::application * papp, ::primitive::memory_base * pmemory) :
   object(papp),
   memory_container(papp, pmemory)
{

   m_dwPosition = 0;

}


memory_file::~memory_file()
{

}


memory_size_t memory_file::read(void *lpBuf, memory_size_t nCount)
{

   return read_inline(lpBuf, nCount);
   
}


void memory_file::write(const void * lpBuf, memory_size_t nCount)
{

   write_inline(lpBuf, nCount);

}

void memory_file::write_from_hex(const void * lpBuf, memory_size_t nCount)
{

   single_lock sl(get_memory()->m_spmutex, TRUE);

   char ch;

   strsize iLen = nCount;

   if ((iLen % 2) != 0)
   {

      iLen++;

   }

   memory_size_t iEndPosition = m_dwPosition + iLen / 2;

   if (iEndPosition > this->get_size())
   {

      allocate(iEndPosition);

   }

   if (iEndPosition <= 0)
   {

      m_dwPosition = 0;

      return;

   }

   LPBYTE lpb = get_data();

   ASSERT(__is_valid_address(&(lpb)[m_dwPosition], (uint_ptr)nCount, TRUE));

   char * pch = (char *)&(lpb)[m_dwPosition];

   const char * psz = (const char *)lpBuf;

   bool bEven = true;

   while (nCount > 0)
   {

      if (bEven)
      {

         ch = 0;

         if (*psz > '9')
            ch |= ((*psz - 'A' + 10) & 0x0f) << 4;
         else
            ch |= ((*psz - '0') & 0x0f) << 4;

         if (*psz == '\0')
            break;

      }
      else
      {

         if (*psz > '9')
            ch |= ((*psz - 'A' + 10) & 0x0f);
         else
            ch |= ((*psz - '0') & 0x0f);

         *pch = ch;

         pch++;

      }

      psz++;

      nCount--;

      bEven = !bEven;

   }

   if (bEven)
   {
      *(pch - 1) = ch;
   }

   m_dwPosition = (memory_position_t)iEndPosition;
}

void memory_file::Truncate(file_size_t size)
{

   single_lock sl(get_memory()->m_spmutex, TRUE);

   allocate((memory_size_t)size);

   if (m_dwPosition > (memory_position_t)size)
      m_dwPosition = (memory_position_t)size;


}



void memory_file::clear()
{

   single_lock sl(get_memory()->m_spmutex, TRUE);

   m_dwPosition = 0;

   Truncate(0);

}


file_size_t memory_file::get_length() const
{
   ASSERT(IsValid());
   return (file_size_t) this->get_size();
}



file_position_t memory_file::get_position() const
{
   if (!IsValid())
      throw io_exception(get_app(), "memory_file::get_position");
   return (file_position_t)m_dwPosition;
}


file_position_t memory_file::seek(file_offset_t lOff, ::file::e_seek nFrom)
{

   single_lock sl(get_memory()->m_spmutex, TRUE);

   ASSERT(IsValid());
   ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
   //ASSERT(::file::seek_begin == FILE_BEGIN && ::file::seek_end == FILE_END && ::file::seek_current == FILE_CURRENT);

   memory_position_t dwNew = (memory_position_t)-1;

   switch (nFrom)
   {
   case ::file::seek_begin:
      dwNew = (memory_position_t)lOff;
      break;
   case ::file::seek_end:
      dwNew = (memory_position_t)(get_length() + lOff);
      break;
   case ::file::seek_current:
      if (lOff < 0)
      {
         dwNew = (memory_position_t)(m_dwPosition + lOff);
         if (dwNew > m_dwPosition)
            dwNew = 0;
      }
      else
      {
         dwNew = (memory_position_t)(m_dwPosition + lOff);
      }

      break;
   default:
      return ::numeric_info< memory_position_t >::allset();
   }

   m_dwPosition = dwNew;

   //if(dwNew > this->get_size())
      //allocate((memory_size_t) dwNew);

   return (file_position_t)dwNew;
}


void memory_file::create(memory_size_t iSize)
{

   allocate(iSize);

}


void memory_file::load_string(string &str)
{
   char * lpsz = str.GetBuffer((int32_t)(this->get_size() + 1));
   memcpy(lpsz, get_data(), (size_t) this->get_size());
   lpsz[this->get_size()] = 0;
   str.ReleaseBuffer();
}


memory_size_t memory_file::remove_begin(void *lpBuf, memory_size_t uiCount)
{

   single_lock sl(get_memory()->m_spmutex, TRUE);

   ASSERT(IsValid());

   if (uiCount > get_memory()->m_cbStorage)
   {

      uiCount = get_memory()->m_cbStorage;

   }

   if (lpBuf != NULL)
   {

      memcpy(lpBuf, get_data(), (size_t)uiCount);

   }

   if (m_dwPosition <= uiCount)
   {

      m_dwPosition = 0;

   }
   else
   {

      m_dwPosition -= uiCount;

   }

   get_memory()->delete_begin(uiCount);

   return uiCount;

}


bool memory_file::IsValid() const
{
   return memory_container::IsValid();
}


string memory_file::GetFilePath() const
{
   return file::GetFilePath();
}


uint64_t memory_file::GetBufferPtr(UINT nCommand, uint64_t nCount, void ** ppBufStart, void ** ppBufMax)
{
   UNREFERENCED_PARAMETER(nCommand);
   UNREFERENCED_PARAMETER(nCount);
   UNREFERENCED_PARAMETER(ppBufStart);
   UNREFERENCED_PARAMETER(ppBufMax);
   return 0;
}


void memory_file::flush()
{
}


void memory_file::set_length(file_size_t dwNewLen)
{
   Truncate(dwNewLen);
}


void memory_file::assert_valid() const
{
   file::assert_valid();
}

void memory_file::dump(dump_context & dumpcontext) const
{
   file::dump(dumpcontext);
}





void memory_file::full_load(var varFile)
{

   single_lock sl(get_memory()->m_spmutex, TRUE);

   ASSERT(IsValid());

   ::file::file_sp spfile = Application.file().get_file(varFile, ::file::type_binary | ::file::mode_read | ::file::share_deny_none);
   
   if (spfile.is_null())
   {

      return;

   }

   memory storage;

   storage.allocate(1024 * 1024 * 8);

   memory_size_t uiRead;

   while ((uiRead = spfile->read(storage.get_data(), storage.get_size())) > 0)
   {

      write(storage.get_data(), uiRead);

   }

}


::primitive::memory_base * memory_file::create_memory()
{

   return canew(memory(this));

}


void * memory_file::get_internal_data()
{

   return get_data();

}


memory_size_t memory_file::get_internal_data_size() const
{

   return get_size();

}


bool memory_file::set_internal_data_size(memory_size_t c)
{

   Truncate(c);

   return c == get_internal_data_size();

}

void memory_file::transfer_to(writer & writer, memory_size_t uiSize)
{

   if (get_internal_data() == NULL || get_internal_data_size() <= 0)
      return;

   if (uiSize > get_internal_data_size())
      uiSize = get_internal_data_size();

   if (writer.increase_internal_data_size(uiSize) && writer.get_internal_data() != NULL)
   {

      if (writer.get_internal_data() == get_internal_data())
         return;

      memmove(((byte *)writer.get_internal_data()) + writer.get_position() + uiSize, ((byte *)writer.get_internal_data()) + writer.get_position(), writer.get_internal_data_size() - uiSize);
      memcpy(((byte *)writer.get_internal_data()) + writer.get_position(), get_internal_data(), uiSize);
      writer.seek(get_internal_data_size(), ::file::seek_current);

   }
   else
   {

      writer.write(get_internal_data(), uiSize);

   }

}


void memory_file::copy_this(const memory_file & file)
{

   m_dwPosition = file.m_dwPosition;

}


memory_file & memory_file::operator = (const memory_file & file)
{

   if (&file == this)
   {
    
      return *this;

   }

   ::object::copy_this(file);

   ::file::file::copy_this(file);

   memory_container::copy_this(file);

   return *this;

}