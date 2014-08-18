#include "framework.h"


namespace file
{


   composite::composite()
   {

   }


   composite::composite(buffer_sp pfile)
   {

      m_spfile = pfile;

   }


   file_position composite::get_position() const
   {

      return m_spfile->get_position();

   }

   bool composite::GetStatus(file_status& rStatus) const
   {

      return m_spfile->GetStatus(rStatus);

   }

   string composite::GetFileName() const
   {

      return m_spfile->GetFileName();

   }

   string composite::GetFileTitle() const
   {

      return m_spfile->GetFileTitle();

   }
   
   string composite::GetFilePath() const
   {

      return m_spfile->GetFilePath();

   }

   void composite::SetFilePath(const char * lpszNewName)
   {

      return m_spfile->SetFilePath(lpszNewName);

   }

   bool composite::open(const char * lpszFileName, UINT nOpenFlags)
   {

      return m_spfile->open(lpszFileName, nOpenFlags);

   }

   bool composite::GetStatus(const char * lpszFileName, file_status& rStatus)
   {

      return m_spfile->GetStatus(lpszFileName, rStatus);

   }

   void composite::SetStatus(const char * lpszFileName, const file_status& status)
   {

      return m_spfile->SetStatus(lpszFileName, status);

   }

   ::file::buffer_sp  composite::Duplicate() const
   {

      return m_spfile->Duplicate();

   }

   file_position composite::seek(file_offset lOff, ::file::e_seek  nFrom)
   {

      return m_spfile->seek(lOff, nFrom);

   }

   void composite::set_length(file_size dwNewLen)
   {

      return m_spfile->set_length(dwNewLen);

   }
   
   file_size composite::get_length() const
   {

      return m_spfile->get_length();

   }

   void composite::LockRange(file_position dwPos, file_size dwCount)
   {

      return m_spfile->LockRange(dwPos, dwCount);

   }

   void composite::UnlockRange(file_position dwPos, file_size dwCount)
   {

      return m_spfile->UnlockRange(dwPos, dwCount);

   }

   void composite::Abort()
   {

      return m_spfile->Abort();

   }
   
   void composite::flush()
   {

      return m_spfile->flush();

   }

   void composite::close()
   {

      return m_spfile->close();

   }

   ::primitive::memory_size composite::read(void *lpBuf, ::primitive::memory_size nCount)
   {

      return m_spfile->read(lpBuf, nCount);

   }

   void composite::write(const void * lpBuf, ::primitive::memory_size nCount)
   {

      return m_spfile->write(lpBuf, nCount);

   }

   string composite::get_location() const
   {

      return m_spfile->get_location();

   }


   bool composite::IsOpened()
   {

      return m_spfile->IsOpened();

   }
   
   composite::~composite()
   {
   }

   void composite::assert_valid() const
   {

      return m_spfile->assert_valid();

   }
   
   void composite::dump(dump_context & dumpcontext) const
   {

      return m_spfile->dump(dumpcontext);

   }


   uint64_t composite::GetBufferPtr(UINT nCommand, uint64_t nCount, void ** ppBufStart, void ** ppBufMax)
   {

      return m_spfile->GetBufferPtr(nCommand, nCount, ppBufStart, ppBufMax);

   }


   void composite::write(output_stream & ostream)
   {

      m_spfile->write(ostream);

   }


   void composite::read(input_stream & istream)
   {

      m_spfile->read(istream);

   }




} // namespace file

