#include "framework.h"


/////////////////////////////////////////////////////////////////////////////
// Runtime Typing

// special runtime-class structure for ::object (no base class)
/*const struct sp(type) object::classbase_object =
{ "::object", sizeof(::object), 0xffff, NULL, NULL, NULL };*/
/*
sp(type) object::GetRuntimeClass() const
{
return _RUNTIME_CLASS(::object);
}
*/

object::object()
{ 
/*      try
   {
      if(::ca2::get_thread_state() != NULL)
      {
         ::ca2::get_thread_state()->m_heapitema.set_heap_alloc(this);
      }
   }
   catch(...)
   {
   }*/
   common_construct(); 
}

object::object(const object& objectSrc)
{
	   
	m_psetObject = NULL;

   /*try
   {
      if(::ca2::get_thread_state() != NULL)
      {
         ::ca2::get_thread_state()->m_heapitema.set_heap_alloc(this);
      }
   }
   catch(...)
   {
   }*/
   operator =(objectSrc);
}

void object::common_construct()
{

   m_psetObject = NULL;

}
   
object::~object()
{ 

   try
   {

      if(m_psetObject != NULL)
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

   if(objectSrc.m_psetObject != NULL)
   {

      if(m_psetObject == NULL)
      {
            
         m_psetObject = new property_set(get_app());

      }

      *m_psetObject = *objectSrc.m_psetObject;

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





property & object::oprop(const char * psz)
{

   return propset()[psz];

}


property & object::oprop(const char * psz) const 
{

   return const_cast < object * > (this)->propset()[psz];

}


property_set & object::propset()
{

   if(m_psetObject == NULL)
   {

      m_psetObject = new property_set(get_app());

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
//void object::AssertValid() const
//   { /* no asserts in release builds */ }
//void object::Dump(dump_context &) const
//   { /* no dumping in release builds */ }
#endif //!DEBUG




/////////////////////////////////////////////////////////////////////////////
// Diagnostic Support

//#ifdef DEBUG
void assert_valid_object(const object * pOb, const char * lpszFileName, int32_t nLine)
{
   if (pOb == NULL)
   {
//      TRACE(::ca2::trace::category_AppMsg, 0, "ASSERT_VALID fails with NULL pointer.\n");
      if (__assert_failed_line(lpszFileName, nLine))
         __debug_break();
      return;     // quick escape
   }
   if (!__is_valid_address(pOb, sizeof(object)))
   {
      ///TRACE(::ca2::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal pointer.\n");
      if (__assert_failed_line(lpszFileName, nLine))
         __debug_break();
      return;     // quick escape
   }

   // check to make sure the VTable pointer is valid
   //   ASSERT(sizeof(::object) == sizeof(void *));
   //   if (!__is_valid_address(*(void **)pOb, sizeof(void *), FALSE))
   if (!__is_valid_address(*(void **)pOb, sizeof(void *), FALSE))
   {
//      TRACE(::ca2::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal vtable pointer.\n");
      if (__assert_failed_line(lpszFileName, nLine))
         __debug_break();
      return;     // quick escape
   }

   /*if (!__is_valid_address(pOb, typeid(pOb->GetRuntimeClass()->m_nObjectSize, FALSE))
   {
   TRACE(::ca2::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal pointer.\n");
   if (__assert_failed_line(lpszFileName, nLine))
   __debug_break();
   return;     // quick escape
   }*/
   pOb->assert_valid();
}




