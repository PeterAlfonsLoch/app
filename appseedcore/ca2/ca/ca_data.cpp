#include "StdAfx.h"


namespace ca
{


   data::writing::writing(data * pdata) :
      interlocked_long_pulse(pdata != NULL ? &pdata->m_lockedlongWriting : NULL, 1)
   {
      if(pdata != NULL)
      {
         if(pdata->m_lockedlongWriting == 1)
         {
            pdata->m_papp->m_psystem->wait_twf();
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
         if(pdata->m_lockedlongSaving == 1)
         {
            pdata->m_papp->m_psystem->wait_twf();
         }
      }
   }

   data::saving::~saving()
   {
   }

   data::data(::ca::application * papp) :
      ca(papp)
   {
   }


   data::~data()
   {
      comparable_array < data_listener * > listenerptra = m_listenerptra;
      for(int i = 0; i < listenerptra.get_count(); i++)
      {
         listenerptra[i]->listen(this, false);
      }
   }

   bool data::is_in_use() const
   {
      return m_lockedlongWriting > 0 || m_lockedlongSaving > 0;
   }

   void data::on_update_data(int iHint)
   {
      for(int i = 0; i < m_listenerptra.get_count(); i++)
      {
         m_listenerptra[i]->on_update_data(this, iHint);
      }
   }

} // namespace ca
