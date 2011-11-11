#include "StdAfx.h"

namespace ikar
{

   data_container::data_container()
   {
   }


   data_container::~data_container()
   {
      gen::release(m_pdata.m_p);
   }


   void data_container::SetKaraokeData(ikar::data *pdata)
   {

      m_pdata = pdata;

   }

   ikar::data & data_container::GetKaraokeData()
   {
      return * m_pdata;
   }

} // namespace ikar