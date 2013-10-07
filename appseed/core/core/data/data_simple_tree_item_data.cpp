#include "framework.h"

namespace data
{

   /*#define ROUND(x,y) (((x)+(y-1))&~(y-1))
   #define ROUND4(x) ROUND(x, 4)
   __STATIC fixed_alloc_no_sync _alloc001SimpleTreeItem(ROUND4(sizeof(::data::simple_tree_item_data)));*/

   simple_tree_item_data::simple_tree_item_data()
   {
      m_iImage          = -1;
      m_iImageSelected  = -1;

   /*#undef new
      new(&m_str) string;
   #define new BASE_NEW*/
   }

   simple_tree_item_data::~simple_tree_item_data()
   {
   }

   string simple_tree_item_data::get_text(sp(::data::tree) ptree)
   {
      UNREFERENCED_PARAMETER(ptree);
      return m_str;
   }
   
   index simple_tree_item_data::get_image(sp(::data::tree) ptree)
   {
      if(ptree->is_tree_item_data_selected(this))
      {
         return m_iImageSelected;
      }
      else
      {
         return m_iImage;
      }
   }


/*#undef new
   void * simple_tree_item_data::operator new(size_t, const char *, int32_t)
   {
      return _alloc001SimpleTreeItem.Alloc();
   }

   void * simple_tree_item_data::operator new(size_t)
   {
      return _alloc001SimpleTreeItem.Alloc();
   }
#define new BASE_NEW*/

/*   void simple_tree_item_data::operator delete(void * p)
   {
      return _alloc001SimpleTreeItem.Free(p);
   }

   void simple_tree_item_data::operator delete(void * p, const char *, int32_t)
   {
      return _alloc001SimpleTreeItem.Free(p);
   }*/

} // namespace data
