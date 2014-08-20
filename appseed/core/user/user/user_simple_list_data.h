#pragma once

namespace user
{

   class CLASS_DECL_CORE simple_list_data  :
      virtual public list_data
   {
   public:
      
      
      bool                 m_bEnable;

      spa(stringa)         m_array;

      
      simple_list_data(sp(::axis::application) papp);
      virtual ~simple_list_data();


      bool remove_item(index iItem);
      void get_data(stringa & stra);
      void get_column_data(stringa & stra, index iColumn);
      void set_data(list * plist, stringa & stra);
      void set_column_data(list * plist, stringa & stra, index iColumn);
      void Enable(bool bEnable);
      void set_item_text(list * plist, index iItem, index iSubItem, const char * lpcsz);
      

      virtual void _001GetItemText(list_item * pitem);

      virtual void _001OnDeleteRange(::user::list::range & range);


      virtual int_ptr _001GetItemCount();

   protected:
      void set_item_text(int_ptr iItem, int_ptr iSubItem, const char * lpcsz);
   };

} // namespace user