#pragma once


namespace databaseuser
{


   class CLASS_DECL_CORE list_data :
      public ::user::list_data,
      public ::database::client
   {
   public:
      
      
      ::count m_iItemCount;


      list_data(sp(::base::application) papp);
      virtual ~list_data();

      virtual void _001GetItemText(::user::list_item * pitem);

      virtual count _001GetItemCount();

      virtual bool Map(::user::list * plist, ::database::id & key1, ::database::id & key2, index iItem, index iSubItem, index iListItem);


   private:


      list_data(const list_data & ) :
         ::user::list_data(NULL)
      {
      }


   };


} // namespace user



