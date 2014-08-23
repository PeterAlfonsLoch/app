#include "framework.h"


namespace file
{


   transfer_buffer::transfer_buffer(sp(::aura::application) papp, mutex * pmutex) :
      element(papp)
   {

      if (pmutex == NULL)
         m_spmutex = new mutex(papp);
      else
         m_spmutex = pmutex;

      m_pmemory = new primitive::memory;
      m_pmemory->set_app(papp);
      m_pmemory->m_spmutex = m_spmutex;

      m_pmemoryfileIn = new ::file::memory_buffer(papp, m_pmemory.m_p);

      m_pmemoryfileOut = new ::file::memory_buffer(papp, m_pmemory.m_p);

      // (uint64_t) -1 - initially unknown size
      m_ptimeoutfile = new ::file::timeout_buffer(papp, m_pmemoryfileOut, (uint64_t)-1);
      m_ptimeoutfile->m_spmutex = m_spmutex;

      m_spfile = m_ptimeoutfile;

      m_ptimeoutfile->m_dwSleep = 284;
      m_ptimeoutfile->m_dwTimeOut = 184 * 1000;

   }

   // it is not currently designed to call open.
   //
   transfer_buffer::transfer_buffer(sp(::aura::application) papp, ::file::memory_buffer * pmemoryfileIn) :
      element(papp)
   {

      if (pmemoryfileIn->get_memory()->m_spmutex.is_null())
         pmemoryfileIn->get_memory()->m_spmutex = new mutex(papp);

      m_spmutex = pmemoryfileIn->get_memory()->m_spmutex;

      m_pmemory = pmemoryfileIn->get_memory();
      m_pmemoryfileIn = pmemoryfileIn;

      m_pmemoryfileOut = new ::file::memory_buffer(papp, m_pmemory.m_p);

      m_ptimeoutfile = new ::file::timeout_buffer(papp, m_pmemoryfileOut);
      m_ptimeoutfile->m_spmutex = m_spmutex;

      m_spfile = m_ptimeoutfile;

      m_ptimeoutfile->m_dwSleep = 284;
      m_ptimeoutfile->m_dwTimeOut = 184 * 1000;

   }

   transfer_buffer::~transfer_buffer()
   {

   }

   /*
   file_position transfer_buffer::seek(file_offset lOff, ::file::e_seek nFrom)
   {
   return m_ptimeoutfile->seek(lOff, nFrom);
   }

   file_size transfer_buffer::get_length() const
   {
   return m_ptimeoutfile->get_length();
   }*/


} // namespace core

