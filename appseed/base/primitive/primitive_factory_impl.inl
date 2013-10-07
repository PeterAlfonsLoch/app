#pragma once


template < class T >
void base_factory::creatable(sp(type) info, int32_t iCount, bool bOverwrite)
{
   if(bOverwrite || !is_set(info->name()))
      set_at(info->name(), new creatable_factory_item<T>(get_app(), get_allocator<T>(iCount)));
}


template < class T >
void base_factory::cloneable(sp(type)  info, int32_t iCount, bool bOverwrite)
{
   if(bOverwrite || !is_set(info->name()))
      set_at(info->name(), new cloneable_factory_item<T>(get_app(), get_allocator<T>(iCount)));
}

