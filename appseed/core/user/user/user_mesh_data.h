#pragma once


namespace user
{


   class list;


   class CLASS_DECL_CORE mesh_data :
      public ::data::data
   {
   public:


      mesh_data(::aura::application * papp);
      virtual ~mesh_data();


      virtual void _001GetItemText(mesh_item * pitem) = 0;

      virtual void _001GetItemImage(mesh_item * pitem);

      virtual void _001GetGroupText(mesh_item * pitem);

      virtual void _001GetGroupImage(mesh_item * pitem);

      virtual count _001GetItemCount();

      virtual count _001GetColumnCount(mesh * pmesh);

      virtual count _001GetGroupCount();

      virtual ::count _001GetGroupMetaItemCount(index iGroup);

      virtual void _001OnDeleteRange(::user::mesh::range & range);

   };


} // namespace user



