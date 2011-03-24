#pragma once


namespace primitive
{

   class CLASS_DECL_ca shared_file : 
   public ::ex1::file,
   public primitive::memory_container < shared_memory >
   {
   public:
      shared_file(::ca::application * papp, UINT nGrowBytes = 4096, UINT nAllocFlags = GMEM_MOVEABLE);

      virtual HGLOBAL Detach();
      virtual void SetHandle(HGLOBAL hGlobalMemory, BOOL bAllowGrow = TRUE);

   public:
      virtual ~shared_file();

   };

} // namespace primitive