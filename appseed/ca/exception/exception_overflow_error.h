//
//  exception_overflow_error.h
//  ca
//
//  Created by Camilo Sasuke Tsumanuma on 1/28/12.
//  Copyright (c) 2012 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once


class CLASS_DECL_ca overflow_error :
   virtual public error_exception
{
   // base class for resource-critical ca2 API exceptions
   // handles ownership and initialization of an error message
public:


   overflow_error(::ca::application * papp, const char * pszError);
   virtual ~overflow_error();


};



