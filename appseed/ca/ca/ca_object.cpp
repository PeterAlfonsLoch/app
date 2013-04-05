#include "framework.h"


namespace ca
{

   /////////////////////////////////////////////////////////////////////////////
   // Runtime Typing

   // special runtime-class structure for ::object (no base class)
   /*const struct ::ca::type_info object::classbase_object =
   { "::object", sizeof(::object), 0xffff, ::null(), ::null(), ::null() };*/
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
         if(::ca::get_thread_state() != ::null())
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
	   
	   m_psetObject = ::null();

      /*try
      {
         if(::ca::get_thread_state() != ::null())
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

      m_psetObject = ::null();

   }
   
   object::~object()
   { 

      try
      {

         if(m_psetObject != ::null())
         {

            delete m_psetObject;

         }

      }
      catch(...)
      {

      }

   }



   object & object::operator=(const object & objectSrc)
   {

      if(objectSrc.m_psetObject != ::null())
      {

         if(m_psetObject == ::null())
         {
            
            m_psetObject = new ::ca::property_set(get_app());

         }

         *m_psetObject = *objectSrc.m_psetObject;

      }

      return *this;

   }

   void object::assert_valid() const
   {
      ASSERT(this != ::null());
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

         oprop("big_icon").operator =((sp(::ca::ca)) picon);

      }
      else
      {

         oprop("small_icon").operator =((sp(::ca::ca)) picon);

      }

      return piconOld;

   }


   ::visual::icon * object::get_icon(bool bBigIcon) const
   {

      if(bBigIcon)
      {

         return const_cast < object * > (this)->oprop("big_icon").ca < ::visual::icon >();

      }
      else
      {

         return const_cast < object * > (this)->oprop("small_icon").ca < ::visual::icon >();

      }

   }


   ::ca::property & object::oprop(const char * psz)
   {

      return propset()[psz];

   }


   ::ca::property & object::oprop(const char * psz) const 
   {

      return const_cast < object * > (this)->propset()[psz];

   }


   ::ca::property_set & object::propset()
   {

      if(m_psetObject == ::null())
      {

         m_psetObject = new ::ca::property_set(get_app());

      }

      return *m_psetObject;

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
//void ::ca::object::AssertValid() const
//   { /* no asserts in release builds */ }
//void ::ca::object::Dump(dump_context &) const
//   { /* no dumping in release builds */ }
#endif //!DEBUG


   ::ca::command_thread & object::command_thread()
   {
      return Application.command();
   }


} //  namespace ca


/////////////////////////////////////////////////////////////////////////////
// Diagnostic Support

//#ifdef DEBUG
void assert_valid_object(const ::ca::object * pOb, const char * lpszFileName, int32_t nLine)
{
   if (pOb == ::null())
   {
//      TRACE(::ca::trace::category_AppMsg, 0, "ASSERT_VALID fails with ::null() pointer.\n");
      if (__assert_failed_line(lpszFileName, nLine))
         __debug_break();
      return;     // quick escape
   }
   if (!__is_valid_address(pOb, sizeof(::ca::object)))
   {
      ///TRACE(::ca::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal pointer.\n");
      if (__assert_failed_line(lpszFileName, nLine))
         __debug_break();
      return;     // quick escape
   }

   // check to make sure the VTable pointer is valid
   //   ASSERT(sizeof(::object) == sizeof(void *));
   //   if (!__is_valid_address(*(void **)pOb, sizeof(void *), FALSE))
   if (!__is_valid_address(*(void **)pOb, sizeof(void *), FALSE))
   {
//      TRACE(::ca::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal vtable pointer.\n");
      if (__assert_failed_line(lpszFileName, nLine))
         __debug_break();
      return;     // quick escape
   }

   /*if (!__is_valid_address(pOb, typeid(pOb->GetRuntimeClass()->m_nObjectSize, FALSE))
   {
   TRACE(::ca::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal pointer.\n");
   if (__assert_failed_line(lpszFileName, nLine))
   __debug_break();
   return;     // quick escape
   }*/
   pOb->assert_valid();
}




