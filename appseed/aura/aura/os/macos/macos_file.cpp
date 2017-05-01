//
//  c_os_file.cpp
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 1/14/12.
//  Copyright (c) 2012 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"



CLASS_DECL_AURA void dll_processes(uint_array & dwa, stringa & straProcesses, const char * pszDll)
{
   
   
   
}


::file::path dir::home()
{

return getenv("HOME");

}

::file::path dir::ca2_user()
{

    return ::file::path(getenv("HOME")) / "Library/ca2";

}

::file::path dir::sys_temp()
{
   
   return ca2_user() / "time";
   
}
