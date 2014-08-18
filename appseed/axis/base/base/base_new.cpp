//
//  base_new.cpp
//  base
//
//  Created by Carlos Gustavo Cecyn Lundgren on 4/11/14.
//  Curitiba, 11 de abril de 2014 05:04 0x -> AM except 11 e 12
//  by Camilo : Carlos, eu te amo!!
//
//

#include "framework.h"


#undef new


void * __cdecl operator new(size_t nSize) new_throw_spec
{
    
    return memory_alloc(nSize);
    
}


void __cdecl operator delete(void * p) del_throw_spec
{
    
    memory_free(p);
    
}


void * __cdecl operator new[](size_t nSize) new_throw_spec
{
    
    return ::operator new(nSize);
    
}


void __cdecl operator delete[](void * p) del_throw_spec
{
    
    ::operator delete(p);
    
}




