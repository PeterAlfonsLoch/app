#pragma once

#include "include/cube.h"

#ifdef _CA2_FONTOPUS_VEIEV_DLL
    #define CLASS_DECL_CA2_VEIEV  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_VEIEV  _declspec(dllimport)
#endif

#include "veiev_const.h"


#include "veiev_tree_item.h"
#include "veiev_tree_data.h"
#include "veiev_tree_interface.h"
#include "veiev_tree.h"

#include "veiev_list_interface.h"
#include "veiev_list.h"

#include "veiev_configuration.h"
#include "veiev_right_pane_view.h"

#include "veiev_main_view.h"
#include "veiev_right_view.h"

#include "veiev_document.h"
#include "frame.h"
#include "view.h"
#include "primary_command_view.h"
#include "form_callback.h"

#include "view_interface.h"

#include "right_split_view.h"
#include "second_command_view.h"

#include "application.h"