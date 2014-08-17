#include "framework.h"


namespace data
{

   simple_lock::simple_lock(simple_data * pdata) :
      interlocked_long_pulse(pdata != NULL ? &pdata->m_lockedlong : NULL, 1)
   {
      
      m_spdata = pdata;
      
      if(pdata != NULL)
      {
         if(pdata->m_lockedlong == 1)
         {
            Sys(pdata->m_pbaseapp).wait_twf();
         }
      }
   }

   simple_lock::~simple_lock()
   {
   
      if(m_plockedlong != NULL)
      {
         m_plockedlong->subtract(m_lLevel);
         m_plockedlong = NULL;
      }
      
   }


   simple_data::simple_data()
   {
   }
   
   simple_data::~simple_data()
   {
   }

   
   bool simple_data::is_locked() const
   {

      return m_lockedlong > 0;

   }


   void simple_data::on_update_data(int32_t iHint)
   {

   }


   lock::lock(::data::data * pdata) :
      interlocked_long_pulse(pdata != NULL ? &pdata->m_lockedlong : NULL, 1)
   {
      if (pdata != NULL)
      {
         if (pdata->m_lockedlong == 1 && (pdata->m_spdataParentLock.is_null() || !pdata->m_spdataParentLock->is_locked()))
         {
            Sys(pdata->m_pbaseapp).wait_twf();
         }
      }
   }

   lock::~lock()
   {
   }


   data::data(sp(::base::application) papp) :
      element(papp),
      m_pmutex(NULL)
   {
   }


   data::~data()
   {
      spa(data_listener) listenerptra = m_listenerptra;
      for(int32_t i = 0; i < listenerptra.get_count(); i++)
      {
         listenerptra[i].listen(this, false);
      }
   }

   bool data::is_locked() const
   {
      return ::data::simple_data::is_locked() || (m_spdataParentLock.is_set() && m_spdataParentLock->is_locked());
   }

   void data::on_update_data(int32_t iHint)
   {
      for(int32_t i = 0; i < m_listenerptra.get_count(); i++)
      {
         m_listenerptra[i].on_update_data(this, iHint);
      }
   }

   void data::edit(axis_edit * pbaseedit)
   {

      UNREFERENCED_PARAMETER(pbaseedit);

   }


} // namespace data





