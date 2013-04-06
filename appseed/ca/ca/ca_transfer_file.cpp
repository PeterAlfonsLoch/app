#include "framework.h"


namespace ca
{


   transfer_file::transfer_file(sp(::ca::application) papp, mutex * pmutex) :
      ca(papp)
   {

      if(pmutex == ::null())
         m_spmutex = new mutex(papp);
      else
         m_spmutex = pmutex;

      m_pmemory = new primitive::memory;
      m_pmemory->set_app(papp);
      m_pmemory->m_spmutex = m_spmutex;

      m_pmemoryfileIn = new ::primitive::memory_file(papp, m_pmemory);

      m_pmemoryfileOut = new ::primitive::memory_file(papp, m_pmemory);

      // (uint64_t) -1 - initially unknown size
      m_ptimeoutfile = new ::ca::timeout_file(papp, m_pmemoryfileOut, (uint64_t) -1);
      m_ptimeoutfile->m_spmutex = m_spmutex;

      m_spreader = m_ptimeoutfile;
      m_spwriter = m_ptimeoutfile;
      m_ptimeoutfile->m_dwSleep = 284;
      m_ptimeoutfile->m_dwTimeOut = 184 * 1000;

   }

   // it is not currently designed to call open.
   //
   transfer_file::transfer_file(sp(::ca::application) papp, ::primitive::memory_file * pmemoryfileIn) :
      ca(papp)
   {

      if(pmemoryfileIn->get_memory()->m_spmutex.is_null())
         pmemoryfileIn->get_memory()->m_spmutex = new mutex(papp);

      m_spmutex = pmemoryfileIn->get_memory()->m_spmutex;

      m_pmemory = pmemoryfileIn->get_memory();
      m_pmemoryfileIn = pmemoryfileIn;

      m_pmemoryfileOut = new ::primitive::memory_file(papp, m_pmemory);

      m_ptimeoutfile = new ::ca::timeout_file(papp, m_pmemoryfileOut);
      m_ptimeoutfile->m_spmutex = m_spmutex;

      m_spreader = m_ptimeoutfile;
      m_spwriter = m_ptimeoutfile;

      m_ptimeoutfile->m_dwSleep = 284;
      m_ptimeoutfile->m_dwTimeOut = 184 * 1000;

   }

   transfer_file::~transfer_file()
   {

   }

   file_position transfer_file::seek(file_offset lOff, ::ca::e_seek nFrom)
   {
      return m_ptimeoutfile->seek(lOff, nFrom);
   }

   file_size transfer_file::get_length() const
   {
      return m_ptimeoutfile->get_length();
   }


} // namespace ca

