#include "StdAfx.h"

namespace primitive
{

   shared_file::shared_file(::ca::application * papp, UINT nAllocFlags, UINT nGrowBytes) :
      ca(papp),
      primitive::memory_container < primitive::shared_memory > (papp)
   {
      UNREFERENCED_PARAMETER(nGrowBytes);
      UNREFERENCED_PARAMETER(nAllocFlags);
   }

   shared_file::~shared_file()
   {
   }

   void shared_file::SetHandle(HGLOBAL hGlobalMemory, BOOL bAllowGrow)
   {
      get_memory()->SetHandle(hGlobalMemory, bAllowGrow);
   }


   HGLOBAL shared_file::Detach()
   {
      return get_memory()->Detach();
   }

} // namespace primitive