#pragma once


namespace fs
{


   class CLASS_DECL_ca list_item_array :
      virtual ::radix::object
   {
   protected:

      class CLASS_DECL_ca base_list_item_array :
         public class_sort_array < base_list_item_array, list_item, const list_item &, array_ptr_alloc < list_item, const list_item & > >
      {
      public:
         list_item & get_item(index i);
         void SoftSwap(index i1, index i2);
      };


      base_list_item_array m_itema;

   public:


      list_item_array(::ca::application * papp);
      virtual ~list_item_array();


      void add_item(list_item & item);
      count get_count();
      count get_size();
      index get_upper_bound(count i = 0);
      list_item & get_item(index i);
      void SetItemAt(index i, list_item & item);
      void SetItemCount(count iCount);
      index find_item_by_path(const char * pszPath);


      void arrange(e_arrange earrange);
   };

} // namespace fs