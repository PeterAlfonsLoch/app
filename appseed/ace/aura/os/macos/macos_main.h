//
//  macos_main.h
//  aura
//
//  Created by Carlos Gustavo Cecyn Lundgren on 8/2/15.
//
//

#pragma once


uint32_t __run_system_command_line(const char * pszCommandLine);



struct main_param
{
   int argc;
   char * *argv;
   
};

uint32_t __run_system_main_param(struct main_param * p);
