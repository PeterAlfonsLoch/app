#pragma once


class var;


namespace visual
{


   class icon;


} // namespace visual


namespace gen
{


   class command_thread;
   class property;
   class property_set;


} // namespace gen


// a bit of the eternal jealousy/envy : javas capability of locking/synching on any object


namespace radix
{


   class CLASS_DECL_ca object :
      virtual public sync_object_base
   {
   public:


      object();
      object(const object & objectSrc);              // no implementation
      virtual ~object();  // virtual destructors are necessary


      void common_construct();

      BOOL IsSerializable() const;


      virtual gen::property & oprop(const char * psz);
      virtual gen::property & oprop(const char * psz) const;
      virtual gen::property_set & propset();


      virtual ::visual::icon * set_icon(::visual::icon * picon, bool bBigIcon);
      virtual ::visual::icon * get_icon(bool bBigIcon) const;


#undef new
#undef delete
      void * PASCAL operator new(size_t nSize);
      void * PASCAL operator new(size_t, void * p);
      void PASCAL operator delete(void * p);
#if _MSC_VER >= 1200 || defined(LINUX)
      void PASCAL operator delete(void * p, void * pPlace);
#endif

#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)  || defined(LINUX)
      // for file name/line number tracking using DEBUG_NEW
      void * PASCAL operator new(size_t nSize, const char * lpszFileName, int nLine);
#if _MSC_VER >= 1200  || defined(LINUX)
      void PASCAL operator delete(void *p, const char * lpszFileName, int nLine);
#endif
#endif
#define new DEBUG_NEW

      // Diagnostic Support
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      object & operator = (const object & objectSrc);       // no implementation


      virtual ::gen::command_thread & command_thread();

   };


} // namespace radix



