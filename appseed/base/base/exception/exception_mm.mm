//
//  exception_mm.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 4/23/14.
// Feliz Aniversário Mummi!! Feliz 63 anos e 1 dia!! Graças a Deus!!
//


#include "framework.h"


void * __get_thread_ptr(const char * psz)
{
   
    return (void *)[[[[NSThread currentThread] threadDictionary] valueForKey: [NSString stringWithUTF8String : psz]] longValue];
    
}


void __set_thread_ptr(void * p, const char * psz)
{
    return [[[NSThread currentThread] threadDictionary] setValue: [NSNumber numberWithInt : (int_ptr) p ] forKey : [NSString stringWithUTF8String : psz]];
}



