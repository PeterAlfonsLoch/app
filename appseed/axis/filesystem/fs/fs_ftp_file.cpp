//#include "framework.h"
//#include "axis/net/net_sockets.h"



#include "openssl/md5.h"


ftpfs_file::ftpfs_file(::ftpfs * pftp, ::ftp::client_socket * pclient) :
   ::object(pclient->get_app()),
   m_file(allocer())
{

   m_pftp = pftp;

   m_pclient = pclient;

   m_varFile = Application.file().time(System.dir().time());

}


void ftpfs_file::close()
{

   try
   {

      m_file->close();

   }
   catch(...)
   {


   }

   m_file.release();

   ::ftp::client_socket * pclient = m_pclient;

   int iTry = 0;

retry:

   if (iTry > 0)
   {

      m_pftp->defer_initialize(&pclient, m_filepath);

   }


   if (pclient->m_estate != ::ftp::client_socket::state_logged)
   {

      if (iTry > 3)
      {

         return;

      }

      iTry++;

      goto retry;

   }

   string strRemoteFile = System.url().get_object(m_filepath);

   if (!pclient->UploadFile(m_varFile, strRemoteFile))
   {

      if (iTry > 3)
      {

         return;

      }

      pclient->m_estate = ::ftp::client_socket::state_initial;

      iTry++;

      goto retry;

   }


} 

ftpfs_file::~ftpfs_file()
{


}


cres ftpfs_file::open(const ::file::path & filepath, UINT nOpenFlags)
{

   m_filepath = filepath;

   return m_file->open(m_varFile, ::file::mode_create | ::file::type_binary | ::file::mode_read_write | ::file::defer_create_directory);

}


memory_size_t ftpfs_file::read(void *lpBuf, memory_size_t nCount)
{

   return m_file->read(lpBuf, nCount);

}


void ftpfs_file::write(const void * lpBuf, memory_size_t nCount)
{

   m_file->write(lpBuf, nCount);

}


file_size_t ftpfs_file::get_length() const
{

   return m_file->get_length();

}


file_position_t ftpfs_file::seek(file_offset_t lOff, ::file::e_seek nFrom)
{

   return m_file->seek(lOff, nFrom);

}


