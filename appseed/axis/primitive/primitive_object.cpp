#include "framework.h"



object::object()
{ 

   common_construct(); 

}


object::object(const object& objectSrc)
{
	   
	m_psetObject = NULL;

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


   return *this;

}


void object::assert_valid() const
{
}







void assert_valid_object(const object * pOb,const char * lpszFileName,int32_t nLine)
{
   if(pOb == NULL)
   {
      //      TRACE(::base::trace::category_AppMsg, 0, "ASSERT_VALID fails with NULL pointer.\n");
      if(__assert_failed_line(lpszFileName,nLine))
         debug_break();
      return;     // quick escape
   }
   if(!__is_valid_address(pOb,sizeof(object)))
   {
      ///TRACE(::base::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal pointer.\n");
      if(__assert_failed_line(lpszFileName,nLine))
         debug_break();
      return;     // quick escape
   }

   // check to make sure the VTable pointer is valid
   //   ASSERT(sizeof(::object) == sizeof(void *));
   //   if (!__is_valid_address(*(void **)pOb, sizeof(void *), FALSE))
   if(!__is_valid_address(*(void **)pOb,sizeof(void *),FALSE))
   {
      //      TRACE(::base::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal vtable pointer.\n");
      if(__assert_failed_line(lpszFileName,nLine))
         debug_break();
      return;     // quick escape
   }

   /*if (!__is_valid_address(pOb, typeid(pOb->GetRuntimeClass()->m_nObjectSize, FALSE))
   {
   TRACE(::base::trace::category_AppMsg, 0, "ASSERT_VALID fails with illegal pointer.\n");
   if (__assert_failed_line(lpszFileName, nLine))
   debug_break();
   return;     // quick escape
   }*/
   pOb->assert_valid();
}







