#pragma once


namespace file
{


   class CLASS_DECL_ca2 transfer_stream :
      virtual public ::file::stream
   {
   public:


      sp(::file::timeout_buffer)       m_ptimeoutfile;
      sp(::primitive::memory_base)     m_pmemory;
      sp(::file::memory_buffer)        m_pmemoryfileIn;
      sp(::file::memory_buffer)        m_pmemoryfileOut;
      sp(mutex)                        m_spmutex;


      transfer_stream(sp(base_application) papp, mutex * pmutex = NULL);
      transfer_stream(sp(base_application) papp, ::file::memory_buffer * pmemoryfileIn);
      virtual ~transfer_stream();


      virtual file_position seek(file_offset lOff, ::file::e_seek  nFrom);
      virtual file_size get_length() const;


   };


} // namespace file



