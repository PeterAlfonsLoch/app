//
//  macos_ns_exception.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 21/07/17.
//
//



#pragma once


#if defined(__cplusplus)

class ns_exception
{
public:
   
   int m_iCode;
   
   ns_exception();
   ~ns_exception();
   
};

#endif



void InstallUncaughtExceptionHandler();
void InstallNullExceptionHandler();




