#include "StdAfx.h"

file_avio::file_avio()
{
   m_dwSize = 1048576;
   m_puchData = (byte *) av_malloc(m_dwSize);
}


file_avio::~file_avio()
{
   av_free(m_puchData);
}

int file_avio::read(void * opaque, uint8_t * buf, int buf_size)
{
   return static_cast < file_avio * >(opaque)->m_spfile->read(reinterpret_cast<char*>(buf), buf_size);
}

int file_avio::write(void * opaque, unsigned char * buf, int buf_size)
{
   static_cast < file_avio * >(opaque)->m_spfile->write(reinterpret_cast<char*>(buf), buf_size);
   return buf_size;
}

int64_t file_avio::seek(void *opaque, int64_t offset, int whence)
{
   if(whence == AVSEEK_SIZE)
      return static_cast < file_avio * >(opaque)->m_spfile->get_length();

   int iSeekCur = SEEK_CUR;
   int iSeekEnd = SEEK_END;
   int iSeekBeg = SEEK_SET;

   ::ex1::e_seek eseek;
   switch(whence)
   {
   case SEEK_CUR:
      eseek = ::ex1::seek_current;
      break;
   case SEEK_END:
      eseek = ::ex1::seek_end;
      break;
   case SEEK_SET:
      eseek = ::ex1::seek_begin;
      break;
   };

   return static_cast < file_avio * >(opaque)->m_spfile->seek(offset, (::ex1::e_seek) eseek);
}

AVIOContext * file_avio::alloc_context(::ex1::file * pfile, int iWrite)
{
   
   m_spfile = pfile;
   
   AVIOContext * pcontext =  avio_alloc_context(m_puchData, m_dwSize, iWrite, this, &file_avio::read, &file_avio::write, &file_avio::seek);
   
   if(pcontext == NULL)
   {
      return NULL;
   }

   pcontext->is_streamed = 1;

   return pcontext;
}
