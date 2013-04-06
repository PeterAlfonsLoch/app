#pragma once


namespace fs
{


   class CLASS_DECL_ca2 list_item_array :
      virtual ::ca::object
   {
   protected:

      class CLASS_DECL_ca2 base_list_item_array :
         public spsa(list_item)
      {
      public:
         list_item & get_item(index i, index (* fCompare)(sp(list_item) *, sp(list_item) *));
         void SoftSwap(index i1, index i2);
      };


      base_list_item_array m_itema;
      index (* m_pfnCompare)(sp(list_item) *, sp(list_item) *);

   public:


      list_item_array(sp(::ca::application) papp);
      virtual ~list_item_array();


      void add_item(list_item & item);
      ::count get_count();
      ::count get_size();
      index get_upper_bound(::count i = -1);
      list_item & get_item(index i);
      //void SetItemAt(index i, list_item & item);
      //void SetItemCount(::count iCount);
      index find_item_by_path(const char * pszPath);


      void arrange(e_arrange earrange);
   };

} // namespace fs
