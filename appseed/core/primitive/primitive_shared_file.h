#pragma once


#if !defined(METROWIN)


namespace primitive
{

   class CLASS_DECL_CORE shared_file :
      public ::file::memory_buffer
   {
   public:

#ifdef WINDOWS
      shared_file(sp(::aura::application) papp, UINT nGrowBytes = 4096, UINT nAllocFlags = GMEM_MOVEABLE);
#else
    shared_file(sp(::aura::application) papp, UINT nGrowBytes = 4096, UINT nAllocFlags = 0);
#endif

      virtual HGLOBAL detach_storage();
      virtual void SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow = TRUE);

   public:
      virtual ~shared_file();

   };

} // namespace primitive


#endif
