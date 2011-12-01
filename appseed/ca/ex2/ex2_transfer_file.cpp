#include "StdAfx.h"


namespace ex2
{


   transfer_file::transfer_file(::ca::application * papp, mutex * pmutex) :
      ca(papp)
   {
      if(pmutex == NULL)
         m_spmutex(new mutex());
      else
         m_spmutex = pmutex;

      m_pmemory(new primitive::memory);
      m_pmemory->set_app(papp);
         
      m_pmemoryfileIn(new gen::memory_file(papp, m_pmemory));
      m_pmemoryfileIn->m_bSynch = true;
      m_pmemoryfileIn->m_spmutex = m_spmutex;

      m_pmemoryfileOut(new gen::memory_file(papp, m_pmemory));
      m_pmemoryfileOut->m_bSynch = true;
      m_pmemoryfileOut->m_spmutex = m_spmutex;

      // (uint64_t) -1 - initially unknown size
      m_ptimeoutfile = new ex1::timeout_file(papp, m_pmemoryfileOut, (uint64_t) -1); 
      m_ptimeoutfile->m_spmutex = m_spmutex;

      m_spreader = m_ptimeoutfile;
      m_spwriter = m_ptimeoutfile;
      m_ptimeoutfile->m_dwSleep = 284;
      m_ptimeoutfile->m_dwTimeOut = 184 * 1000;
   }

   // it is not currently designed to call open.
   //
   transfer_file::transfer_file(::ca::application * papp, ::gen::memory_file * pmemoryfileIn, mutex * pmutex) :
      ca(papp)
   {
      if(pmutex == NULL)
         m_spmutex(new mutex());
      else
         m_spmutex = pmutex;

      m_pmemory = pmemoryfileIn->get_memory();
      m_pmemoryfileIn = pmemoryfileIn;
      m_pmemoryfileIn->m_bSynch = true;
      m_pmemoryfileIn->m_spmutex = m_spmutex;

      m_pmemoryfileOut(new gen::memory_file(papp, m_pmemory));
      m_pmemoryfileOut->m_bSynch = true;
      m_pmemoryfileOut->m_spmutex = m_spmutex;

      m_ptimeoutfile = new ex1::timeout_file(papp, m_pmemoryfileOut);
      m_ptimeoutfile->m_spmutex = m_spmutex;
      m_spreader = m_ptimeoutfile;
      m_spwriter = m_ptimeoutfile;

      m_ptimeoutfile->m_dwSleep = 284;
      m_ptimeoutfile->m_dwTimeOut = 184 * 1000;
   }

   transfer_file::~transfer_file()
   {

   }
      
   file_position transfer_file::seek(file_offset lOff, ::ex1::e_seek nFrom)
   {
      return m_ptimeoutfile->seek(lOff, nFrom);
   }

   file_size transfer_file::get_length() const
   {
      return m_ptimeoutfile->get_length();
   }


} // namespace ex2

