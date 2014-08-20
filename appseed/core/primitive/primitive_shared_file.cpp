#include "framework.h"


#if !defined(METROWIN)


namespace primitive
{


   shared_file::shared_file(sp(::axis::application) papp, UINT nAllocFlags, UINT nGrowBytes) :
      element(papp),
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

      return (dynamic_cast < shared_memory * >(get_memory()))->detach();

   }


} // namespace primitive


#endif

