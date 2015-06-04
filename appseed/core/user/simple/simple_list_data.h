#pragma once


class CLASS_DECL_CORE simple_list_data:
   virtual public ::user::list_data
{
public:


   bool                 m_bEnable;

   spa(stringa)         m_array;


   simple_list_data(::aura::application * papp);
   virtual ~simple_list_data();


   bool remove_item(index iItem);
   void get_data(stringa & stra);
   void get_column_data(stringa & stra,index iColumn);
   void set_data(::user::mesh * pmesh,stringa & stra);
   void set_column_data(::user::mesh * pmesh,stringa & stra,index iColumn);
   void Enable(bool bEnable);
   void set_item_text(::user::mesh * pmesh,index iItem,index iSubItem,const char * lpcsz);


   virtual void _001GetItemText(::user::mesh_item * pitem);

   virtual void _001OnDeleteRange(::user::mesh::range & range);


   virtual int_ptr _001GetItemCount();

   void set_item_text(int_ptr iItem,int_ptr iSubItem,const char * lpcsz);


};














