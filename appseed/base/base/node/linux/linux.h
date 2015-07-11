#pragma once

#include "aura/node/linux/linux.h"


#include "linux_factory_exchange.h"


#include "linux_copydesk.h"


#include "linux_window_draw.h"


#include "linux_interaction_impl.h"


#include "linux_internal.h"


#define LNX_WINDOW(pwnd) (dynamic_cast < ::linux::interaction_impl * > (((sp(::user::interaction_impl))(pwnd)).m_p))


