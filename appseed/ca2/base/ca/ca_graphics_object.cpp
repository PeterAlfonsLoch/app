#include "framework.h"

namespace ca
{

   /////////////////////////////////////////////////////////////////////////////
   // graphics_object

   void graphics_object::dump(dump_context & dumpcontext) const
   {
      UNREFERENCED_PARAMETER(dumpcontext);
      throw interface_only_exception(get_app());
   }

   void graphics_object::assert_valid() const
   {
      throw interface_only_exception(get_app());
   }

   graphics_object::~graphics_object()
   {
      
      destroy();
      
   }

/*   int32_t graphics_object::___FUNCNAME(GetObject)(int32_t nCount, LPVOID lpObject) const
   {
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpObject);
      throw interface_only_exception(get_app());
   }*/

/*#pragma push_macro("GetObject")
#undef GetObject

   int32_t graphics_object::GetObject(int32_t nCount, LPVOID lpObject) const
   {
      return ___FUNCNAME(GetObject)(nCount, lpObject);
   }

#pragma pop_macro("GetObject")*/

   bool graphics_object::CreateStockObject(int32_t nIndex)
   {
      throw interface_only_exception(get_app());
   }

   bool graphics_object::UnrealizeObject()
   {
      throw interface_only_exception(get_app());
   }

   UINT graphics_object::GetObjectType() const
   {
      throw interface_only_exception(get_app());
   }

   bool graphics_object::operator==(const graphics_object & obj) const
   {
      UNREFERENCED_PARAMETER(obj);
      throw interface_only_exception(get_app());
   }

   bool graphics_object::operator!=(const graphics_object & obj) const
   {
      UNREFERENCED_PARAMETER(obj);
      throw interface_only_exception(get_app());
   }

   
   void * graphics_object::get_os_data() const
   {
      
      return 0;
      
   }

   
   bool graphics_object::is_set()
   {
      
      return get_os_data() != 0;
      
   }

   
   bool graphics_object::is_updated()
   {
      
      return is_set() && m_bUpdated;
      
   }
   
   
   void graphics_object::defer_update() const
   {
      
      if(!m_bUpdated)
      {

         const_cast < ::ca::graphics_object * > (this)->destroy();
         
         const_cast < ::ca::graphics_object * > (this)->create();
         
         const_cast < ::ca::graphics_object * > (this)->m_bUpdated = true;
         
      }
      
   }
   
   
   bool graphics_object::create()
   {
      
      return true;
      
   }

   
   bool graphics_object::destroy()
   {
      
      return true;
      
   }

   
} // namespace ca





