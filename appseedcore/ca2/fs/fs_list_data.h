#pragma once


namespace fs
{


   class CLASS_DECL_ca list_data :
         public ::user::list_data
   {
   public:

      index                      m_iNameSubItem;
      index                      m_iNameSubItemText;
      index                      m_iSelectionSubItem;
      index                      m_iSizeSubItem;
      bool                       m_bPendingSize;
      DWORD                      m_dwLastFileSizeGet;

      list_item_array            m_itema; 



      list_data(::ca::application * papp);
      virtual ~list_data();

      void update();

      virtual bool _001GetItemText(
         ::user::list * plist,
	      string &str,
	      INT_PTR iItem,
	      INT_PTR iSubItem, 
	      INT_PTR iListItem);

      virtual count _001GetItemCount();

   };


} // namespace fs

