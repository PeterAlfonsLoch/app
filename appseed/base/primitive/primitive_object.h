#pragma once


class CLASS_DECL_c object :
   virtual public waitable
{
public:


   property_set *     m_psetObject;


   object();
   object(const object & objectSrc);              // no implementation
   virtual ~object();  // virtual destructors are necessary


   void common_construct();

   bool IsSerializable() const;


   virtual property & oprop(const char * psz);
   virtual property & oprop(const char * psz) const;
   virtual property_set & propset();




#undef new
#undef delete
   void * operator new(size_t nSize);
   void * operator new(size_t, void * p);
   void operator delete(void * p);
#if _MSC_VER >= 1200 || defined(LINUX) || defined(MACOS) || defined(ANDROID) || defined(SOLARIS)
   void operator delete(void * p, void * pPlace);
#endif

#if defined(DEBUG) && !defined(___NO_DEBUG_CRT) || defined(LINUX) || defined(MACOS) || defined(ANDROID) || defined(SOLARIS)
   // for file name/line number tracking using DEBUG_NEW
   void * operator new(size_t nSize, const char * lpszFileName, int32_t nLine);
#if _MSC_VER >= 1200  || defined(LINUX) || defined(MACOS) || defined(ANDROID)
   void operator delete(void *p, const char * lpszFileName, int32_t nLine);
#endif
#endif
#define new DEBUG_NEW

   // Diagnostic Support

   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;

   object & operator = (const object & objectSrc);       // no implementation


   inline sp(::command_thread) command_thread();


};







