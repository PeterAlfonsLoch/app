//
//  ios_thread_mm.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 4/23/14.
// Feliz Aniversário Mummi!! Feliz 63 anos e 1 dia!! Graças a Deus!!
//


#include "framework.h"


void * get_thread_ptr(const char * pszKey)
{
    
    return (void *)[[[[NSThread currentThread] threadDictionary] valueForKey: [NSString stringWithUTF8String : pszKey]] inValue];
    
}


void set_thread_ptr(const char * pszKey, const void * p)
{
    
    [[[NSThread currentThread] threadDictionary] setValue: [NSNumber numberWithInt : (int_ptr) p] forKey: [NSString stringWithUTF8String : psz]];
    
}


int get_thread_int(const char * pszKey)
{
    
    return (int)[[[[NSThread currentThread] threadDictionary] valueForKey: [NSString stringWithUTF8String : pszKey]] inValue];
    
}


void set_thread_int(const char * pszKey, int i)
{
    
    [[[NSThread currentThread] threadDictionary] setValue: [NSNumber numberWithInt : i] forKey: [NSString stringWithUTF8String : pszKey]];
    
}


