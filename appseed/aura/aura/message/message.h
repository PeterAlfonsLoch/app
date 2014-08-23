#pragma once


#include "message_cross_windows.h"


#define CN_UPDATE_COMMAND_UI 23
#define WM_REFLECT_AXIS 2048
#define MX_APPLANGUAGE 1000
#define USER_MESSAGE 1024


#define MPARAM uint32_t
#define NPARAM uint32_t
#define OPARAM uint32_t


#include "message_definition.h"
#include "message_dispatch.h"
#undef new
#include "message_base.h"
//#include "message_user.h"
#define new AXIS_NEW
#include "message.inl"


namespace message
{




   CLASS_DECL_AURA bool is_idle_message(::signal_details * pobj);


   CLASS_DECL_AURA bool is_idle_message(MESSAGE* pMsg);




} // namespace message




