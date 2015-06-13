#pragma once


namespace databaseuser
{


   class CLASS_DECL_CORE mesh_data :
      public ::user::mesh_data,
      public ::database::client
   {
   public:
      
      
      ::count m_iItemCount;


      mesh_data(::aura::application * papp);
      virtual ~mesh_data();

      virtual void _001GetItemText(::user::mesh_item * pitem);

      virtual count _001GetItemCount();

      virtual bool Map(::user::mesh * pmesh, ::database::id & key1, ::database::id & key2, index iItem, index iSubItem, index iListItem);


   private:


      mesh_data(const mesh_data & ) :
         ::user::mesh_data(NULL)
      {
      }


   };


} // namespace user



