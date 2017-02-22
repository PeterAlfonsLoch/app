#pragma once


namespace file
{


   class CLASS_DECL_AURA transfer_file :
      virtual public ::file::composite
   {
   public:


      sp(::file::timeout_file)       m_ptimeoutfile;
      sp(::primitive::memory_base)     m_pmemory;
      sp(::memory_file)        m_pmemoryfileIn;
      sp(::memory_file)        m_pmemoryfileOut;
      sp(mutex)                        m_spmutex;


      transfer_file(::aura::application * papp, mutex * pmutex = NULL);
      transfer_file(::aura::application * papp, ::memory_file * pmemoryfileIn);
      virtual ~transfer_file();


      //      virtual file_position_t seek(file_offset_t lOff, ::file::e_seek  nFrom);
      //    virtual file_size_t get_length() const;


   };


} // namespace file



