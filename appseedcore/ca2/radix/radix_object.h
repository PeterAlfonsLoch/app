#pragma once

#include "gen/gen_object.h"
#include "primitive/id.h"

class var;

namespace visual
{

   class icon;

} // namespace visual


namespace radix
{

   class CLASS_DECL_ca object :
      virtual public ::gen::object
   {
   public:

      object();
      object(const object & objectSrc);              // no implementation
      virtual ~object();  // virtual destructors are necessary

      void common_construct();

      BOOL IsSerializable() const;

      virtual var & oprop(id id);
      virtual var & oprop(id id) const;

      virtual ::visual::icon * set_icon(::visual::icon * picon, bool bBigIcon);
      virtual ::visual::icon * get_icon(bool bBigIcon) const;

      // Diagnostic allocations
   #undef new
      void * PASCAL operator new(size_t nSize);
      void * PASCAL operator new(size_t, void * p);
      void PASCAL operator delete(void * p);
   #if _MSC_VER >= 1200
      void PASCAL operator delete(void * p, void * pPlace);
   #endif

   #if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
      // for file name/line number tracking using DEBUG_NEW
      void * PASCAL operator new(size_t nSize, const char * lpszFileName, int nLine);
   #if _MSC_VER >= 1200
      void PASCAL operator delete(void *p, const char * lpszFileName, int nLine);
   #endif
   #endif
   #define new DEBUG_NEW

      // Diagnostic Support
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      object & operator = (const object & objectSrc);       // no implementation

   };

} // namespace radix