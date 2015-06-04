#pragma once


class simple_mesh_data:
   public ::user::mesh_data
{
public:


   int_map < int_map < string > >          m_map;


   simple_mesh_data(::aura::application * papp);
   virtual ~simple_mesh_data();


   virtual void _001GetItemText(::user::mesh_item * pitem);

   virtual int_ptr _001GetItemCount();
   virtual int_ptr _001GetColumnCount(::user::mesh * pmesh);

   virtual void clear();

};
