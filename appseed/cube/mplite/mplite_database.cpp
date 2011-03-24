#include "StdAfx.h"

namespace mplite
{

   database::database(::ca::application * papp) :
      ca(papp)
   {
      m_bInitialized = false;
   }

   database::~database()
   {
      Finalize();
   }

   bool database::Initialize()
   {
      ASSERT(!m_bInitialized);
      if(m_bInitialized)
         return false;
      m_bInitialized = true;

      return true;
   }

   void database::Finalize()
   {
      ASSERT(m_bInitialized);
      if(!m_bInitialized)
         return;
      m_bInitialized = false;
   }


} // namespace mplite