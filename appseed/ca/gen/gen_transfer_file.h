#pragma once


namespace gen
{


   class CLASS_DECL_ca transfer_file : 
      virtual public ::gen::file
   {
   public:

         
      ::gen::timeout_file *         m_ptimeoutfile;
      sp(::primitive::memory_base)  m_pmemory;
      sp(::gen::memory_file)        m_pmemoryfileIn;
      sp(::gen::memory_file)        m_pmemoryfileOut;
      sp(mutex)                     m_spmutex;                      

         
      transfer_file(::ca::application * papp, mutex * pmutex = NULL);
      transfer_file(::ca::application * papp, ::gen::memory_file * pmemoryfileIn);
      virtual ~transfer_file();


      virtual file_position seek(file_offset lOff, ::gen::e_seek  nFrom);
      virtual file_size get_length() const;


   };


} // namespace gen



