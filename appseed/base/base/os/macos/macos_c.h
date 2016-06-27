//
//  macos_c.h
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 6/26/16.
//
//

#pragma once


#include "macos_windowing_c.h"



void nsapp_activate_ignoring_other_apps(int i);
void nsapp_activation_policy_regular();
void nsapp_activation_policy_prohibited();
void nsapp_activation_policy_accessory();
bool nsapp_activation_policy_is_accessory();
bool nsapp_activation_policy_is_regular();



int32_t run_system();
int32_t base_main_command_line(const char * pszParams, int argc, char *argv[]);
