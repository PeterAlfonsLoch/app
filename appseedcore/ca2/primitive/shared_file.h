#pragma once


namespace primitive
{

   class CLASS_DECL_ca shared_file :
      public primitive::memory_file
   {
   public:

#ifdef WINDOWS
      shared_file(::ca::application * papp, UINT nGrowBytes = 4096, UINT nAllocFlags = GMEM_MOVEABLE);
#else
    shared_file(::ca::application * papp, UINT nGrowBytes = 4096, UINT nAllocFlags = 0);
#endif

      virtual HGLOBAL detach_storage();
      virtual void SetHandle(HGLOBAL hGlobalMemory, BOOL bAllowGrow = TRUE);

   public:
      virtual ~shared_file();

   };

} // namespace primitive
