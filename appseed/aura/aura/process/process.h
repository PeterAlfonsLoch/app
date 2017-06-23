#pragma once


namespace process
{


   CLASS_DECL_AURA bool set_priority(int32_t priority);

   CLASS_DECL_AURA string app_id_to_app_name(string strId);

   
} // namespace process



#include "process_pipe.h"
#include "process_bidi_pipe.h"
#include "process_process.h"
#include "process_department.h"
