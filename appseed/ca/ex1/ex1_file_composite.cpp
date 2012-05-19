#include "framework.h"


namespace ex1
{


   file_composite::file_composite()
   {
   }

   file_composite::file_composite(file * pfile)
   {

      m_spfile = pfile;

   }

   file_composite::operator HFILE() const
   {
      return m_spfile->operator HFILE();
   }

   file_position file_composite::get_position() const
   {

      return m_spfile->get_position();

   }

   bool file_composite::GetStatus(file_status& rStatus) const
   {

      return m_spfile->GetStatus(rStatus);

   }

   string file_composite::GetFileName() const
   {

      return m_spfile->GetFileName();

   }

   string file_composite::GetFileTitle() const
   {

      return m_spfile->GetFileTitle();

   }
   
   string file_composite::GetFilePath() const
   {

      return m_spfile->GetFilePath();

   }

   void file_composite::SetFilePath(const char * lpszNewName)
   {

      return m_spfile->SetFilePath(lpszNewName);

   }

   bool file_composite::open(const char * lpszFileName, UINT nOpenFlags, file_exception_sp * pError)
   {

      return m_spfile->open(lpszFileName, nOpenFlags, pError);

   }

   bool file_composite::GetStatus(const char * lpszFileName, file_status& rStatus)
   {

      return m_spfile->GetStatus(lpszFileName, rStatus);

   }

   void file_composite::SetStatus(const char * lpszFileName, const file_status& status)
   {

      return m_spfile->SetStatus(lpszFileName, status);

   }

   file * file_composite::Duplicate() const
   {

      return m_spfile->Duplicate();

   }

   file_position file_composite::seek(file_offset lOff, ::ex1::e_seek  nFrom)
   {

      return m_spfile->seek(lOff, nFrom);

   }

   void file_composite::set_length(file_size dwNewLen)
   {

      return m_spfile->set_length(dwNewLen);

   }
   
   file_size file_composite::get_length() const
   {

      return m_spfile->get_length();

   }

   void file_composite::LockRange(file_position dwPos, file_size dwCount)
   {

      return m_spfile->LockRange(dwPos, dwCount);

   }

   void file_composite::UnlockRange(file_position dwPos, file_size dwCount)
   {

      return m_spfile->UnlockRange(dwPos, dwCount);

   }

   void file_composite::Abort()
   {

      return m_spfile->Abort();

   }
   
   void file_composite::Flush()
   {

      return m_spfile->Flush();

   }

   void file_composite::close()
   {

      return m_spfile->close();

   }

   ::primitive::memory_size file_composite::read(void *lpBuf, ::primitive::memory_size nCount)
   {

      return m_spfile->read(lpBuf, nCount);

   }

   void file_composite::write(const void * lpBuf, ::primitive::memory_size nCount)
   {

      return m_spfile->write(lpBuf, nCount);

   }

   string file_composite::get_location() const
   {

      return m_spfile->get_location();

   }

   bool file_composite::read(char * pch)
   {

      return m_spfile->read(pch);

   }
   
   bool file_composite::read(unsigned char * puch)
   {
   
      return m_spfile->read(puch);

   }

   bool file_composite::read(char & ch)
   {

      return m_spfile->read(ch);

   }

   bool file_composite::read(unsigned char & uch)
   {

      return m_spfile->read(uch);

   }

   bool file_composite::peek(char * pch)
   {

      return m_spfile->peek(pch);

   }

   bool file_composite::peek(unsigned char * puch)
   {

      return m_spfile->peek(puch);

   }

   bool file_composite::peek(char & ch)
   {

      return m_spfile->peek(ch);

   }

   bool file_composite::peek(unsigned char & uch)
   {

      return m_spfile->peek(uch);

   }

   bool file_composite::IsOpened()
   {

      return m_spfile->IsOpened();

   }
   
   file_composite::~file_composite()
   {
   }

   void file_composite::assert_valid() const
   {

      return m_spfile->assert_valid();

   }
   
   void file_composite::dump(dump_context & dumpcontext) const
   {

      return m_spfile->dump(dumpcontext);

   }


   uint64_t file_composite::GetBufferPtr(UINT nCommand, uint64_t nCount, void ** ppBufStart, void ** ppBufMax)
   {

      return m_spfile->GetBufferPtr(nCommand, nCount, ppBufStart, ppBufMax);

   }


   void file_composite::write(byte_output_stream & ostream)
   {

      m_spfile->write(ostream);

   }


   void file_composite::read(byte_input_stream & istream)
   {

      m_spfile->read(istream);

   }




} // namespace ex1

