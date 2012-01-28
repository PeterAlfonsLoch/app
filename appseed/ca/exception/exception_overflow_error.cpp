//
//  exception_overflow_error.cpp
//  ca
//
//  Created by Camilo Sasuke Tsumanuma on 1/28/12.
//  Copyright (c) 2012 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "StdAfx.h"


overflow_error::overflow_error(const char * pszError) :
error_exception(pszError)
{
}

overflow_error::~overflow_error()
{
}