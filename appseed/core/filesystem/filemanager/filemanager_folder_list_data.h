#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE folder_list_data :
      public ::user::list_data,
      public ::database::client
   {
   public:


      folder_list_data(sp(::base::application) papp);
      virtual ~folder_list_data();


      virtual void _001GetItemText(::user::list_item * pitem);

      virtual count _001GetItemCount();

      bool add_unique(const stringa & stra, bool_array & baRecursive);
      bool remove(const stringa & stra);

      void GetSel(::user::list * plist , stringa & stra);


   private:

      
      folder_list_data(const folder_list_data & ) :
         ::user::list_data(NULL)
      {
      }


   };


} // namespace filemanager



