#pragma once

#if defined(_M_IA64) || defined(_M_AMD64)
#define bs_offset long long
#else
#define bs_offset long
#endif


#ifdef _WIN32

#ifdef __cplusplus

#ifdef _BSDIFF_LIBRARY
#define CLASS_DECL_BSDIFF  extern "C" CLASS_DECL_EXPORT
#else
#define CLASS_DECL_BSDIFF  extern "C" CLASS_DECL_IMPORT
#endif

#else

#ifdef _BSDIFF_LIBRARY
#define CLASS_DECL_BSDIFF  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_BSDIFF  CLASS_DECL_IMPORT
#endif


#endif

#else
#define CLASS_DECL_BSDIFF



#endif



CLASS_DECL_BSDIFF int libbsdiff_diff(bs_offset * bsret,unsigned char *old,bs_offset oldsize,unsigned char *pnew,bs_offset newsize,unsigned char *patch,bs_offset patch_size);
CLASS_DECL_BSDIFF bs_offset libbsdiff_size_of_patched(unsigned char *patch);
CLASS_DECL_BSDIFF int libbsdiff_patch(unsigned char *old,bs_offset oldsize,unsigned char *patch,bs_offset patch_size,unsigned char *pnew);


CLASS_DECL_BSDIFF int bsdiff(const char * oldfile,const char * newfile,const char * patchfile);
CLASS_DECL_BSDIFF int bspatch(const char * oldfile,const char * newfile,const char * patchfile);


