#include "framework.h"


namespace gen
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
/*      try
      {
         if(::ca::get_thread_state() != NULL)
         {
            ::ca::get_thread_state()->m_heapitema.set_heap_alloc(this);
         }
      }
      catch(...)
      {
      }*/
      common_construct(); 
   }

   object::object(const object& objectSrc)
   {
	   
	   m_pset = NULL;

      /*try
      {
         if(::ca::get_thread_state() != NULL)
         {
            ::ca::get_thread_state()->m_heapitema.set_heap_alloc(this);
         }
      }
      catch(...)
      {
      }*/
      operator =(objectSrc);
   }

   void object::common_construct()
   {

      m_pset = NULL;

   }
   
   object::~object()
   { 

      try
      {

         if(m_pset != NULL)
         {

            delete m_pset;

         }

      }
      catch(...)
      {

      }

   }



   object & object::operator=(const object & objectSrc)
   {

      if(objectSrc.m_pset != NULL)
      {

         if(m_pset == NULL)
         {
            
            m_pset = new gen::property_set(get_app());

         }

         *m_pset = *objectSrc.m_pset;

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

      UNUSED(dumpcontext); // unused in release build
   }



   ::visual::icon * object::set_icon(::visual::icon * picon, bool bBigIcon)
   {

      ::visual::icon * piconOld = get_icon(bBigIcon);

      if(bBigIcon)
      {

         oprop("big_icon").operator =((::ca::ca *) picon);

      }
      else
      {

         oprop("small_icon").operator =((::ca::ca *) picon);

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


   gen::property & object::oprop(const char * psz)
   {

      return propset()[psz];

   }


   gen::property & object::oprop(const char * psz) const 
   {

      return const_cast < object * > (this)->propset()[psz];

   }


   gen::property_set & object::propset()
   {

      if(m_pset == NULL)
      {

         m_pset = new gen::property_set(get_app());

      }

      return *m_pset;

   }




#undef new
   void * object::operator new(size_t size, void * p)
   { 
      UNREFERENCED_PARAMETER(size);
      return p; 
   }
#define new DEBUG_NEW
#ifndef DEBUG
// DEBUG versions in afxmem.cpp
//void object::operator delete(void * p)
  // { ::operator delete(p); }
#if _MSC_VER >= 1200
//void object::operator delete(void * p, void *)
  // { ::operator delete(p); }
#endif
//void * object::operator new(size_t nSize)
  // { return ::operator new(nSize); }
// DEBUG versions in objcore.cpp
//void ::gen::object::AssertValid() const
//   { /* no asserts in release builds */ }
//void ::gen::object::Dump(dump_context &) const
//   { /* no dumping in release builds */ }
#endif //!DEBUG


   ::gen::command_thread & object::command_thread()
   {
      return Application.command();
   }


} //  namespace gen


/////////////////////////////////////////////////////////////////////////////
// Diagnostic Support

//#ifdef DEBUG
void assert_valid_object(const ::gen::object * pOb, const char * lpszFileName, int32_t nLine)
{
   if (pOb == NULL)
   {
//      TRACE(::gen::trace::category_AppMsg, 0, "ASSERT_VALID fails with NULL pointer.\n");
      if (__assert_failed_line(lpszFileName, nLine))
         __debug_break();
      return;     // quick escape
   }
   if (!__is_valid_address(pOb, sizeof(::gen::object)))
   {
      ///TRACE(::gen::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal pointer.\n");
      if (__assert_failed_line(lpszFileName, nLine))
         __debug_break();
      return;     // quick escape
   }

   // check to make sure the VTable pointer is valid
   //   ASSERT(sizeof(::object) == sizeof(void *));
   //   if (!__is_valid_address(*(void **)pOb, sizeof(void *), FALSE))
   if (!__is_valid_address(*(void **)pOb, sizeof(void *), FALSE))
   {
//      TRACE(::gen::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal vtable pointer.\n");
      if (__assert_failed_line(lpszFileName, nLine))
         __debug_break();
      return;     // quick escape
   }

   /*if (!__is_valid_address(pOb, typeid(pOb->GetRuntimeClass()->m_nObjectSize, FALSE))
   {
   TRACE(::gen::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal pointer.\n");
   if (__assert_failed_line(lpszFileName, nLine))
   __debug_break();
   return;     // quick escape
   }*/
   pOb->assert_valid();
}




