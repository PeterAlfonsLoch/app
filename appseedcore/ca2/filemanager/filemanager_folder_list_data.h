#pragma once


namespace filemanager
{
   
   class CLASS_DECL_ca folder_list_data :
      public ::user::list_data,
      public ::database::client
   {
   public:


      folder_list_data(::ca::application * papp);
      virtual ~folder_list_data(void);


      virtual bool _001GetItemText(::user::list * plist, string &str, index iItem, index iSubItem, index iListItem);

      virtual count _001GetItemCount();

      bool add_unique(const stringa & stra, bool_array & baRecursive);
      bool remove(const stringa & stra);

      void GetSel(::user::list * plist , stringa & stra);

   };


} // namespace filemanager
