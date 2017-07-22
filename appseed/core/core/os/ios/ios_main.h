//
//  ios_main.hpp
//  core
//
//  Created by Camilo Sasuke Tsumanuma on 21/07/17.
//  Copyright © 2017 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once


namespace aura
{
   
   class library;
   
   class application;
   
   typedef class library * (*PFN_GET_NEW_LIBRARY)(::aura::application * papp);
   
   
} // namespace aura


extern ::aura::PFN_GET_NEW_LIBRARY g_pfnNewLibrary;


int ios_core_main(int argc, char * argv[]);



#define DECL_LIB(X) extern "C" \
::aura::library * X##_get_new_library(::aura::application * papp)

#define SET_LIB(X) g_pfnNewLibrary = &X##_get_new_library


#define DEF_CORE_APP(X) \
DECL_LIB(X); \
\
\
int main(int argc, char * argv[]) \
{ \
   \
   SET_LIB(X); \
    \
   return ios_core_main(argc, argv); \
   \
}








