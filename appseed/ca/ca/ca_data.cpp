#include "framework.h"


namespace ca
{


   data::writing::writing(data * pdata) :
      interlocked_long_pulse(pdata != ::null() ? &pdata->m_lockedlongWriting : ::null(), 1)
   {
      if(pdata != ::null())
      {
         if(pdata->m_lockedlongWriting == 1 && (pdata->m_spdataParentLock.is_null() || !pdata->m_spdataParentLock->is_in_use()))
         {
            Sys(pdata->m_papp).wait_twf();
         }
      }
   }

   data::writing::~writing()
   {
   }

   data::saving::saving(data * pdata) :
      interlocked_long_pulse(pdata != ::null() ? &pdata->m_lockedlongSaving : ::null(), 1)
   {
      if(pdata != ::null())
      {
         if(pdata->m_lockedlongSaving == 1 && (pdata->m_spdataParentLock.is_null() || !pdata->m_spdataParentLock->is_in_use()))
         {
            Sys(pdata->m_papp).wait_twf();
         }
      }
   }

   data::saving::~saving()
   {
   }

   data::data(::ca::application * papp) :
      ca(papp),
      m_pmutex(::null())
   {
   }


   data::~data()
   {
      comparable_array < data_listener * > listenerptra = m_listenerptra;
      for(int32_t i = 0; i < listenerptra.get_count(); i++)
      {
         listenerptra[i]->listen(this, false);
      }
   }

   bool data::is_in_use() const
   {
      return m_lockedlongWriting > 0 || m_lockedlongSaving > 0 || (m_spdataParentLock.is_set() && m_spdataParentLock->is_in_use());
   }

   void data::on_update_data(int32_t iHint)
   {
      for(int32_t i = 0; i < m_listenerptra.get_count(); i++)
      {
         m_listenerptra[i]->on_update_data(this, iHint);
      }
   }

   bool data::initialize_data()
   {
      return true;
   }

   bool data::finalize_data()
   {
      return true;
   }

   void data::edit(::ca::base_edit * pbaseedit)
   {

      UNREFERENCED_PARAMETER(pbaseedit);

   }


} // namespace ca


