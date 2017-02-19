#pragma once


class CLASS_DECL_AXIS ftpfs_file :
   virtual public ::file::file
{
public:


   ftpfs *                       m_pftp;
   ::file::file_sp             m_file;
   var                           m_varFile;
   ::file::path                  m_filepath;
   ::ftp::client_socket *               m_pclient;


   // Download false
   // Create temp file and upload file on destruction
   ftpfs_file(::ftpfs * pftp, ::ftp::client_socket * pclient);
   virtual ~ftpfs_file();


   virtual cres open(const ::file::path & lpszFileName, UINT nOpenFlags) override;

   virtual memory_size_t read(void *lpBuf, memory_size_t nCount) override;
   virtual void write(const void * lpBuf, memory_size_t nCount) override;

   file_position_t seek(file_offset_t lOff, ::file::e_seek  nFrom) override;

   virtual file_size_t get_length() const override;

   virtual void close() override;

};


