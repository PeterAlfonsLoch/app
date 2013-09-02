#include "framework.h"


data::writing::writing(data * pdata) :
   interlocked_long_pulse(pdata != NULL ? &pdata->m_lockedlongWriting : NULL, 1)
{
   if(pdata != NULL)
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
   interlocked_long_pulse(pdata != NULL ? &pdata->m_lockedlongSaving : NULL, 1)
{
   if(pdata != NULL)
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

data::data(sp(::application) papp) :
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

bool data::is_in_use() const
{
   return m_lockedlongWriting > 0 || m_lockedlongSaving > 0 || (m_spdataParentLock.is_set() && m_spdataParentLock->is_in_use());
}

void data::on_update_data(int32_t iHint)
{
   for(int32_t i = 0; i < m_listenerptra.get_count(); i++)
   {
      m_listenerptra[i].on_update_data(this, iHint);
   }
}

void data::edit(base_edit * pbaseedit)
{

   UNREFERENCED_PARAMETER(pbaseedit);

}




