#pragma once


namespace databaseuser
{


   class CLASS_DECL_CORE data_key_mesh_data :
      public ::user::mesh_data,
      public ::database::client
   {
   public:


      data_key_mesh_data(::aura::application * papp);
      virtual ~data_key_mesh_data();


      virtual void _001GetItemText(::user::mesh_item * pitem);

      virtual count _001GetItemCount();

      bool add_unique(const stringa & stra);
      bool remove(const stringa & stra);

      void GetSel(::user::list * plist , stringa & stra);


   private:


      data_key_mesh_data(const data_key_mesh_data & ) :
         ::user::mesh_data(NULL)
      {
      }


   };


} // namespace databaseuser



