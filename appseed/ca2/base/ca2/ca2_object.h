#pragma once




class var;
class dump_context;


namespace visual
{


   class icon;


} // namespace visual


namespace ca2
{


   class command_thread;
   class property;
   class property_set;


} // namespace ca2


// a bit of the eternal jealousy/envy : javas capability of locking/synching on any object


namespace ca2
{


   class CLASS_DECL_ca2 object :
      virtual public waitable
   {
   public:


      ::ca2::property_set *     m_psetObject;


      object();
      object(const object & objectSrc);              // no implementation
      virtual ~object();  // virtual destructors are necessary


      void common_construct();

      bool IsSerializable() const;


      virtual ::ca2::property & oprop(const char * psz);
      virtual ::ca2::property & oprop(const char * psz) const;
      virtual ::ca2::property_set & propset();


      virtual ::visual::icon * set_icon(::visual::icon * picon, bool bBigIcon);
      virtual ::visual::icon * get_icon(bool bBigIcon) const;


#undef new
#undef delete
      void * operator new(size_t nSize);
      void * operator new(size_t, void * p);
      void operator delete(void * p);
#if _MSC_VER >= 1200 || defined(LINUX) || defined(MACOS) || defined(ANDROID)
      void operator delete(void * p, void * pPlace);
#endif

#if defined(DEBUG) && !defined(___NO_DEBUG_CRT) || defined(LINUX) || defined(MACOS) || defined(ANDROID)
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


      virtual sp(::ca2::command_thread) command_thread();

   };




} // namespace ca2



