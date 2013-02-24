//
//  plane_system_radix_factory.h
//  ca
//
//  Created by Camilo Sasuke Tsumanuma on 1/28/12.
//  Copyright (c) 2012 ca Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once


template < class T >
void factory::creatable(int32_t iCount, bool bOverwrite)
{

   if(bOverwrite || !is_set(System.type_info < T > ().name()))
      set_at(System.type_info < T > ().name(), new creatable_factory_item<T>(get_app(), get_allocator<T>(iCount)));

}


template < class T >
void factory::cloneable(int32_t iCount, bool bOverwrite)
{

   if(bOverwrite || !is_set(System.type_info < T > ().name()))
      set_at(System.type_info < T > ().name(), new cloneable_factory_item<T>(get_app(), get_allocator<T>(iCount)));

}

template < class T >
factory_allocator * factory::get_allocator(int32_t iCount)
{

   factory_allocator * pallocator = get_allocator(System.type_info < T > ().name());

   if(pallocator != NULL)
      return pallocator;

   pallocator = new factory_allocator_impl < T > (get_app(), iCount);

   set_at(System.type_info < T > ().name(), pallocator);

   return pallocator;

}
