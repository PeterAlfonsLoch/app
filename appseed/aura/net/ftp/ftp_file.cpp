#include "framework.h"


namespace ftp
{


   file::file(::aura::application * papp) :
      ::object(papp)
   {
   }

   file::~file()
   {
      close();
   }

   bool file::Open(const string& strFileName, UINT uiMode)
   {
      
      m_strFileName = strFileName;

      m_file = Application.file().get_file(strFileName, uiMode);

      return m_file.is_set();

   }

   bool file::close()
   {

      m_file->close();
      m_file.release();
      
      return true;

   }

   bool file::Seek(long lOffset, ::file::e_seek enOrigin)
   {
      return m_file.is_set() && m_file->seek(lOffset, enOrigin) == 0;
   }

   
   long file::Tell()
   {

      if (m_file.is_null())
      {

         return -1L;

      }

      return (long) m_file->get_position();

   }


   
   size_t file::write(const void* pBuffer, size_t itemSize, size_t itemCount)
   {
      
      if (m_file.is_null())
      {

         return 0;

      }
      
      m_file->write(pBuffer, itemSize * itemCount);
      
      return itemCount;

   }


   size_t file::Read(void* pBuffer, size_t itemSize, size_t itemCount)
   {

      if (m_file.is_null())
      {

         return 0;

      }

      memory_size_t uiRead = m_file->read(pBuffer, itemSize * itemCount);

      return uiRead / itemSize;

   }


   string file::GetLocalStreamName() const
   {
      return m_strFileName;
   }

   UINT file::GetLocalStreamSize() const
   {
      if (m_file.is_null())
         return 0;


      return (UINT) m_file->get_length();
   }

   void file::SetLocalStreamOffset(DWORD dwOffsetFromBeginOfStream)
   {
      Seek(dwOffsetFromBeginOfStream, ::file::seek_begin);
   }

   void file::OnBytesReceived(const memory& vBuffer, long lReceivedBytes)
   {
      write(vBuffer.get_data(), sizeof(memory::value_type), lReceivedBytes);
   }

   void file::OnPreBytesSend(byte* pszBuffer, size_t bufferSize, size_t& bytesToSend)
   {
      bytesToSend = Read(pszBuffer, sizeof(char), bufferSize);
   }



} // namespace ftp




