//
//  ios_ns_exception.h
//  base
//
//  Created by Carlos Gustavo Cecyn Lundgren on 18/10/13.
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




