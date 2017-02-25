#include "framework.h"


namespace file
{


   transfer_file::transfer_file(::aura::application * papp, mutex * pmutex) :
      object(papp)
   {

      if (pmutex == NULL)
         m_spmutex = canew(mutex(papp));
      else
         m_spmutex = pmutex;

      m_pmemory = canew(memory);
      m_pmemory->set_app(papp);
      m_pmemory->m_spmutex = m_spmutex;

      m_pmemoryfileIn = canew(::memory_file(papp, m_pmemory.m_p));

      m_pmemoryfileOut = canew(::memory_file(papp, m_pmemory.m_p));

      // (uint64_t) -1 - initially unknown size
      m_ptimeoutfile = canew(::file::timeout_file(papp, m_pmemoryfileOut, (uint64_t)-1));
      m_ptimeoutfile->m_spmutex = m_spmutex;

      m_spfile = m_ptimeoutfile;

      m_ptimeoutfile->m_dwSleep = 284;
      m_ptimeoutfile->m_dwTimeOut = 184 * 1000;

   }

   // it is not currently designed to call open.
   //
   transfer_file::transfer_file(::aura::application * papp, ::memory_file * pmemoryfileIn) :
      object(papp)
   {

      if (pmemoryfileIn->get_memory()->m_spmutex.is_null())
         pmemoryfileIn->get_memory()->m_spmutex = canew(mutex(papp));

      m_spmutex = pmemoryfileIn->get_memory()->m_spmutex;

      m_pmemory = pmemoryfileIn->get_memory();
      m_pmemoryfileIn = pmemoryfileIn;

      m_pmemoryfileOut = canew(::memory_file(papp, m_pmemory.m_p));

      m_ptimeoutfile = canew(::file::timeout_file(papp, m_pmemoryfileOut));
      m_ptimeoutfile->m_spmutex = m_spmutex;

      m_spfile = m_ptimeoutfile;

      m_ptimeoutfile->m_dwSleep = 284;
      m_ptimeoutfile->m_dwTimeOut = 184 * 1000;

   }

   transfer_file::~transfer_file()
   {

   }

   /*
   file_position_t transfer_file::seek(file_offset_t lOff, ::file::e_seek nFrom)
   {
   return m_ptimeoutfile->seek(lOff, nFrom);
   }

   file_size_t transfer_file::get_length() const
   {
   return m_ptimeoutfile->get_length();
   }*/


} // namespace core

