#include "framework.h"


namespace draw2d_direct2d
{


   object::object()
   {

      //set_handle(NULL); 
      m_pgraphics    = NULL;
      m_powner       = NULL;

   }
   
   object::~object()
   { 
      //delete_object(); 
   }
   
   int object::get_object(int nCount, LPVOID lpObject) const
   { 
      //return ::GetObject(get_handle(), nCount, lpObject); 
      return 0;
   }

   bool object::CreateStockObject(int nIndex)
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

   bool object::operator==(const object& obj) const
   { 
      //return ((HGDIOBJ) obj.get_os_data()) == get_handle(); 
      return FALSE;
   }

   bool object::operator!=(const object& obj) const
   { 
      //return ((HGDIOBJ) obj.get_os_data()) != get_handle(); 
      return TRUE;
   }


   object * object_allocator(::base::application * papp, HANDLE h)
   {

      return NULL;

   }


   bool object::delete_object()
   {
      //if (get_os_data() == NULL)
        // return FALSE;
      //return ::DeleteObject(Detach());
      return FALSE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // object


   void object::dump(dump_context & dumpcontext) const
   {
      ::object::dump(dumpcontext);

//      dumpcontext << "get_handle() = " << get_handle();
  //    dumpcontext << "\n";
   }

   void object::assert_valid() const
   {
      ::object::assert_valid();
      //ASSERT(get_handle() == NULL ||
        // (afxData.bWin95 || ::GetObjectType(get_handle()) != 0));
   }


   /*void * object::detach_os_data()
   {
      return Detach();
   }*/

   /*void * object::get_os_data() const
   {
   return get_os_data();
   }*/

   void * object::get_os_data() const
   {
      return NULL;
   }

   void * object::get_os_data_ex(int i) const
   {
      if(i == data_graphics)
      {
         return m_pgraphics;
      }
      return ::draw2d::object::get_os_data_ex(i);
   }

} // namespace draw2d_direct2d


/*hgdiobj_map * afxMapHGDIOBJ(bool bCreate)
{
   UNREFERENCED_PARAMETER(bCreate);
   try
   {
      __MODULE_STATE* pState = __get_module_state();
      if(pState == NULL)
         return NULL;
      return pState->m_pmapHGDIOBJ;
   }
   catch(...)
   {
      return NULL;
   }

}
*/


