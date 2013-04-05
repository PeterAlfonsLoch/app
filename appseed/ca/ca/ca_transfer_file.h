#pragma once


namespace ca
{


   class CLASS_DECL_ca transfer_file :
      virtual public ::ca::file
   {
   public:


      sp(::ca::timeout_file)        m_ptimeoutfile;
      sp(::primitive::memory_base)  m_pmemory;
      sp(::primitive::memory_file)  m_pmemoryfileIn;
      sp(::primitive::memory_file)  m_pmemoryfileOut;
      sp(mutex)                     m_spmutex;


      transfer_file(::ca::applicationsp papp, mutex * pmutex = ::null());
      transfer_file(::ca::applicationsp papp, ::primitive::memory_file * pmemoryfileIn);
      virtual ~transfer_file();


      virtual file_position seek(file_offset lOff, ::ca::e_seek  nFrom);
      virtual file_size get_length() const;


   };


} // namespace ca



