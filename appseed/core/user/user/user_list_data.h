#pragma once


namespace user
{


   class list;


   class CLASS_DECL_CORE list_data :
      public ::data::data
   {
   public:


      list_data(sp(::aura::application) papp);
      virtual ~list_data();


      virtual void _001GetItemText(list_item * pitem) = 0;

      virtual void _001GetItemImage(list_item * pitem);

      virtual void _001GetGroupText(list_item * pitem);

      virtual void _001GetGroupImage(list_item * pitem);

      virtual count _001GetItemCount() = 0;

      virtual count _001GetGroupCount();

      virtual ::count _001GetGroupMetaItemCount(index iGroup);

      virtual void _001OnDeleteRange(::user::list::range & range);

   };


} // namespace user



