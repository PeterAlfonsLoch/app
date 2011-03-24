#pragma once

namespace user
{

   class CLASS_DECL_ca simple_list_data  :
      virtual public list_data
   {
   public:
      
      
      bool m_bEnable;

      array_ptr_alloc < stringa , stringa & > m_array;

      
      simple_list_data(::ca::application * papp);
      virtual ~simple_list_data();


      bool RemoveItem(index iItem);
      void get_data(stringa & stra);
      void GetColumnData(stringa & stra, index iColumn);
      void set_data(list * plist, stringa & stra);
      void SetColumnData(list * plist, stringa & stra, index iColumn);
      void Enable(bool bEnable);
      void SetItemText(list * plist, index iItem, index iSubItem, const char * lpcsz);
      

      virtual bool _001GetItemText(list * plist, string &str, index iItem, index iSubItem, index iListItem);

      virtual INT_PTR _001GetItemCount();

   protected:
      void SetItemText(INT_PTR iItem, INT_PTR iSubItem, const char * lpcsz);
   };

} // namespace user