#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 transfer_file :
      virtual public ::file::file
   {
   public:


      sp(::ca2::timeout_file)        m_ptimeoutfile;
      sp(::primitive::memory_base)  m_pmemory;
      sp(::primitive::memory_file)  m_pmemoryfileIn;
      sp(::primitive::memory_file)  m_pmemoryfileOut;
      sp(mutex)                     m_spmutex;


      transfer_file(sp(base_application) papp, mutex * pmutex = NULL);
      transfer_file(sp(base_application) papp, ::primitive::memory_file * pmemoryfileIn);
      virtual ~transfer_file();


      virtual file_position seek(file_offset lOff, ::file::e_seek  nFrom);
      virtual file_size get_length() const;


   };


} // namespace ca2



