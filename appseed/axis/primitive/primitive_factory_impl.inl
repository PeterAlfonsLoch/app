#pragma once


template < class T >
void axis_factory::creatable(sp(type) info, int32_t iCount, bool bOverwrite, bool bAligned)
{
   if(bOverwrite || !is_set(info->name()))
      set_at(info->name(), new creatable_factory_item<T>(get_app(), get_allocator<T>(iCount, bAligned)));
}


template < class T >
void axis_factory::cloneable(sp(type)  info, int32_t iCount, bool bOverwrite, bool bAligned)
{
   if(bOverwrite || !is_set(info->name()))
      set_at(info->name(), new cloneable_factory_item<T>(get_app(), get_allocator<T>(iCount, bAligned)));
}


template < class T >
void axis_factory::creatable(int32_t iCount, bool bOverwrite, bool bAligned)
{
   
   if(bOverwrite || !is_set(System.type_info <  T  > ()->name()))
      set_at(System.type_info <  T  > ()->name(), new creatable_factory_item<T>(get_app(), get_allocator<T>(iCount, bAligned)));
   
}


template < class T >
void axis_factory::cloneable(int32_t iCount, bool bOverwrite, bool bAligned)
{
   
   if(bOverwrite || !is_set(System.type_info <  T  > ()->name()))
      set_at(System.type_info <  T  > ()->name(), new cloneable_factory_item<T>(get_app(), get_allocator<T>(iCount, bAligned)));
   
}

template < class T >
sp(factory_allocator) axis_factory::get_allocator(int32_t iCount, bool bAligned)
{
   
   sp(factory_allocator) pallocator = get_allocator(System.type_info <  T  > ()->name());
   
   if(pallocator != NULL)
      return pallocator;
   
   pallocator = canew(factory_allocator_impl < T > (get_app(), iCount, bAligned));
   
   set_at(System.type_info <  T  > ()->name(), pallocator);
   
   return pallocator;
   
}
