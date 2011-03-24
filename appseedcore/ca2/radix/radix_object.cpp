#include "StdAfx.h"


namespace radix
{

   /////////////////////////////////////////////////////////////////////////////
   // Runtime Typing

   // special runtime-class structure for ::object (no base class)
   /*const struct ::ca::type_info object::classbase_object =
   { "::object", sizeof(::object), 0xffff, NULL, NULL, NULL };*/
   /*
   ::ca::type_info object::GetRuntimeClass() const
   {
   return _RUNTIME_CLASS(::object);
   }
   */

   object::object()
   { 
      try
      {
         if(::icube::get_heap_itema() != NULL)
         {
            ::icube::get_heap_itema()->set_heap_alloc(this);
         }
      }
      catch(...)
      {
      }
      common_construct(); 
   }
   
   void object::common_construct()
   {
   }
   
   object::~object()
   { 
   }

   object::object(const object& objectSrc)
   {
      try
      {
         if(::icube::get_heap_itema() != NULL)
         {
            ::icube::get_heap_itema()->set_heap_alloc(this);
         }
      }
      catch(...)
      {
      }
      operator =(objectSrc);
   }


   object & object::operator=(const object& objectSrc)
   {
      if(this != &objectSrc)
      {
         gen::object::operator =(objectSrc);
      }
      return *this;
   }



   void object::assert_valid() const
   {
      ASSERT(this != NULL);
   }

   void object::dump(dump_context & dumpcontext) const
   {
      dumpcontext << "a " << typeid(*this).name() <<
         " at " << (void *)this << "\n";

      UNUSED(spgraphics); // unused in release build
   }


   ::visual::icon * object::set_icon(::visual::icon * picon, bool bBigIcon)
   {
      ::visual::icon * piconOld = get_icon(bBigIcon);
      if(bBigIcon)
      {
         oprop("big_icon").operator =((::ca::object *) picon);
      }
      else
      {
         oprop("small_icon").operator =((::ca::object *) picon);
      }
      return piconOld;
   }


   ::visual::icon * object::get_icon(bool bBigIcon) const
   {
      if(bBigIcon)
      {
         return const_cast < object * > (this)->oprop("big_icon").ca2 < ::visual::icon >();
      }
      else
      {
         return const_cast < object * > (this)->oprop("small_icon").ca2 < ::visual::icon >();
      }
   }


   var & object::oprop(id id)
   {
      return System.oprop(this, id);
   }

   var & object::oprop(id id) const 
   {
      return const_cast < var & > (System.oprop(const_cast < object * > (this), id));
   }




#undef new
   void * PASCAL object::operator new(size_t size, void * p)
   { 
      return p; 
   }
#define new DEBUG_NEW

} //  namespace radix


/////////////////////////////////////////////////////////////////////////////
// Diagnostic Support

//#ifdef _DEBUG
void Afxassert_validObject(const ::radix::object * pOb, const char * lpszFileName, int nLine)
{
   if (pOb == NULL)
   {
//      TRACE(::radix::trace::category_AppMsg, 0, "ASSERT_VALID fails with NULL pointer.\n");
      if (AfxAssertFailedLine(lpszFileName, nLine))
         AfxDebugBreak();
      return;     // quick escape
   }
   if (!fx_is_valid_address(pOb, sizeof(::radix::object)))
   {
      ///TRACE(::radix::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal pointer.\n");
      if (AfxAssertFailedLine(lpszFileName, nLine))
         AfxDebugBreak();
      return;     // quick escape
   }

   // check to make sure the VTable pointer is valid
   //   ASSERT(sizeof(::object) == sizeof(void *));
   //   if (!fx_is_valid_address(*(void **)pOb, sizeof(void *), FALSE))
   if (!fx_is_valid_address(*(void **)pOb, sizeof(void *), FALSE))
   {
//      TRACE(::radix::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal vtable pointer.\n");
      if (AfxAssertFailedLine(lpszFileName, nLine))
         AfxDebugBreak();
      return;     // quick escape
   }

   /*if (!fx_is_valid_address(pOb, typeid(pOb->GetRuntimeClass()->m_nObjectSize, FALSE))
   {
   TRACE(::radix::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal pointer.\n");
   if (AfxAssertFailedLine(lpszFileName, nLine))
   AfxDebugBreak();
   return;     // quick escape
   }*/
   pOb->assert_valid();
}
