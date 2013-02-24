//
//  exception_overflow_error.cpp
//  ca
//
//  Created by Camilo Sasuke Tsumanuma on 1/28/12.
//  Copyright (c) 2012 ca Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"


overflow_error::overflow_error(::ca::application * papp, const char * pszError) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp),
   error_exception(papp, pszError)
{
}

overflow_error::~overflow_error()
{
}
