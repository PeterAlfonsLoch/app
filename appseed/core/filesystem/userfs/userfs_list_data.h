#pragma once


namespace userfs
{


   class CLASS_DECL_CORE list_data :
         public ::user::list_data
   {
   public:

      index                      m_iNameSubItem;
      index                      m_iNameSubItemText;
      index                      m_iSelectionSubItem;
      index                      m_iSizeSubItem;
      bool                       m_bPendingSize;
      uint32_t                      m_dwLastFileSizeGet;

      list_item_array            m_itema; 



      list_data(sp(::axis::application) papp);
      virtual ~list_data();

      void update();

      virtual void _001GetItemText(::user::list_item * pitem);

      virtual count _001GetItemCount();

      virtual void _001GetItemImage(::user::list_item * pitem);


   };


} // namespace userfs

