//
//  ios_mm.m
//  aura
//
//  Created by Carlos Gustavo Cecyn Lundgren on 8/3/15.
//
//

#include "framework.h"

int _get_exe_path_len()
{
   
   return strlen([[[NSBundle mainBundle] executablePath] UTF8String]);
   
}

void _get_exe_path(char * pszPath, int size)
{
   
   strncpy(pszPath, [[[NSBundle mainBundle] executablePath] UTF8String], size);
   
}