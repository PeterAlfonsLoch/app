#pragma once


class CLASS_DECL_AXIS ifs_file :
   virtual public ::sockets::http_batch_buffer
{
public:


   smart_pointer < ::sockets::http_buffer >     m_httpfile;
   ::file::memory_buffer                        m_memfile;
   var                                          m_varFile;


   ifs_file(::aura::application * papp, var varFile);
   virtual ~ifs_file();

   using ::sockets::http_batch_buffer::read;
   virtual memory_size_t read(void *lpBuf, memory_size_t nCount);
   using ::sockets::http_batch_buffer::write;
   virtual void write(const void * lpBuf, memory_size_t nCount);

   file_position_t seek(file_offset_t lOff, ::file::e_seek  nFrom);

   virtual file_size_t get_length() const;

   virtual void get_file_data();
   virtual void set_file_data();


};


