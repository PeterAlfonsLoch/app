#pragma once


template < class T >
void base_factory::creatable(const type * info, int32_t iCount, bool bOverwrite, bool bAligned)
{
   if(bOverwrite || !is_set(info->name()))
      m_mapItem[info->name()] = canew(creatable_factory_item<T>(get_app(), get_allocator<T>(iCount, bAligned)));
}


template < class T >
void base_factory::cloneable(const type *  info, int32_t iCount, bool bOverwrite, bool bAligned)
{
   if(bOverwrite || !is_set(info->name()))
      m_mapItem[info->m_id] = canew(cloneable_factory_item<T>(get_app(), get_allocator<T>(iCount, bAligned)));
}


template < class T >
void base_factory::creatable(int32_t iCount, bool bOverwrite, bool bAligned)
{
   
   if(bOverwrite || !is_set(System.type_info <  T  > ()->name()))
      m_mapItem[System.type_info <  T  > ()->m_id] = canew(creatable_factory_item<T>(get_app(), get_allocator<T>(iCount, bAligned)));
   
}


template < class T >
void base_factory::cloneable(int32_t iCount, bool bOverwrite, bool bAligned)
{
   
   if(bOverwrite || !is_set(System.type_info <  T  > ()->name()))
      m_mapItem[System.type_info <  T  > ()->m_id] = canew(cloneable_factory_item<T>(get_app(), get_allocator<T>(iCount, bAligned)));
   
}

template < class T >
void base_factory::default_creatable(const type * info,int32_t iCount,bool bOverwrite,bool bAligned)
{
   if(bOverwrite || !is_set(info->name()))
      m_mapItem[info->m_id] = canew(default_creatable_factory_item<T>(get_app(),get_allocator<T>(iCount,bAligned)));
}


template < class T >
void base_factory::default_cloneable(const type *  info,int32_t iCount,bool bOverwrite,bool bAligned)
{
   if(bOverwrite || !is_set(info->name()))
      m_mapItem[info->m_id] = canew(default_cloneable_factory_item<T>(get_app(),get_allocator<T>(iCount,bAligned)));
}


template < class T >
void base_factory::default_creatable(int32_t iCount,bool bOverwrite,bool bAligned)
{

   if(bOverwrite || !is_set(System.type_info <  T  >()->name()))
      m_mapItem[System.type_info <  T  >()->m_id] = canew(default_creatable_factory_item<T>(get_app(),get_allocator<T>(iCount,bAligned)));

}


template < class T >
void base_factory::default_cloneable(int32_t iCount,bool bOverwrite,bool bAligned)
{

   if(bOverwrite || !is_set(System.type_info <  T  >()->name()))
      m_mapItem[System.type_info <  T  >()->m_id] = canew(default_cloneable_factory_item<T>(get_app(),get_allocator<T>(iCount,bAligned)));

}

template < class T >
sp(factory_allocator) & base_factory::get_allocator(int32_t iCount, bool bAligned)
{
   
   sp(factory_allocator) & pallocator = m_mapAllocator[System.type_info <  T  > ()->m_id];
   
   if(pallocator.is_set())
      return pallocator;
   
   pallocator = canew(factory_allocator_impl < T > (get_app(), iCount, bAligned));
   
   return pallocator;
   
}
