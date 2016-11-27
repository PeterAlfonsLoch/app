#pragma once


namespace user
{


   class CLASS_DECL_CORE list_cache:
      virtual public mesh_cache_interface
   {
   public:



      int_ptr_to_int_ptr_to_string        m_map;


      list_cache(::aura::application * papp);
      virtual ~list_cache();


      void _001Invalidate(mesh * pmesh);

      virtual void _001CacheHint(mesh * pmesh,int_ptr iItemStart,int_ptr iItemCount);

      virtual void _001GetItemText(::user::mesh_item * pitem);


   };


} // namespace user





