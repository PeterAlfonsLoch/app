#include "framework.h"


namespace draw2d_xlib
{



   object::object()
   {
      //set_handle(NULL);
   }

   object::~object()
   {
      //delete_object();
   }

   int32_t object::get_object(int32_t nCount, LPVOID lpObject) const
   {
      //return ::GetObject(get_handle(), nCount, lpObject);
      return 0;
   }

   bool object::CreateStockObject(int32_t nIndex)
   {
      //return (set_handle(::GetStockObject(nIndex))) != NULL;
      return 0;
   }
   bool object::UnrealizeObject()
   {
      //ASSERT(get_handle() != NULL); return ::UnrealizeObject(get_handle());
      return 0;
   }
   UINT object::GetObjectType() const
   {
      //return (UINT)::GetObjectType(get_handle());
      return 0;
   }

   object * graphics_object_allocator(sp(::base::application) papp, HANDLE h)
   {
      return NULL;
   }


   bool object::delete_object()
   {
      return FALSE;
   }



   void object::dump(dump_context & dumpcontext) const
   {
      ::object::dump(dumpcontext);

   }

   void object::assert_valid() const
   {
      ::object::assert_valid();
   }



   void * object::get_os_data() const
   {

      return NULL;

   }


} // namespace draw2d_xlib






