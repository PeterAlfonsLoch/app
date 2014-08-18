#pragma once


class CLASS_DECL_AXIS ifs_file :
   virtual public ::sockets::http_batch_buffer
{
public:


   smart_pointer < ::sockets::http_buffer >     m_httpfile;
   ::file::memory_buffer                        m_memfile;
   var                                          m_varFile;


   ifs_file(sp(::axis::application) papp, var varFile);
   virtual ~ifs_file();

   using ::sockets::http_batch_buffer::read;
   virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
   using ::sockets::http_batch_buffer::write;
   virtual void write(const void * lpBuf, ::primitive::memory_size nCount);

   file_position seek(file_offset lOff, ::file::e_seek  nFrom);

   virtual file_size get_length() const;

   virtual void get_file_data();
   virtual void set_file_data();


};


