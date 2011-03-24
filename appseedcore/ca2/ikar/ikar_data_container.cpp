#include "StdAfx.h"

namespace ikar
{

   data_container::data_container()
   {

      m_pdata = NULL;

   }


   data_container::~data_container()
   {

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