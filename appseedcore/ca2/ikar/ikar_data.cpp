#include "StdAfx.h"

namespace ikar
{

   data::data(::ca::application * papp) :
      ca(papp),
      ::ca::data(papp)
   {
      m_pstaticdata = NULL;
      m_pdynamicdata = NULL;

      m_pstaticdata = new ikar::static_data();
      if(m_pstaticdata == NULL)
         throw new memory_exception;
      m_pdynamicdata = new ikar::dynamic_data();
      if(m_pdynamicdata == NULL)
         throw new memory_exception;

   }

   data::~data()
   {
      if(m_pstaticdata != NULL)
      {
         delete m_pstaticdata;
         m_pstaticdata = NULL;
      }
      if(m_pdynamicdata != NULL)
      {
         delete m_pdynamicdata;
         m_pdynamicdata = NULL;
      }
   }



   void data::SetInterface(ikar::karaoke *pinterface)
   {
      m_pinterface = pinterface;
   }

   void data::Initialize(ikar::karaoke * pinterface)
   {
      SetInterface(pinterface);
      GetStaticData().m_dwDefaultCodePage = pinterface->GetDefaultCodePage();
   }


   void data::Prepare()
   {
      GetDynamicData().reset();
      GetInterface()->Prepare(*this);
   }

   void data::delete_contents()
   {
      GetDynamicData().reset();
      GetStaticData().delete_contents();
   }

   bool ikar::data::IsNull()
   {
      return this == NULL;
   }

   ikar::static_data & ikar::data::GetStaticData()
   {
      return * m_pstaticdata;
   }

   ikar::dynamic_data & ikar::data::GetDynamicData()
   {
      return * m_pdynamicdata;
   }

   ikar::karaoke * ikar::data::GetInterface()
   {
      return m_pinterface;
   }

} // namespace ikar