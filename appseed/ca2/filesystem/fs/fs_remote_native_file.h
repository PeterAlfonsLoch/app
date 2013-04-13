#pragma once


namespace fs
{


   class CLASS_DECL_ca2 remote_native_file : 
      virtual public ::sockets::http::batch_file
   {
   public:


      ::ca::smart_pointer < sockets::http::file >  m_httpfile;
      ::primitive::memory_file                             m_memfile;
      var                                          m_varFile;


      remote_native_file(sp(::ca::application) papp, var varFile);
      virtual ~remote_native_file();

      virtual ::primitive::memory_size read(void *lpBuf, ::primitive::memory_size nCount);
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);

      file_position seek(file_offset lOff, ::ca::e_seek  nFrom);

      virtual file_size get_length() const;

      virtual void get_file_data();
      virtual void set_file_data();


   };


} // namespace fs