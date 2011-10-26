#include "StdAfx.h"

namespace primitive
{

   shared_file::shared_file(::ca::application * papp, UINT nAllocFlags, UINT nGrowBytes) :
      ca(papp),
      memory_container(papp),
      memory_file(papp)
   {
      UNREFERENCED_PARAMETER(nGrowBytes);
      UNREFERENCED_PARAMETER(nAllocFlags);
   }

   shared_file::~shared_file()
   {
   }

   void shared_file::SetHandle(HGLOBAL hGlobalMemory, BOOL bAllowGrow)
   {
      (dynamic_cast < shared_memory * >(get_memory()))->SetHandle(hGlobalMemory, bAllowGrow);
   }


   HGLOBAL shared_file::detach_storage()
   {
      return (dynamic_cast < shared_memory * >(get_memory()))->detach();
   }

} // namespace primitive