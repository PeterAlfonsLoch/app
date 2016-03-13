#include "framework.h"


#if !defined(METROWIN)


namespace primitive
{


   shared_file::shared_file(::aura::application * papp, UINT nAllocFlags, UINT nGrowBytes) :
      ::object(papp),
      memory_container(papp),
      memory_buffer(papp)
   {

      UNREFERENCED_PARAMETER(nGrowBytes);

      UNREFERENCED_PARAMETER(nAllocFlags);

   }


   shared_file::~shared_file()
   {

   }


   void shared_file::SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow)
   {

      (dynamic_cast < shared_memory * >(get_memory()))->SetHandle(hGlobalMemory, bAllowGrow);

   }


   HGLOBAL shared_file::detach_storage()
   {

      HGLOBAL hglobal = NULL;

      (dynamic_cast < shared_memory * >(get_memory()))->detach_shared_memory(hglobal);

      return hglobal;

   }


} // namespace primitive


#endif

